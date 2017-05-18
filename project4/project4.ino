/*
========================================
 PROYEK ROBOTIK KEREN DENGAN ARDUINO
 OLEH  FIRMANSYAH SAFTARI - 2015
 PROJECT-4 : STOPWATCH ARDUINO
========================================
*/

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()

{
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  pinMode(9, INPUT);
  digitalWrite(9, HIGH);
  // pinMode(10, INPUT);
  // digitalWrite(10, HIGH);
}
double i = 0;
double a = millis();
double c ;
void loop()
{
  lcd.clear();
  lcd.print("Tekan START");
  delay(100);

  if (digitalRead(8) == LOW)
  {

    lcd.clear();
    a = millis();
    while (digitalRead(9) == HIGH)
    {

      c = millis();
      unsigned long start, finished, elapsed;
      float h, m, s, ms;
      unsigned long over;
      elapsed = c;
      h = int(elapsed / 3600000);
      over = elapsed % 3600000;
      m = int(over / 60000);
      over = over % 60000;
      s = int(over / 1000);
      ms = over % 1000;
      lcd.setCursor(0, 1);
      lcd.print(h, 0);
      lcd.print("h ");
      lcd.print(m, 0);
      lcd.print("m ");
      lcd.print(s, 0);
      lcd.print("s ");
      if (h < 10)
      {
        lcd.print(ms, 0);
        lcd.print("ms ");
      }

      if (digitalRead(9) == LOW)
      {
        while (digitalRead(8) == HIGH)
        {

        }
      }
    }

  }
}
