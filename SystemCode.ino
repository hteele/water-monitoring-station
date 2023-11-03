#include <DHT.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "SystemLogic.h"

// Pin definitions
const int DHT_PIN = 0;
const int PHOTOCELL_PIN = A0;
const int SOIL_PIN = 39;
const int SERVO_PIN = 2;
const int SOLENOID_PIN = 4;

// WiFi credentials
const char* WIFI_NAME = "Stevens-IoT";
const char* WIFI_PASS = "nMN882cmg7";

// MQTT configuration
const char* MQTT_SERVER = "98db5050a791439c98eac188febfecbe.s2.eu.hivemq.cloud";
const char* MQTT_USER = "stevens";
const char* MQTT_PASS = "Stevens@1870";
const int MQTT_PORT = 8883;

// Team information
const String YEAR = "2023";
const String SECTION = "OI";
const String STATION_NUMBER = "5";
String PAYLOAD;

// Sensor configuration
const int SOIL_MAXWET = 2640;
const int SOIL_MAXDRY = 3260;

const int SERVO_OPEN_ANGLE = 160;
const int SERVO_CLOSE_ANGLE = 0;

const unsigned long SERVO_OPEN_TIME = 1500;
const unsigned long SERVO_CLOSE_TIME = 3600000UL * 4;  // CHANGE INTEGER FOR HOURS CLOSED e.g. 3600000UL*5 = 5 hours

const int DATA_POINTS = 20;
const int AVG_DELAY = 20;

unsigned long previousMillis = 0;

void setup() {
  wifi_start();
  mqtt_start();
  enable_sensors();
  previousMillis = millis();
}

unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 100000;
unsigned long currentStatus = SERVO_CLOSE_TIME;
bool isClosed = true;

void loop() {

  mqtt_loop();

  unsigned long currentMillis = millis();

  if(isClosed && (currentMillis - previousMillis >= SERVO_OPEN_TIME)){ 
    myservo.attach(SERVO_PIN, 1000, 2000); // attaches the servo on pin 18 to the servo object
    myservo.write(SERVO_OPEN_ANGLE);
    isClosed = false;
    delay(500); //This delay contributes to open time
    myservo.detach();
    previousMillis = currentMillis;
  } 
  else if(!isClosed && (currentMillis - previousMillis >= SERVO_CLOSE_TIME)){
    myservo.attach(SERVO_PIN, 1000, 2000); // attaches the servo on pin 18 to the servo object
    myservo.write(SERVO_CLOSE_ANGLE);
    isClosed = true;
    delay(500); //This delay contributes to close time
    myservo.detach();
    previousMillis = currentMillis;
   }  
      
  float temperature = tempAvg(DATA_POINTS, AVG_DELAY);
  float humidity = humAvg(DATA_POINTS, AVG_DELAY);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  int photocellAverage = photocellAvg(DATA_POINTS, AVG_DELAY);
  Serial.print("Photocell Value: ");
  Serial.println(photocellAverage);

  int soilhumidity = analogRead(SOIL_PIN);
  int soilPercent = map(soilhumidity, SOIL_MAXWET, SOIL_MAXDRY, 100, 0);
  Serial.print("Soil Humidity Reading: ");
  Serial.print(soilPercent);
  Serial.println(" %");

  /*Must match the PAYLOAD structure ex) PAYLOAD = SECTION +"/" + STATION_NUMBER + "var_name";
  /"var_name" can be temp / hum / soil_hum / photocell/temperature*/
  char pubString1[8];
  dtostrf(temperature, 1, 2, pubString1);
  String tempTopic = YEAR + "/" + SECTION + "/" + STATION_NUMBER + "/" + "temp";
  
  char pubString2[8];
  dtostrf(humidity, 1, 2, pubString2);
  String humTopic = YEAR + "/" + SECTION + "/" + STATION_NUMBER + "/" + "hum";
  
  char pubString3[8];
  dtostrf(soilPercent, 1, 2, pubString3);
  String soilTopic = YEAR + "/" + SECTION + "/" + STATION_NUMBER + "/" + "soil_hum";
  
  char pubString4[8];
  dtostrf(photocellAverage, 1, 2, pubString4);
  String photocellTopic = YEAR + "/" + SECTION + "/" + STATION_NUMBER + "/" + "photocell";
  
  PAYLOAD = YEAR + "/" + SECTION + "/" + STATION_NUMBER;
  
  //Non-blocking MQTT publish & delay
  if (millis() - lastPublishTime >= publishInterval) {
    // Publish each value in its own topic
    client.publish(tempTopic.c_str(), pubString1);
    delay(250);
    client.publish(humTopic.c_str(), pubString2);
    delay(250);
    client.publish(soilTopic.c_str(), pubString3);
    delay(250);
    client.publish(photocellTopic.c_str(), pubString4);
    delay(250);
  
    lastPublishTime = millis();
    }
}
