#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define WIFI_SSID "Redmi10"
#define WIFI_PASSWORD "habibaahmed18"

#define API_KEY "AIzaSyBzOXJHsiKddSSGtLYOoVpGyU5mHiL3KSM"
#define DATABASE_URL "https://gr433-5068f-default-rtdb.firebaseio.com/" 

int waterlvl = 34;
int dataL;
int CO2 = 35;
int dataC;
int pH = 39;
int dataP;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void setup(){
  Serial.begin(115200);
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

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
    pinMode(waterlvl, INPUT);
       pinMode(CO2, INPUT);
          pinMode(pH, INPUT);
}

void loop(){
   dataL= analogRead(34);
  String datalvl = String(dataL);
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();    
    if (Firebase.RTDB.setInt(&fbdo, "Sensor/waterlvl", dataL)){
      Serial.println("PASSEDlvl");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("lvlFAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
   {
   dataC= analogRead(35);
  String datacarbon = String(dataC);
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();    
    if (Firebase.RTDB.setInt(&fbdo, "Sensor2/CO2", dataL)){
      Serial.println("PASSEDCO2");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("GasFAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    {
   dataP= analogRead(39);
  String datapH = String(dataP);
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();    
    if (Firebase.RTDB.setInt(&fbdo, "Sensor3/pH", dataL)){
      Serial.println("pHPASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("pHFAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
}
  }
   }
     }
      }
       }
