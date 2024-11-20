#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int moistureSensorPin = A0;
const int motorRelayPin = 3;
const int heaterRelayPin = 9;
const int moistureThreshold = 500;

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Statia Compost");

  pinMode(moistureSensorPin, INPUT);
  pinMode(motorRelayPin, OUTPUT);
  pinMode(heaterRelayPin, OUTPUT);

  digitalWrite(motorRelayPin, LOW);
  digitalWrite(heaterRelayPin, LOW);

  delay(2000);
}

void loop() {
  int moistureLevel = analogRead(moistureSensorPin);

  lcd.setCursor(0, 0);
  lcd.print("Umiditate: ");
  lcd.print(moistureLevel);

  if (moistureLevel < moistureThreshold) {
    lcd.setCursor(0, 1);
    lcd.print("Adauga apa!   ");
    digitalWrite(heaterRelayPin, LOW);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Umiditate OK  ");
    digitalWrite(heaterRelayPin, HIGH);
  }

  digitalWrite(motorRelayPin, HIGH);
  delay(5000);
  digitalWrite(motorRelayPin, LOW);

  delay(5000);
}
