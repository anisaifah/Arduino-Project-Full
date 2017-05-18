/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include <ESP8266WiFi.h>

const char* ssid = "Osiloscop";
const char* password = "janganmakane201";

int kamartidur = 16;
int kamarmandi = 5;
int kamartengah = 4;
int kamarkeluarga = 0;
int depanrumah = 2;
int garasi = 14;

int valuekamarmandi = LOW;
int valuekamartidur = LOW;
int valuekamartengah = LOW;
int valuekamarkeluarga = LOW;
int valuedepanrumah = LOW;
int valuegarasi = LOW;

WiFiServer server(80);


void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(kamartidur,OUTPUT);
  pinMode(kamarmandi,OUTPUT);
  pinMode(kamartengah,OUTPUT);
  pinMode(kamarkeluarga,OUTPUT);
  pinMode(depanrumah,OUTPUT);
  pinMode(garasi,OUTPUT);

  Serial.println();
  Serial.println("Menghubungkan menuju : ");
  Serial.print(ssid);

  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("Terhubung Jaringan");

  server.begin();
  Serial.println("Memulai Server");

  Serial.println("Gunakan Alamat ini untuk mengkontrol : http://");
  Serial.print(WiFi.localIP());
  Serial.print("/");

}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("Klient Baru");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/LED=ON_kamarmandi") != -1)  {
    digitalWrite(kamarmandi, HIGH);
    valuekamarmandi = HIGH;
  }
  if (request.indexOf("/LED=OFF_kamarmandi") != -1)  {
    digitalWrite(kamarmandi, LOW);
    valuekamarmandi = LOW;
  }

    if (request.indexOf("/LED=ON_kamartidur") != -1)  {
    digitalWrite(kamartidur, HIGH);
    valuekamartidur = HIGH;
  }
  if (request.indexOf("/LED=OFF_kamartidur") != -1)  {
    digitalWrite(kamartidur, LOW);
    valuekamartidur = LOW;
  }

    if (request.indexOf("/LED=ON_kamartengah") != -1)  {
    digitalWrite(kamartengah, HIGH);
    valuekamartengah = HIGH;
  }
  if (request.indexOf("/LED=OFF_kamartengah") != -1)  {
    digitalWrite(kamartengah, LOW);
    valuekamartengah = LOW;
  }

    if (request.indexOf("/LED=ON_kamarkeluarga") != -1)  {
    digitalWrite(kamarkeluarga, HIGH);
    valuekamarkeluarga = HIGH;
  }
  if (request.indexOf("/LED=OFF_kamarkeluarga") != -1)  {
    digitalWrite(kamarkeluarga, LOW);
    valuekamarkeluarga = LOW;
  }

    if (request.indexOf("/LED=ON_depanrumah") != -1)  {
    digitalWrite(depanrumah, HIGH);
    valuedepanrumah = HIGH;
  }
  if (request.indexOf("/LED=OFF_depanrumah") != -1)  {
    digitalWrite(depanrumah, LOW);
    valuedepanrumah = LOW;
  }

    if (request.indexOf("/LED=ON_garasi") != -1)  {
    digitalWrite(garasi, HIGH);
    valuegarasi = HIGH;
  }
  if (request.indexOf("/LED=OFF_garasi") != -1)  {
    digitalWrite(garasi, LOW);
    valuegarasi = LOW;
  }

 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Status Lampu Kamar Tidur : ");
 
  if(valuekamartidur == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }

  client.println("<br><br>");
  client.println("Status Lampu Kamar Mandi : ");
  if(valuekamarmandi == HIGH) {
    client.print("On");
  } else if(valuekamarmandi == LOW)  {
    client.print("Off");
  }

  client.println("<br><br>");
  client.println("Status Lampu Kamar Tengah : ");
  if(valuekamartengah == HIGH) {
    client.print("On");
  } else if(valuekamartengah == LOW) {
    client.print("Off");
  }

  client.println("<br><br>");
  client.println("Status Lampu Kamar Keluarga : ");
  if(valuekamarkeluarga == HIGH) {
    client.print("On");
  } else if(valuekamarkeluarga == LOW) {
    client.print("Off");
  }

  client.println("<br><br>");
  client.println("Status Lampu Depan Rumah : ");
  if(valuedepanrumah == HIGH) {
    client.print("On");
  } else if(valuedepanrumah == LOW) {
    client.print("Off");
  }

  client.println("<br><br>");
  client.println("Status Lampu Garasi : ");
  if(valuegarasi == HIGH) {
    client.print("On");
  } else if(valuegarasi == LOW) {
    client.print("Off");
  }
  
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON_kamarmandi\"\"><button> Lampu Kamar Mandi On </button></a>");
  client.println("<a href=\"/LED=OFF_kamarmandi\"\"><button> Lampu Kamar Mandi off </button></a><br />");
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON_kamartidur\"\"><button> Lampu Kamar Tidur On </button></a>");
  client.println("<a href=\"/LED=OFF_kamartidur\"\"><button> Lampu Kamar Tidur off </button></a><br />");
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON_kamartengah\"\"><button> Lampu Kamar Tengah On </button></a>");
  client.println("<a href=\"/LED=OFF_kamartengah\"\"><button> Lampu Kamar Tengah off </button></a><br />");
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON_kamarkeluarga\"\"><button> Lampu Kamar Keluarga On </button></a>");
  client.println("<a href=\"/LED=OFF_kamarkeluarga\"\"><button> Lampu Kamar Keluarga off </button></a><br />");
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON_depanrumah\"\"><button> Lampu Depan On </button></a>");
  client.println("<a href=\"/LED=OFF_depanrumah\"\"><button> Lampu Depan off </button></a><br />");
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON_garasi\"\"><button> Lampu garasi On </button></a>");
  client.println("<a href=\"/LED=OFF_garasi\"\"><button> Lampu garasi off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
