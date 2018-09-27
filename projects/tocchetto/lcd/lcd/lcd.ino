// Programa : Display LCD 16x2 e modulo I2C
// Autor : Arduino e Cia

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};

void setup()
{
  lcd.begin(16,2);
  lcd.createChar(3, heart);
}
 
void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  // lcd.print("Arduino e Cia !!");
  lcd.write(3);
  lcd.write(3);
  lcd.write(3);
  lcd.print(" Deise e ");
  lcd.write(3);
  lcd.write(3);
  lcd.write(3);
  lcd.setCursor(0,1);
  lcd.write(3);
  lcd.write(3);
  lcd.write(3);
  lcd.print(" Marcelo ");
  lcd.write(3);
  lcd.write(3);
  lcd.write(3);
  // lcd.print("LCD e modulo I2C");
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
}


