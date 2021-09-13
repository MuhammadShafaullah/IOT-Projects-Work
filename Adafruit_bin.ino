
#include <ESP8266WiFi.h>
#include<String.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define TRIGGERPIN D4
#define ECHOPIN    D3
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D1, D2); // RX | TX
/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "CPH1723"
#define WLAN_PASS       "12345678"
/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
///////////////////////////
#define AIO_USERNAME    "Shafaullah_Malik"
#define AIO_KEY          "aio_dpRH55y7loce9yr7eWLvdxyRb7tV"
/////////////////////////
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
/////////////////////////
Adafruit_MQTT_Publish DISTANCE = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME"/feeds/Dustbin status");
void MQTT_connect();
////////////////////////
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  Serial.println(F("Adafruit MQTT demo"));
  // Connect to wifi access point
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  MQTT_connect();
  uint32_t duration, distance;
  digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println("distance in cm:");
  Serial.println(distance);
  DISTANCE.publish(distance);
  delay(2000);
  if (distance > 10 && distance < 15)
{
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+923166203882 \"\r");
  delay(1000);
  mySerial.println("Smoke Detected");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}

if (distance > 20 && distance < 25 )
{
  mySerial.println("ATD+923166203882;");
  Serial.println("Called +923166203882");
  delay(1000);
}
}
void MQTT_connect() {
  int8_t ret;
  //stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
