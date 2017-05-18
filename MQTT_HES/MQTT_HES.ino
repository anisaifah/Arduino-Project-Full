/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include "PubSubClient.h"
#include <ESP8266WiFi.h>

// Mendefinisikan konektivitas yang akan didefinisikan dalam MQTT
#define MQTT_SERVER "Alamat IP"            // Alamat IP yang didapatkan dari broker
const char* ssid = "SSID WIFI";            // Nama WiFi spot yang ada, harus sama dengan Wifi spot broker
const char* password = "PASS WIFI";   // pasword Wifi Spot

char* HesLight = "/HES/light1";             // Topik yang diberikan untuk MQTT

// Inisialisasi penggunaan pin pada NodeMCU untuk LED
int const led1 = 16;        
int const led2= 5;
int const led3= 4;
int const led4= 0;
int const suhu=A0;


void callback(char* topic, byte* payload, unsigned int length);

WiFiClient wifiClient;
PubSubClient client(MQTT_SERVER, 1883, callback, wifiClient);

// Inisialisasi permulaan program yang harus dilakukan unttuk memberikan start pada awal program
void setup() {
  // memberikan Mode pin output pada pin yang diset pada NodeMCU
  pinMode(led1,OUTPUT);   
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(suhu,INPUT);

  //Memberikan Inisial awal pada pin pada kassus ini diset LOW atau mati
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  
  Serial.begin(115200);           //Menggunakan Serial 115200 sebagai Serial Debug
  delay(100);
  WiFi.begin(ssid, password);     // Memcoba menghubungkan dengan Wifi Spot
  reconnect();
  delay(2000);
}

//Badan program yang akan terus menerus diulang
void loop(){
  if (!client.connected() && WiFi.status() == 3) {
    reconnect();
    }
  client.loop();
  delay(10); 
}

// Prosedur ynag digunakan untuk mengeksekusi perintah yang diberikan oleh broker
void callback(char* topic, byte* payload, unsigned int length) {
  String topicStr = topic;              
  Serial.println("Memanggil Ulang.");
  Serial.print("Topic\k: ");
  Serial.println(topicStr);
  if (payload[0]=='1'){                                     // Membaca pesan dari payload, apakah sesuai
    digitalWrite(led1, HIGH);                               // Mengeksekusi perintah jika payload bernilai benar
    client.publish("/HES/confirm", "Lampu Merah Menyala");  // NodeMCU akan memberikan balikan kepada broker
  }
  if (payload[0]=='2'){
    digitalWrite(led1, LOW);
    client.publish("/HES/confirm", "Lampu Merah Mati");
  }
  if (payload[0]=='3'){
    digitalWrite(led2, HIGH);
    client.publish("/HES/confirm", "Lampu Hijau Menyala");
  }
  if (payload[0]=='4'){
    digitalWrite(led2, LOW);
    client.publish("/HES/confirm", "Lampu Hijau Mati");
  }
  if (payload[0]=='5'){
    digitalWrite(led3, HIGH);
    client.publish("/HES/confirm", "Lampu Kuning Menyala");
  }
  if (payload[0]=='6'){
    digitalWrite(led3, LOW);
    client.publish("/HES/confirm", "Lampu Kinung Mati");
  }
  if (payload[0]=='7'){
    digitalWrite(led4, HIGH);
    client.publish("/HES/confirm", "Lampu Biru Menyala");
  }
  if (payload[0]=='8'){
    digitalWrite(led4, LOW);
    client.publish("/HES/confirm", "Lampu Biru Mati");
  }
}

// Prosedur yang digunakan untuk menghubungkan menuju broker
void reconnect() {
  if(WiFi.status() != WL_CONNECTED){
      Serial.print("Menguhbungkan Ke ");
      Serial.println(ssid);
      while (WiFi.status() != WL_CONNECTED) {
          digitalWrite(LED_BUILTIN,HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN,LOW);
        }
      Serial.println("");
      Serial.println("WiFi terhubung");  
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }
  if(WiFi.status() == WL_CONNECTED){
      while (!client.connected()) {
          Serial.print("Menunggu koneksi MQTT ");
          String clientName;
          clientName += "esp8266-";
          uint8_t mac[6];
          WiFi.macAddress(mac);
          clientName += macToStr(mac);
          if (client.connect((char*) clientName.c_str())) {
              Serial.print("\tMTQQ terhubung");
              client.subscribe(HesLight);
          }
          else{Serial.println("\tTidak Terhubung."); abort();}
      }
  }
}

//Fungsi untuk mengembalikan mac dari broker
String macToStr(const uint8_t* mac){

  String result;

  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);

    if (i < 5){
      result += ':';
    }
  }

  return result;
}
