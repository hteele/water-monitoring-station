#ifndef SystemLogic_h
#define SystemLogic_h

static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

#include <DHT.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// Pin definitions
extern const int DHT_PIN;
extern const int PHOTOCELL_PIN;
extern const int SOIL_PIN;
extern const int SERVO_PIN;
extern const int SOLENOID_PIN;

// WiFi credentials
extern const char* WIFI_NAME;
extern const char* WIFI_PASS;

// MQTT configuration
extern const char* MQTT_SERVER;
extern const char* MQTT_USER;
extern const char* MQTT_PASS;
extern const int MQTT_PORT;

// Team information
extern const String YEAR;
extern const String SECTION;
extern const String STATION_NUMBER;
extern String PAYLOAD;

// Sensor configuration
extern const int SOIL_MAXWET;
extern const int SOIL_MAXDRY;
extern const int SERVO_OPEN_ANGLE;
extern const int SERVO_CLOSE_ANGLE;
extern const unsigned long SERVO_OPEN_TIME;
extern const unsigned long SERVO_CLOSE_TIME;

extern const int DATA_POINTS;
extern const int AVG_DELAY;

// Global objects
WiFiClientSecure espClient;
PubSubClient client(espClient);
DHT dht(DHT_PIN, DHT11);
Servo myservo;  // create servo object to control a servo
Servo mysol;

String get_wifi_status(int status){
    switch(status){
        case WL_IDLE_STATUS:
        return "WL_IDLE_STATUS";
        case WL_SCAN_COMPLETED:
        return "WL_SCAN_COMPLETED";
        case WL_NO_SSID_AVAIL:
        return "WL_NO_SSID_AVAIL";
        case WL_CONNECT_FAILED:
        return "WL_CONNECT_FAILED";
        case WL_CONNECTION_LOST:
        return "WL_CONNECTION_LOST";
        case WL_CONNECTED:
        return "WL_CONNECTED";
        case WL_DISCONNECTED:
        return "WL_DISCONNECTED";
    }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
      Serial.println("connected");

      client.subscribe("led_state");   // subscribe the topics here

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqtt_loop(){
   if (!client.connected()) {
   reconnect();
  }
  client.loop();
  }

void wifi_start(){
   Serial.begin(115200);
  // Network settings
  
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  
  //WIFI connection status checking
  WiFi.mode(WIFI_STA);
  int status = WL_IDLE_STATUS;
  
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  Serial.println(get_wifi_status(status));
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    status = WiFi.status();
    Serial.println(get_wifi_status(status));
    delay(1000);
  }
  
  Serial.println("\nConnected to the WiFi network");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void enable_sensors(){
  //Enabling the PWM function on ESP32
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  mysol.setPeriodHertz(50);    // standard 50 hz servo
  //myservo.attach(SERVO_PIN, 1000, 2000); // attaches the servo on pin 18 to the servo object
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep

  //DHT Sensor setting
  dht.begin();
 }

void mqtt_start(){
  espClient.setCACert(root_ca);      // enable this line and the the "certificate" code for secure connection
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
 }

int photocellAvg(int numPoints, int delayPhoto){
  int photoTotal = 0;
  for(int i = 0; i<numPoints; i++){
    photoTotal += analogRead(PHOTOCELL_PIN);
    delay(delayPhoto);
    }
    int photoAvg = photoTotal/numPoints;
    return photoAvg;
}

int tempAvg(int numPoints, int delayTemp){
  float tempTotal = 0;
  for(int i = 0; i<numPoints; i++){
    tempTotal += dht.readTemperature();
    delay(delayTemp);
    }
    float tempAvg = tempTotal/numPoints;
    return tempAvg;
}

int humAvg(int numPoints, int delayHum){
  int humTotal = 0;
  for(int i = 0; i<numPoints; i++){
    humTotal += dht.readHumidity();
    delay(delayHum);
    }
    int humAvg = humTotal/numPoints;
    return humAvg;
  }
  
#endif
