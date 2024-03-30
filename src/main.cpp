#include <Arduino.h>

#define PIN_LED 2
#define ACTIVE_STATE HIGH

uint8_t count = 1;

void setup() {

  Serial.begin(115200);
  
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(PIN_LED, !ACTIVE_STATE);

}

void loop() {

  if(Serial.available() > 0){
    
    uint8_t buttonState = Serial.parseInt();

    Serial.printf("buttonState = %d\n", buttonState);

    if(buttonState == ACTIVE_STATE){

      count = count + 1;

      if(count == 5){
        
        count = 1;

        digitalWrite(PIN_LED, ACTIVE_STATE);
      }

    }
    else if(buttonState == 2){
      digitalWrite(PIN_LED, ACTIVE_STATE);
      delay(5000);

      digitalWrite(PIN_LED, !ACTIVE_STATE);

    }
    else{
      digitalWrite(PIN_LED, !ACTIVE_STATE);
    }
    
  }

}
