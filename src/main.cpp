#include <Arduino.h>
#include "libs/SerialMonitor.h"

void setup() {

  Serial.begin(115200);
  print(Serial, "Hello World!");

}

void loop() {

  char readed = read(Serial);

  if(readed){
    print(Serial, readed);
  }

  delay(100);

}
