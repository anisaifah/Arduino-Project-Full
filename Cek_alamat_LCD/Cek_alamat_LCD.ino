#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


// definisi untuk I2C LCD Backpack
#define I2C_ADDR       0x27
#define BACKLIGHT_PIN  3
#define EN_PIN         2
#define RW_PIN         1
#define RS_PIN         0
#define D4_PIN         4
#define D5_PIN         5
#define D6_PIN         6
#define D7_PIN         7
#define echoPin 5
#define iniPin 6
unsigned long pulseTime = 0;

LiquidCrystal_I2C lcd(I2C_ADDR, EN_PIN, RW_PIN, RS_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  delay(1000);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);  // menggunakan lcd 16 kolom dan 2 baris
  pinMode(iniPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop()
{
  digitalWrite(iniPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(iniPin,LOW);
  pulseTime = pulseIn(echoPin,HIGH);
  lcd.setCursor(0,0);
  lcd.print("Jarak = ");
  lcd.print(pulseTime / 58, DEC);
  Serial.println(pulseTime / 58, DEC);
  lcd.print(" cm");
  lcd.setCursor(0,1);
  lcd.print(" Sensor Jarak");
  
  delay(100);
  lcd.clear();
}
