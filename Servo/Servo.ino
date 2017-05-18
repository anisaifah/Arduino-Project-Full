/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);

Servo myservo; 
int pos = 0;    

void setup()
{
    myservo.attach(7); 
} 

void loop()
{
  for(pos = 0; pos < 45; pos++)  
  {                                  
    myservo.write(pos);              
    delay(15);                       
  }
  for(pos = 45; pos < 90; pos++)  
  {                                  
    myservo.write(pos);              
    delay(15);                       
  }
  for(pos = 90; pos < 135; pos++)  
  {                                  
    myservo.write(pos);              
    delay(15);                       
  }
  for(pos = 135; pos < 180; pos++)  
  {                                  
    myservo.write(pos);              
    delay(15);                       
  }
  for(pos = 180; pos>=1; pos-=1)    
  {
    myservo.write(pos);              
    delay(15);                       
  }
}
