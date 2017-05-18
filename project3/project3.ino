/*
========================================
 PROYEK ROBOTIK KEREN DENGAN ARDUINO
 OLEH  FIRMANSYAH SAFTARI - 2015
 PROJECT-3 : PENGUKUR JARAK ULTRASONIK
 ========================================
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int pingPin = 7;
int inPin = 8;

//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop()
{
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(cm);
  lcd.print("cm");
  delay(200); 
  if (cm < 10) 
  {
    lcd.setCursor(0, 1);
    lcd.print("SUDAH SANGAT DEKAT");
    delay(100); 
  } 
  else {
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
