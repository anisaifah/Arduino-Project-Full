/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include <AnalogMatrixKeypad.h>
#include <AddicoreRFID.h>
#include <SPI.h>

#define	uchar	unsigned char
#define	uint	unsigned int
#define buz 9
uchar serNumA[5];

uchar fifobytes;
uchar fifoValue;

AddicoreRFID myRFID;

const int chipSelectPin = 15;
const int NRSTPD = 4;

#define MAX_LEN 16

bool masuk=false;
int kode=0;
char kodeinput[4];
AnalogMatrixKeypad AnMatrixKeypad(4);

void setup() {                
   Serial.begin(115200);                       
   SPI.begin();
   pinMode(buz,OUTPUT);
   pinMode(4,INPUT);
   pinMode(chipSelectPin,OUTPUT);             
   digitalWrite(chipSelectPin, HIGH);        
   pinMode(NRSTPD,OUTPUT);                   
   digitalWrite(NRSTPD, HIGH);
   myRFID.AddicoreRFID_Init();  
}

void loop()
{
  	uchar i, tmp, checksum1;
	uchar status;
        uchar str[MAX_LEN];
        uchar RC_size;
        uchar blockAddr;
        String mynum = "";

        str[1] = 0x4400;
	status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);
        if(masuk){
           input();
        }	
	if (status == MI_OK)
	{
          Serial.println("RFID Di Deteksi");
    	    Serial.print(str[0],BIN);
          Serial.print(" , ");
    	    Serial.print(str[1],BIN);
            Serial.println(" ");
            clearpass();
            kode=0;
	}

	status = myRFID.AddicoreRFID_Anticoll(str);
	if (status == MI_OK)
	{           
            if((str[0] == 189)|| (str[0] == 136))
            {
                tune();
                Serial.print("Hello Resa!\n");
                Serial.print("Silahkan Masukkan PIN\n");
                masuk = true;
            } else{
                masuk = false;
            }
            Serial.println();
            delay(1000);
	}
		
        myRFID.AddicoreRFID_Halt();           
}

void input(){
    char Key = AnMatrixKeypad.readKey();
    if(Key != KEY_NOT_PRESSED){
    Serial.println(Key);
    kodeinput[kode]=Key;
    Serial.println(kodeinput);
    kode++;
    }
    if(kode==4){
      checkPassword();
    }
}

void checkPassword(){
    if(kodeinput[0]=='1'&& kodeinput[1]=='2'&&kodeinput[2]=='3'&& kodeinput[3]=='4'){
        Serial.println("Masuk");
        delay(10);
        clearpass();
        tune();
        tune();
        masuk=false;
        kode=0;        
    }else{
        Serial.println(kodeinput);
        Serial.println("Ditolak");
        delay(10);
        clearpass();
        masuk=false;
        kode=0;        
      }
}

void tune(){
    digitalWrite(buz,HIGH);
    delay(100);
    digitalWrite(buz,LOW);
    delay(100);
    digitalWrite(buz,HIGH);
    delay(100);
    digitalWrite(buz,LOW);
}

void clearpass(){
      for(int t=0;t<4;t++){
      kodeinput[t]='0';
    }
}

