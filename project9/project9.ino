
/*
========================================
 PROYEK ROBOTIK KEREN DENGAN ARDUINO
 OLEH  FIRMANSYAH SAFTARI - 2015
 PROJECT-9 : ANIMATRONIC EYES
 ========================================
*/

#include <Servo.h>  

const int servo1 = 10; 
const int servo2 = 11; 
const int joyH = 4; 
const int joyV = 0; 
int servoVal1; 
int servoVal2;  
Servo myservo1; 
Servo myservo2; 

void setup() { 
  myservo1.attach(servo1); 
  myservo2.attach(servo2); 
}  

void loop() { 
  servoVal1 = analogRead(joyH);               
  servoVal1 = map(servoVal1, 0, 1023, 30, 170); 
  servoVal1 = servoVal1+20;     
  myservo2.write(servoVal1); 
  servoVal2 = analogRead(joyV);                
  servoVal2 = map(servoVal2, 0, 1023, 30, 160);
  servoVal2 = servoVal2+20;     
  myservo1.write(servoVal2);
  delay(15); 
}  

