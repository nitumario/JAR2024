#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>

LiquidCrystal lcd(13, 12, 6, 5, 4, 3);
SoftwareSerial ser(8, 9);

float t = 0;
String apiKey = ""; 
String firebaseHost = 
String firebaseAuth = 

void setup() {
  Serial.begin(9600);
  ser.begin(9600);
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print("    Welcome");
  lcd.setCursor(0, 1);
  lcd.print("       To        ");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("     AIR");
  lcd.setCursor(0, 1);
  lcd.print("QUALITY MONITOR");
  delay(3000);

  Firebase.begin(firebaseHost, firebaseAuth);

  ser.println("AT");
  delay(1000);
  ser.println("AT+GMR");
  delay(1000);
  ser.println("AT+CWMODE=3");
  delay(1000);
  ser.println("AT+RST");
  delay(5000);
  ser.println("AT+CIPMUX=1");
  delay(1000);

  String cmd = "AT+CWJAP=\"SSID\",\"PASSWORD\"";
  ser.println(cmd);
  delay(1000);
  ser.println("AT+CIFSR");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      WIFI");
  lcd.setCursor(0, 1);
  lcd.print("   CONNECTED");
}

void loop() {
  delay(1000);

  t = analogRead(A0);
  Serial.print("Airquality = ");
  Serial.println(t);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Air Qual: ");
  lcd.print(t);
  lcd.print(" PPM");

  lcd.setCursor(0, 1);
  if (t <= 500) {
    lcd.print("aer curat");
    Serial.print("aer curat ");
  } else if (t >= 500 && t <= 1000) {
    lcd.print("calitatea aerului este slaba");
    Serial.print("calitatea aerului este slaba");
  } else if (t >= 1000) {
    lcd.print("calitatea aerului este foarte slaba");
    Serial.print("calitatea aerului este foarte slaba");
  }

  delay(10000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  SENDING DATA");
  lcd.setCursor(0, 1);
  lcd.print("    TO CLOUD");

  sendToFirebase();
}

void sendToFirebase() {
  String sensorPath = "/air_quality";
  
  Firebase.setFloat(sensorPath + "/value", t);
  
  if (Firebase.failed()) {
    Serial.print("Firebase set failed: ");
    Serial.println(Firebase.error());
  } else {
    Serial.println("am uploadat");
  }

  delay(17000); 
}
