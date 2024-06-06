#include <Arduino.h>
#include <LiquidCrystal.h>
#include "DHT.h"

const int rs = 19, en = 23, d4 = 18, d5 = 17, d6 = 16, d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHTPIN 2
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("Iniciando...");

  delay(1000);

  lcd.clear();

  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.println(F("°F"));

  lcd.setCursor(0, 0);
  lcd.printf("UMIDADE: %.1f %", h);
  lcd.setCursor(0, 1);
  lcd.printf("TEMPERATURA:%.1fC", t);

}
