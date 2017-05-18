/*
 * Program Ini didedikasikan Untuk Pembelajaran
 * 
 * Didesain Oleh
 * 
 * Rizka Reza Pahlevi
 */

#include <Wire.h>               // Default Harus dipanggil untuk wiring
#include <LiquidCrystal_I2C.h>  // Librari untuk LCD I2C
#include <AnalogMatrixKeypad.h> // Library Untuk Mengonversi Analog Input Dari Pin A1 menjadi karakter keypad
#include <AddicoreRFID.h>       // Library untuk membaca RFID
#include <SPI.h>

#define	uchar	unsigned char     // Char yang konstant
#define buz 9                   // Pin untuk Buzzer
#define MAX_LEN 16              // Merupakan Maksimal Length RFID Data
#define SDA 10                  // Pin SDA 
/*
 * Pada Arduino Pin SPI terdapat pada :
 * SCK    : 13
 * Mosi   : 11
 * Miso   : 12
 * SDA    : 10
 */

/*
 * Pada Arduino, letak pin untuk LCD sebagai berikut :
 * SCL    : PIN SCL Arduino
 * SDA    : PIN SDA Arduino
 * VCC    : 5 V
 * GND    : GND
 * 
 * Jangan Lupa Untuk membuatkan PULL UP untuk I2C dengan resistor 4,7K Ohm atau 3,3K Ohm
 * Untuk Skematik PULL UP, silakan mencari sendiri
 */

AddicoreRFID myRFID;                                            // Membuat alias untuk RFID
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Mendefinisikan PIN LCD

// Inisialisasi Variabel yang Diperlukan dalam Program
int state;            // Membaca Pin A2
bool masuk=false;     // Memberikan nilai true jika RFID yang dibaca terdaftar dalam program
int kode=0;           // Menghitung masuknya password dari keypad
char kodeinput[4];    // Menampung password yang dimasukkan dari Keypad
int pos=0;            // Memberikan posisi kursor LCD
//---------------------------------------------------

AnalogMatrixKeypad AnMatrixKeypad(1); // Analog Input Yang digunakan Adalah A1 pada Arduino Uno

void setup() {
   lcd.begin(16,2);               // Menginisialisasi LCD
   lcd.backlight();               // Menyalakan Lampu LCD
   lcd.setCursor(3,0);            // Set Kursor
   lcd.print("HES STUDIO");
   delay(2000);
   lcd.setCursor(1,1);            // Set Kursor
   lcd.print("Tap Kartu RFID");                       
   SPI.begin();                   // Memulai SPI
   pinMode(buz,OUTPUT);           // Menginisialisasi buz menjadi OUTPUT
   pinMode(SDA,OUTPUT);           // Menginisialisasi SDA sebagai OUTPUT  
   digitalWrite(SDA, LOW);        // Memberi state SDA LOW
   pinMode(8,OUTPUT);
   digitalWrite(8,HIGH);
   delay(100);
   digitalWrite(8,LOW);
   myRFID.AddicoreRFID_Init();    // Menyalakan RFID 
}

void loop()
{
    uchar status;                                             // status dijadikan unsigned char
    uchar str[MAX_LEN];                                       // str dijadikan unsigned char dengan panjang 16
    str[1] = 0x4400;
    status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);   
    if(masuk){
        input();                                               // No Branch ketika masuk bernilai TRUE
    }	
    if (status == MI_OK)
    {
        clearpass();                                          // Membersihkan isi kodeinput
        kode=0;                                               // kode diisi dengan 0 untuk menghitung kembali
        pos=0;
    }
    
    status = myRFID.AddicoreRFID_Anticoll(str);               
    if (status == MI_OK)
    {           
        if((str[0] == 189)|| (str[0] == 136)||(str[0] == 10))
        {
            tune();                                       // Membunyikan Buzzer dengan maksud memberi tahu jika RFID yang di tap terdaftar dan dipersilahkan memasukkan password
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Hello");
            delay(500);
            lcd.clear();
            lcd.setCursor(5,0);
            lcd.print("Silahkan Masukkan PIN");
            delay(300);
            for(char k=0;k<26;k++)
            {
              lcd.scrollDisplayLeft();
              delay(300);
            }
            lcd.clear();
            lcd.print("PIN : ");
            masuk = true;
        } else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("RFID Tidak");
            lcd.setCursor(0,1);
            lcd.print("Terdaftar");
            masuk = false;
            delay(2000);
            hallo();
        }
        delay(1000);
    }
    
    myRFID.AddicoreRFID_Halt();                             // Menunggu tap RFID kembali
}

void input(){
    char Key = AnMatrixKeypad.readKey();                    // Membaca Arus yang masuk pada pin A1
    if(Key != KEY_NOT_PRESSED){                             // Jika Key bernilai, maka akan diproses dalam library
        //lcd.clear();
        lcd.setCursor(pos,1);
        lcd.print(Key);
        kodeinput[kode]=Key;                                // Memasukkan key dalam array kodeinput
        pos++;
        kode++;                                             // Mengincreament kode
    }
    if(kode==4){                                            // Jika kode yang dimasukkan sudah sejumlah 4 kode, maka akan di check
        checkPassword();
    }
}

void checkPassword(){
    if(kodeinput[0]=='2'&& kodeinput[1]=='3'&&kodeinput[2]=='5'&& kodeinput[3]=='6'){
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Selamat Datang");
        delay(10);
        clearpass();
        tune();
        tune();
        masuk=false;
        kode=0;
        pos=0;
        delay(3000);
        hallo();        
    }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Password Salah");
        delay(10);
        clearpass();
        masuk=false;
        kode=0;
        pos=0;        
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

void hallo(){
   lcd.clear();
   lcd.setCursor(3,0);            // Set Kursor
   lcd.print("HES STUDIO");
   delay(2000);
   lcd.setCursor(1,1);            // Set Kursor
   lcd.print("Tap Kartu RFID"); 
}

