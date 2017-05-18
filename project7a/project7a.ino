/*
========================================
 PROYEK ROBOTIK KEREN DENGAN ARDUINO
 OLEH  FIRMANSYAH SAFTARI - 2015
 PROJECT-7A : PENERIMA KODE REMOTE IR
 ========================================
 
PEMASANGAN SENSOR IR
 Pin 1 to Vout --> PIN 11 ARDUINO
 Pin 2 to GND --> PIN GND ARDUINO
 Pin 3 to Vcc --> PIN +5V ARDUINO
 
 */

#include <IRremote.h>

int IRpin = 4;
IRrecv irrecv(IRpin);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, DEC); // Print the Serial 'results.value'
    irrecv.resume();   // Receive the next value
  }
}

