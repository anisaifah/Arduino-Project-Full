/*
========================================
PROYEK ROBOTIK KEREN DENGAN ARDUINO
OLEH  FIRMANSYAH SAFTARI - 2015
PROJECT-1 : THERMOMETER DIGITAL
========================================
*/

#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x27,20,4);

int tempPin = 0;
float tempC;
int reading;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
}

void loop() {
  int reading = analogRead(tempPin);
  tempC = reading / 9.31;
  lcd.setCursor(0, 1);
  lcd.clear(); lcd.setCursor(0, 0);
  lcd.print("Suhu saat ini:");
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print(" Celsius");
  delay(1000);
}
