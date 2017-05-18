/*
========================================
 PROYEK ROBOTIK KEREN DENGAN ARDUINO
 OLEH  FIRMANSYAH SAFTARI - 2015
 PROJECT-10 : ANIMATRONIC HAND ROBOTIC
 ========================================

cable info:
SERVOS:
SERVO 1 - D3 : 1st finger servo (thumb)
SERVO 2 - D5 : 2nd finger servo (index finger)
SERVO 3 - D6 : 3rd finger servo (middle finger)
SERVO 4 - D9 : 4th finger servo (ring finger)
SERVO 5 - D10 : 5th finger servo (little finger)
SERVO 6 - D11 : Elbow servo
SERVO 7 - D12 : Hand wrist X-servo
SERVO 8 - D13 : Hand wrist Y-servo

FLEX SENSORS:
FLEX 1 - A7 : 1st finger servo (thumb)
FLEX 2 - A6 : 2nd finger servo (index finger)
FLEX 3 - A3 : 3rd finger servo (middle finger)
FLEX 4 - A2 : 4th finger servo (ring finger)
FLEX 5 - A1 : 5th finger servo (little finger)
FLEX 6 - A0 : Elbow servo

IMU-6050:
1 - VCC - BLACK (3.3v)
2 - GND - BROWN (GND)
3 - SCL - RED (D5)
4 - SDA - ORANGE (D4)


*/

#include <Servo.h>
#include <Wire.h>


Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo yservo;
Servo xservo;


#include "Kalman.h"
Kalman kalmanX;
Kalman kalmanY;

uint8_t IMUAddress = 0x68;

/* IMU Data */
int16_t accX;
int16_t accY;
int16_t accZ;
int16_t tempRaw;
int16_t gyroX;
int16_t gyroY;
int16_t gyroZ;

int moveX;
int moveY;
int mapX;
int mapY;
int correctionX;
int correctionY;

double accXangle; 
double accYangle;
double temp;
double gyroXangle = 9; 
double gyroYangle = 180;
double compAngleX = 90; 
double compAngleY = 90;
double kalAngleX; 
double kalAngleY;

uint32_t timer;

int pos1=0;
int pos2=0;
int pos3=0;
int pos4=0;
int pos5=0;
int pos6=0;

int flex1=0;
int flex2=0;
int flex3=0;
int flex4=0;
int flex5=0;
int flex6=0;

void setup()
{
myservo1.attach(3);    // 1st finger servo (thumb)
myservo2.attach(5);    // 2nd finger servo (index finger)
myservo3.attach(6);    // 3rd finger servo (middle finger)
myservo4.attach(9);    // 4th finger servo (ring finger)
myservo5.attach(10);   // 5th finger servo (little finger)
myservo6.attach(11);   // elbow servo
xservo.attach(12);    // hand wrist X-servo
yservo.attach(13);    // hand wrist Y-servo

  Wire.begin();  
  i2cWrite(0x6B,0x00); 
  if(i2cRead(0x75,1)[0] != 0x68) 
  { 
    Serial.print(F("MPU-6050 with address 0x"));
    Serial.print(IMUAddress,HEX);
    Serial.println(F(" is not connected"));
    while(1);
  }      
  kalmanX.setAngle(90); // Set starting angle
  kalmanY.setAngle(90);
  timer = micros();
    
Serial.begin(9600);
}

void loop()
{

flex1 = analogRead(A7);      // Read 1st finger flex sensor (thumb)
flex2 = analogRead(A6);      // 2nd finger flex sensor (index finger)
flex3 = analogRead(A3);      // 3rd finger flex sensor (middle finger)
flex4 = analogRead(A2);      // 4th finger flex sensor (ring finger)
flex5 = analogRead(A1);      // 5th finger flex sensor (little finger)
flex6 = analogRead(A0);      // Elbow flex sensor


  uint8_t* data = i2cRead(0x3B,14);  
  accX = ((data[0] << 8) | data[1]);
  accY = ((data[2] << 8) | data[3]);
  accZ = ((data[4] << 8) | data[5]);  
  tempRaw = ((data[6] << 8) | data[7]);  
  gyroX = ((data[8] << 8) | data[9]);
  gyroY = ((data[10] << 8) | data[11]);
  gyroZ = ((data[12] << 8) | data[13]);
  
  accYangle = (atan2(accX,accZ)+PI)*RAD_TO_DEG;
  accXangle = (atan2(accY,accZ)+PI)*RAD_TO_DEG;    
  
  double gyroXrate = (double)gyroX/131.0;
  double gyroYrate = -((double)gyroY/131.0);
  gyroXangle += gyroXrate*((double)(micros()-timer)/1000000); 
  gyroYangle += gyroYrate*((double)(micros()-timer)/1000000);
  gyroXangle += kalmanX.getRate()*((double)(micros()-timer)/1000000); 
  gyroYangle += kalmanY.getRate()*((double)(micros()-timer)/1000000);
  
  compAngleX = (0.93*(compAngleX+(gyroXrate*(double)(micros()-timer)/1000000)))+(0.07*accXangle); 
  compAngleY = (0.93*(compAngleY+(gyroYrate*(double)(micros()-timer)/1000000)))+(0.07*accYangle);  
  
  kalAngleX = kalmanX.getAngle(accXangle, gyroXrate, (double)(micros()-timer)/1000000); 
  kalAngleY = kalmanY.getAngle(accYangle, gyroYrate, (double)(micros()-timer)/1000000);
  timer = micros();
  

mapX = map(kalAngleX, 0, 200, 0, 179);
mapY = map(kalAngleY, 0, 180, 0, 179);
  
    correctionX = 25;
    correctionY = 52;
  
    moveX = 270 - (kalAngleX) + correctionX; 
    moveY = 200 - (kalAngleY) + correctionY;

pos1=map(flex1,870,800,0,180);
pos2=map(flex2,870,800,0,180);
pos3=map(flex3,870,800,0,180);
pos4=map(flex4,820,800,0,180);
pos5=map(flex5,870,800,0,180);
pos6=map(flex6,870,800,0,180);


myservo1.write(pos1*1.5);      // 1st finger servo (thumb)
myservo2.write(pos2*1.5);     // 2nd finger servo (index finger)
myservo3.write(pos3*1.5);     // 3rd finger servo (middle finger)
myservo4.write(pos4*1.5);     // 4th finger servo (ring finger)
myservo5.write(pos5*1.5);     // 5th finger servo (little finger)
myservo6.write(pos6*1.5);     // Elbow Servo
xservo.write(moveX);         // Hand wrist X-Servo
yservo.write(moveY);         // Hand wrist Y-Servo
delay(15); 
}

void i2cWrite(uint8_t registerAddress, uint8_t data){
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t* i2cRead(uint8_t registerAddress, uint8_t nbytes) {
  uint8_t data[nbytes];  
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  Wire.endTransmission(false);
  Wire.requestFrom(IMUAddress, nbytes);
  for(uint8_t i = 0; i < nbytes; i++)
    data[i] = Wire.read();
  return data;
} 

