#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
int backLight = 13;  

void setup()
{
  pinMode(backLight, OUTPUT);         
  analogWrite(backLight, 150);        
  lcd.begin(16,2);                    
  lcd.clear();                        
  lcd.setCursor(0,0);                 
  lcd.print("Hello. Is there anybody out there?");  
  lcd.setCursor(0,1);                 
  lcd.print("www.abrushfx.com");    
}

void loop()
{
  lcd.setCursor(16,1);
  lcd.autoscroll();    
  lcd.print(" ");     
  delay(500);          
} 
