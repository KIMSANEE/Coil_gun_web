#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

#define WIFI_SSID "LG X500_9646"
#define WIFI_PASSWORD "12345678"
#define API_KEY "AIzaSyC7Jng3b2Dv446U5aDyOB2GVumvHJ6CB-o"
#define DATABASE_URL "https://coil-gun-default-rtdb.firebaseio.com/"


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

bool Switch = false;

int s1=13;
int s2=12;
int s3=14;
int s4=27;
int coil1=15;
int coil2=2;
int coil3=4;
int distance1=0;
int distance2=0;
int distance3=0;
int distance4=0;
float v1=0.0;
float v2=0.0;
float v3=0.0;
float v4=0.0;



void setup(){
  Serial.begin(115200);
  pinMode(coil1, OUTPUT);
  pinMode(coil2, OUTPUT);
  pinMode(coil3, OUTPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);

  
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if(Firebase.signUp(&config, &auth, "","")){
    Serial.println("signUp OK");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.RTDB.setBool(&fbdo,"/Switch",false);
  // pinMode(13,OUTPUT);
  digitalWrite(coil1,LOW);
  digitalWrite(coil2,LOW);
  digitalWrite(coil3,LOW);
  
}


void loop(){
   if(Firebase.RTDB.getInt(&fbdo,"/Distance/D1")){
    if(fbdo.dataType()=="int"){
      distance1=fbdo.intData();
      // Serial.println(distance1);
    }
      }
    if(Firebase.RTDB.getInt(&fbdo,"/Distance/D2")){
    if(fbdo.dataType()=="int"){
      distance2=fbdo.intData();
      // Serial.println(distance2);
    }
      }
    
      if(Firebase.RTDB.getInt(&fbdo,"/Distance/D3")){
    if(fbdo.dataType()=="int"){
      distance3=fbdo.intData();
      // Serial.println(distance3);
    }
      }
          if(Firebase.RTDB.getInt(&fbdo,"/Distance/D4")){
    if(fbdo.dataType()=="int"){
      distance4=fbdo.intData();
      // Serial.println(distance4);
    }
          }
  

    if(Firebase.RTDB.getBool(&fbdo,"/Switch")){
      if (fbdo.dataType()=="boolean"){
        Switch = fbdo.boolData();
        float t0=0.0;
        float t1=0.0;
        float t2=0.0;
        float t3=0.0;
        float t4=0.0;
        
        if(Switch==true){
      
    
            t0=millis();
            
            while(digitalRead(s1)==0 and Switch==true)
            {
              digitalWrite(coil1,HIGH);
            }
            digitalWrite(coil1,LOW);
            t1=millis();
            
            while(digitalRead(s2)==0 and Switch==true)
            {
            digitalWrite(coil2,HIGH);
            }
            digitalWrite(coil2,LOW);
            t2=millis();
            
            while(digitalRead(s3)==0 and Switch==true)
            {
            digitalWrite(coil3,HIGH);
            }
            digitalWrite(coil3,LOW);
            t3=millis();
            while(digitalRead(s4)==0 and Switch==true)
            {
            }
            t4=millis();
            Serial.println(t0);
            Serial.println(t1);
            Serial.println(t2);
            Serial.println(t3);
            Serial.println(t4);

            Serial.println(t1-t0);
            Serial.println(t2-t1);
            Serial.println(t3-t2);
            Serial.println(t4-t3);


            v1=100*distance1/(t1-t0);
            v2=100*distance2/(t2-t1);
            v3=100*distance3/(t3-t2);
            v4=100*distance4/(t4-t3);
            Serial.println(v1);
            Serial.println(v2);
            Serial.println(v3);
            Serial.println(v4);

            Firebase.RTDB.setFloat(&fbdo,"/Valocity/v1",v1);
            Firebase.RTDB.setFloat(&fbdo,"/Valocity/v2",v2);
            Firebase.RTDB.setFloat(&fbdo,"/Valocity/v3",v3);
            Firebase.RTDB.setFloat(&fbdo,"/Valocity/v4",v4);

            Serial.println("Finish");
            Firebase.RTDB.setBool(&fbdo,"/Switch",false);
            Switch == false;
            }
        }
    }
}
