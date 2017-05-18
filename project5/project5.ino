/*
========================================
 PROYEK ROBOTIK KEREN DENGAN ARDUINO
 OLEH  FIRMANSYAH SAFTARI - 2015
 PROJECT-5 : ALARM DENGAN SENSOR GERAK
========================================
*/
 
int ledPin = 13;                
int inputPin = 2;               
int pirState = LOW;             
int val = 0;                    
int pinSpeaker = 10;           

void setup() {
  pinMode(ledPin, OUTPUT);      
  pinMode(inputPin, INPUT);     
  pinMode(pinSpeaker, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  val = digitalRead(inputPin);  
  if (val == HIGH) {            
    digitalWrite(ledPin, HIGH);  
    playTone(300, 160);
    delay(150);

    
    if (pirState == LOW) {
     
      Serial.println("Motion detected!");
      
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW); 
      playTone(0, 0);
      delay(300);    
      if (pirState == HIGH){
      
      Serial.println("Motion ended!");
      
      pirState = LOW;
    }
  }
}

void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
