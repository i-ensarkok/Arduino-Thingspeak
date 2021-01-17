
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <dht11.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

unsigned long CHANNEL_ID = 1279502; // YOUR CHANNEL ID
const char* CHANNEL_API_KEY = "C59SHAAEIM8503XT"; //YOUR CHANNEL WRITE API KEY
  
int status = WL_IDLE_STATUS;
WiFiClient  client;

int MQ135_VALUE; // variable to save analog reading

#define DHT11PIN 13 // On NodeMCU D7 pin, on Arduino IDE 13.

dht11 DHT11;

#define TEMPERATURE_FIELD 1
#define HUMIDITY_FIELD 2
#define MQ135_FIELD 3


 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  
  ThingSpeak.begin(client);
 
}
 
void loop() {
   int chk = DHT11.read(DHT11PIN);
   
  float TEMPERATURE = (float)DHT11.temperature;
  float HUMIDITY = (float)DHT11.humidity;
  MQ135_VALUE = analogRead(A0);
  
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (Celcius): ");
  Serial.println((float)DHT11.temperature, 2);
  ThingSpeak.writeField(CHANNEL_ID, 1, TEMPERATURE, CHANNEL_API_KEY);
  delay(250);
  ThingSpeak.writeField(CHANNEL_ID, 2, HUMIDITY, CHANNEL_API_KEY);
  delay(250);
  ThingSpeak.writeField(CHANNEL_ID, 3, MQ135_VALUE, CHANNEL_API_KEY);
   delay(500);
}
