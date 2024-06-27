#include <Arduino.h>
#include <WiFi.h>
#include <DHT.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"

// Insert Firebase project API Key
#define API_KEY "AIzaSyAJ6xRK6Tt_Z_hYubzDPbPLpzjQCbsHa_g"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://fag-pse-teste-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

#define DHTPIN 4
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

float readDHTTemperature() {

  float t = dht.readTemperature();
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return 0;
  }
  else {
    Serial.println(t);
    return t;
  }

}

float readDHTHumidity() {

  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;
  }
  else {
    Serial.println(h);
    return h;
  }

}
void setup(){

  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    if (Firebase.RTDB.setFloat(&fbdo, "readings/temperature", readDHTTemperature())){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    if (Firebase.RTDB.setFloat(&fbdo, "readings/humidity", readDHTHumidity())){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    float threshold = 0.0f;
    if(Firebase.RTDB.getFloat(&fbdo, "readings/threshold", &threshold)){
      Serial.printf("Threshold: %.2f", threshold);
    }
    else{
      Serial.println("-");
    }

    if(readDHTTemperature() >= threshold){
      digitalWrite(2, HIGH);
    }
    else{
      digitalWrite(2, LOW);
    }

  }

}