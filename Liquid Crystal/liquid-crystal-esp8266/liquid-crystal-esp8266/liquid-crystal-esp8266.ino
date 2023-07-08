#include <LiquidCrystal_I2C.h>

byte currentLength = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup(){
Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Password");
  lcd.setCursor(3, 1);
  lcd.print("kelompok 12");
  delay(5000);
  lcd.clear();
}

void loop(){
  lcd.setCursor(0, 0);
  lcd.print("Masukan Password");
  lcd.setCursor(0,1);
  lcd.print("Pass: ");
}
