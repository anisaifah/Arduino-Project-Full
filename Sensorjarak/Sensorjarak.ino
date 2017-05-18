/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

// include the library code:
#include <LiquidCrystal.h>

#define echoPin 2             //inisialisai echo pin pada port 6
#define initPin 3             // inisialisasi triger pin pada port 5
unsigned long pulseTime = 0;  // variabel untuk membaca pulsa

// inisialisai LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
 //Setup LCD
 Serial.begin(9600);
 lcd.begin(16, 2);
 Serial.begin(9600);

 // setting output pada pin initPin
 pinMode(initPin, OUTPUT);
 //setting input untuk pin Echo
 pinMode(echoPin, INPUT);
}

void loop() {
 digitalWrite(initPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(initPin, LOW);

 pulseTime = pulseIn(echoPin, HIGH);

 lcd.setCursor(0,0);
 lcd.print("Jarak = ");
 lcd.print(pulseTime / 58, DEC);
 Serial.print(pulseTime / 58, DEC);
 Serial.print(" Cm \n");
 lcd.print(" cm");
 lcd.setCursor(0,1);
 lcd.print(" Sensor Jarak");

 delay(100);
 lcd.clear();
}
