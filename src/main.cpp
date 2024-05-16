#include <Arduino.h>
#include <LiquidCrystal.h>

// BACKLIGHT (VO) -> GND
// ESQUEMA: https://www.circuitschools.com/wp-content/uploads/2020/09/Interfacing-16X2-LCD-module-with-ESP-32-without-using-I2C-adapter.webp

const int rs = 19, en = 23, d4 = 18, d5 = 17, d6 = 16, d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint8_t count = 0;

void setup() {

  lcd.begin(16, 2);
  lcd.print("Iniciando...");

  delay(5000);

}

void loop() {

  lcd.clear();
  lcd.print(count++);
  delay(1000);

}
