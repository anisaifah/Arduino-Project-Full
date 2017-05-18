/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include <SoftwareSerial.h>
#define DEBUG true

SoftwareSerial esp8266(10,11); //RX TX
/*
 * Pada Proyek ini menggunakan ESP8266 ESP-1 yang berkomunikasi dengan socket RX an TX
 * Letak Pin RX pada arduino di pin 10, dan TX di pin 11
 * 
 * Pada Project ini menggunakan LED sebagai output yang dipasang pada Arduino Pin :
 * 2,3,4,5
 */

void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600);

  pinMode(2,OUTPUT); // Pin 2 sebagai output
  digitalWrite(2,LOW);

  pinMode(3,OUTPUT); // Pin 3 sebagai output
  digitalWrite(3,LOW);

  pinMode(4,OUTPUT); // Pin 4 sebagai output
  digitalWrite(4,LOW);

  pinMode(5,OUTPUT); // Pin 5 sebagai output
  digitalWrite(5,LOW);
  
  pinMode(7,OUTPUT);
  digitalWrite(7,LOW);
 
  kirimPerintah("AT+RST\r\n",2000,DEBUG);                                   // Digunakan untuk mereset koneksi dalam ESP
  kirimPerintah("AT+CWMODE=1\r\n",1000,DEBUG);                              // Merubah Mode dalam ESP menjadi mode 1 yaitu mode server
 
  kirimPerintah("AT+CWJAP=\"IOT Apapunada\",\"smartiot\"\r\n",3000,DEBUG);  //IOT Apapunada merupakan SSID Wifi yang digunakan dan smartiot merupakan password wifi
  delay(10000);
  kirimPerintah("AT+CIFSR\r\n",1000,DEBUG);       
  kirimPerintah("AT+CIPMUX=1\r\n",1000,DEBUG);
  kirimPerintah("AT+CIPSERVER=1,80\r\n",1000,DEBUG);
  Serial.println("sudah siap!"); 
 }
void loop()
{
  if(esp8266.available())
  {
   if(esp8266.find("+IPD,"))                            // Menentukan apakah perintah yang diberikan ada
    {
     digitalWrite(7,HIGH);
     delay(200);
     digitalWrite(7,LOW);
     delay(1000);
     int connectionId = esp8266.read()-48;              // Dikurangi 48 karena merujuk pada perhitungan untuk merubah kedalam bilangan bulat
     esp8266.find("pin=");                              // Menentukan pin berapa yang akan dieksekusi
     int nomorPin = (esp8266.read()-48);                // Merubah string nomor pin menjadi bilagan bulat
     Serial.print(nomorPin);
     digitalWrite(nomorPin, !digitalRead(nomorPin));    // Mengeksekusi PIN
     String closeCommand = "AT+CIPCLOSE=";              // Menghentikan service
     closeCommand+=connectionId;
     closeCommand+="\r\n";
     kirimPerintah(closeCommand,1000,DEBUG);
    }
  }
}
String kirimPerintah(String perintah, const int timeout, boolean debug) // Kirim perintah digunakan untuk memberikan hasil di Serial print
{
    String response = "";
    esp8266.print(perintah);
    long int time = millis();
    while( (time+timeout) > millis()) 
    {
      while(esp8266.available()) 
      {
        char c = esp8266.read();
        response+=c;
      }
    }
    if(debug) {
      Serial.print(response);
    }
    return response;
}
