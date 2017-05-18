

/*
========================================
 PROYEK ROBOTIK KEREN DENGAN ARDUINO
 OLEH  FIRMANSYAH SAFTARI - 2015
 PROJECT-6 : ALAT KONTROL TEKS DENGAN PERINTAH SUARA
 ========================================
*/
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x27,20,4);

SoftwareSerial BT(11, 10); //TX, RX Bluetooth Communication

String voice;

void setup() {
lcd.init();
lcd.backlight();
BT.begin(9600);
lcd.begin(20,4);
  Serial.begin(9600);
}

void loop() {
  while (BT.available()){  //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = BT.read(); //Conduct a serial read
    if (c == '#') {
      break;
    } //Exit the loop when the # is detected after the word
    voice += c; //Shorthand for voice = voice + c
  }
  lcd.print(voice); // ------Print a message to the LCD.
  delay(5000);
  lcd.clear();
  voice=""; //Reset the variable after initiating
}

