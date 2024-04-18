#include <Arduino.h>

#define PIN_POT 34
#define PIN_LED 27

void setup() {

  Serial.begin(115200);

}

void loop() {

  int raw = analogRead(PIN_POT);

  // float voltage = (3.3 / 4095) * raw;
  // float resistence = (10000.0 / 4095) * raw;
  // Serial.printf("Raw: %d, Voltage: %.2f\n", raw, voltage);

  int brightness = 255.0 / 4095 * raw;  
  analogWrite(PIN_LED, brightness);

  delay(10);

}
