/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include <LiquidCrystal.h>;

LiquidCrystal lcd(12,11, 5, 4, 3, 2);
// deklarasi variabel
float tempC;

void setup() {
    lcd.begin(16, 2);
    lcd.print("Temperatur:");
}

void loop() {
  lcd.setCursor(0, 1);
  tempC = (500*analogRead(A0))/1024;
  lcd.print(analogRead(A0));
  // Serial.println(tempC);
  if(tempC>=30) //jika temperatur >=30 derajat
    digitalWrite(13,HIGH);
  else digitalWrite(13,LOW);
  delay(1000); // berhenti 2 detik untuk menunggu perubahan temperatur
} 
