#include <Arduino.h>

#define PIN_LED 2
#define PIN_BUTTON 4

uint8_t count = 1;
bool ledState = LOW;

void setup() {

  Serial.begin(115200);

  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(PIN_LED, LOW);

}

void loop() {

  bool state = digitalRead(PIN_BUTTON);

  if(state == LOW){

    count = count + 1;
    // count++;

    Serial.println(count);

  }

  if(count == 5){
    
    count = 1;

    ledState = !ledState;
    
    digitalWrite(PIN_LED, ledState);

  }
  
  // Serial.println(state);

  delay(100);


}
