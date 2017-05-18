/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include "PubSubClient.h"
#include <ESP8266WiFi.h>

#define MQTT_SERVER "IP MQTT"
const char* ssid = "SSID NAME";
const char* password = "SSID PASSWORD";

char* lightTopic = "/HES/light1";
char* tempTopic = "/HES/temp";
char* redTopic = "/HES/red";
char* grenTopic ="/HES/green";
char* yelTopic = "/HES/yel";

int const kamartidur = 16;
int const kamarmandi = 0;
int const ruangtengah = 4;
int const ruangtv = 5;
int const ruangdepan = 14;
int const parkiran = 12;
int const lap = A0;

void lamp();
void callback(char* topic, byte* payload, unsigned int length);

WiFiClient wifiClient;
PubSubClient client(MQTT_SERVER, 1883, callback, wifiClient);

void setup() {
  pinMode(kamarmandi,OUTPUT);
  pinMode(kamartidur,OUTPUT);
  pinMode(ruangtengah,OUTPUT);
  pinMode(ruangtv,OUTPUT);
  pinMode(ruangdepan,OUTPUT);
  pinMode(parkiran,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(kamarmandi,LOW);
  digitalWrite(kamartidur,LOW);
  digitalWrite(ruangtengah,LOW);
  digitalWrite(ruangtv,LOW);
  digitalWrite(ruangdepan,LOW);
  digitalWrite(parkiran,LOW);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
  delay(100);
  WiFi.begin(ssid, password);
  reconnect();
  delay(2000);
}

void loop(){
  lamp();
  if (!client.connected() && WiFi.status() == 3) {
    reconnect();
    }
  client.loop();
  delay(10); 
}

void lamp(){
  if(analogRead(lap)<7)
  {
    digitalWrite(parkiran,HIGH);
    delay(300);
    digitalWrite(parkiran,LOW);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String topicStr = topic; 
  Serial.println("Callback update.");
  Serial.print("Topic: ");
  Serial.println(topicStr);
  if (payload[0]=='1'){
    digitalWrite(kamartidur, HIGH);
    client.publish("/HES/confirm", "Kamar Tidur On");
  }
  if (payload[0]=='2'){
    digitalWrite(kamartidur, LOW);
    client.publish("/HES/confirm", "Kamar Tidur Off");
  }
  if (payload[0]=='3'){
    digitalWrite(kamarmandi, HIGH);
    client.publish("/HES/confirm", "Kamar Mandi On");
  }
  if (payload[0]=='4'){
    digitalWrite(kamarmandi, LOW);
    client.publish("/HES/confirm", "Kamar Mandi Off");
  }
  if (payload[0]=='5'){
    digitalWrite(ruangtengah, HIGH);
    client.publish("/HES/confirm", "Ruang Tengah On");
  }
  if (payload[0]=='6'){
    digitalWrite(ruangtengah, LOW);
    client.publish("/HES/confirm", "Ruang Tengah Off");
  }
  if (payload[0]=='7'){
    digitalWrite(ruangtv, HIGH);
    client.publish("/HES/confirm", "Ruang Tengah On");
  }
  if (payload[0]=='8'){
    digitalWrite(ruangtv, LOW);
    client.publish("/HES/confirm", "Ruang Tengah Off");
  }
  if (payload[0]=='9'){
    digitalWrite(ruangdepan, HIGH);
    client.publish("/HES/confirm", "Ruang Depan On");
  }
  if (payload[0]=='A'){
    digitalWrite(ruangdepan, LOW);
    client.publish("/HES/confirm", "Ruang Depan Off");
  }
  if (payload[0]=='B'){
    digitalWrite(parkiran, HIGH);
    client.publish("/HES/confirm", "Parkiran On");
  }
  if (payload[0]=='C'){
    digitalWrite(parkiran, LOW);
    client.publish("/HES/confirm", "Parkiran Off");
  }
  if(payload[0] == 'D'){
    digitalWrite(LED_BUILTIN, HIGH);
    client.publish("/HES/confirm", "Light On");

  }
  if (payload[0] == 'E'){
    digitalWrite(LED_BUILTIN, LOW);
    client.publish("/HES/confirm", "Light Off");
  }
}

void reconnect() {
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Connecting to ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_BUILTIN,HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN,LOW);
      }
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  if(WiFi.status() == WL_CONNECTED){
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      String clientName;
      clientName += "esp8266-";
      uint8_t mac[6];
      WiFi.macAddress(mac);
      clientName += macToStr(mac);
      if (client.connect((char*) clientName.c_str())) {
        Serial.print("\tMTQQ Connected");
        client.subscribe(lightTopic);
        client.subscribe(tempTopic);
        client.subscribe(redTopic);
        client.subscribe(grenTopic);
        client.subscribe(yelTopic);
      }
      else{Serial.println("\tFailed."); abort();}
    }
  }
}

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
