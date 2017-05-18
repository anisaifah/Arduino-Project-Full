/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include <Servo.h>
#include <Wire.h>
#include <Keypad.h>

//constants for LEDs
int greenLED = 12;
int redLED = 13;

//set our code
char* pinnya = "1234";
int posisi = 0;
int i;

//define the keypad
const byte rows = 4;
const byte cols = 3;

char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[rows] = {11,10,9,8};
byte colPins[cols] = {7,6,5};
Servo svr;
int pos;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup()
{
  Serial.begin(9600);   
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  svr.attach(1);
  svr.write(0);
  
}

void loop()
{  
  char key = keypad.getKey();
  Serial.print(key);
  Serial.print("\n");
  if (int(key) != 0) 
  {
    if (key == pinnya[posisi])
      {
        ++posisi;
        if (posisi == 4)
        {
          unlockDoor();
          posisi = 0;
        }
      }
     else if (key =='*')
      {
         posisi=0;
      } 
      else {
        invalidCode();
        posisi = 0;
      }    
  }
  svr.write(0);
  delay(1);
}

void invalidCode()
{
  digitalWrite(redLED, HIGH);
  delay(5000);
  digitalWrite(redLED, LOW);
}

void unlockDoor()
{
  svr.write(90);
  digitalWrite(greenLED, HIGH);
  delay(5000);
  digitalWrite(greenLED, LOW);
  svr.write(0);
}
