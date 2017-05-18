/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {9,8,7,6};
byte colPins[cols] = {5,4,3,2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);


void setup()
{
  Serial.begin(9600);
  //lcd.init();                      // initialize the lcd 
  //// Print a message to the LCD.
  //lcd.backlight();
  //lcd.setCursor(3,0);
  //lcd.print("You Pressed:");

}

void loop()
{
  char keys[4];
  char key = keypad.getKey();
  
  if (int(key)!=0) {
    keys[0]=key;
    Serial.print(keys[0]);
    char key = keypad.getKey();
    if(key=='2'){
       keys[1]=key;
       Serial.print(key);
       char key = keypad.getKey();
       if(key=='3'){
         keys[3]=key;
         Serial.print(key);
         char key = keypad.getKey();
         if(key=='4'){
           keys[4]=key;
           Serial.print(key);
           Serial.print("Terbuka");  
         }
       } 
    }
  }
  
  if(key='*'){
    
  }
  
}
