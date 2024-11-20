#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int enA = 5;
int in1 = 3;
int in2 = 4;

LiquidCrystal_I2C lcd(32, 16, 2);

int tempPin = A1;
int lightPin = A2;
int moisturePin = A0;

void setup() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  int tempValue = analogRead(tempPin);
  int lightValue = analogRead(lightPin);
  int moistureValue = analogRead(moisturePin);

  float temp = (((tempValue * 5.0) / 1024.0) - 0.5) * 100;
  float light = (lightValue * 5.0) / 1024.0;
  float moisture = (moistureValue * 5.0) / 1024.0;

  Serial.print("Temp ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Light:");
  Serial.print(light);
  Serial.println("V");
  Serial.print("Moist: ");
  Serial.print(moisture);
  Serial.println("V");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Light:");
  lcd.print(light);
  lcd.print("V");
  lcd.setCursor(8, 1);
  lcd.print("Moist:");
  lcd.print(moisture);
  lcd.print("V");

  if ((temp > 30 || light < 2) && moisture < 4) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 255);
    Serial.println("Turning on the motor...");
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0);
    Serial.println("Turning off the motor...");
  }

  delay(1000);
}
