/*
========================================
 PROYEK ROBOTIK KEREN DENGAN ARDUINO
 OLEH  FIRMANSYAH SAFTARI - 2015
 PROJECT-7B : REMOTE CONTROL IR
========================================
 
PEMASANGAN SENSOR IR
 Pin 1 GND --> PIN GND ARDUINO
 Pin 2 VCC --> PIN +5V ARDUINO
 Pin 3 DATA --> PIN DIGITAL 4 ARDUINO
 
PEMASANGAN LED RGB
Pin 1 RED --> PIN DIGITAL 9 ARDUINO
Pin 2 GND --> PIN GND ARDUINO
Pin 3 GREEN --> PIN DIGITAL 10 ARDUINO

Contoh Code IR remote
1 16738455
2 16750695
3 16756815
4 16724175
5 16718055
6 16743045
7 16716015
8 16726215
9 16734885
0 16730805
*/

#include <IRremote.h>

int IRpin = 4;  // pin for the IR sensor
int LED1 = 9;    // LED RED
int LED2 = 10;    // LED GREEN
int LED3 = 11;    // LED BLUE
IRrecv irrecv(IRpin);
decode_results results;

boolean LEDon = true; // initializing LEDon as true

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

}


void loop()
{

  if (irrecv.decode(&results))
  {

    irrecv.resume();   // Receive the next value
  }

  switch (results.value)
  {

    case 16738455:
      digitalWrite(LED1, HIGH); // Turn ON RED
      delay(1000);
      break;

    case 16750695:
      digitalWrite(LED2, HIGH); // Turn ON GREEN
      delay(1000);
      break;

    case 16756815:
      digitalWrite(LED3, HIGH); // Turn ON BLUE
      delay(1000);

      break;

    default:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
  }
}

