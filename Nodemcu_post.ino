//==================================
#include<SoftwareSerial.h>
SoftwareSerial mySerialn(D1, D2); //Rx,TX
//==================================
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "CPH1723";  // SSID
const char *password = "12345678"; // Password

void setup() {
  mySerialn.begin(9600); //me add
  Serial.begin(9600); // Starting Serial Terminal
  WiFi.begin(ssid, password); // Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  //================================================
  float rom = mySerialn.readStringUntil('\r');
  float obj = mySerialn.readStringUntil('\r');
  float ecg = mySerialn.readStringUntil('\r');
  Serial.println(rom);
  Serial.println(obj);
  Serial.println(ecg);
if (rom == 0  && obj ==0  && ecg ==0)
  {
    Serial.println("Failed to read from sensor!");
    return;
  }
//===============================================
  //////////////////////////////////
 // CODE TO RETRIEVE DATA FROM SENSORS
    
  float body_temp = obj;
  float room_temp = rom;
  float ecg_data = ecg;
  //////////////////////////////////
  
  //Post Data
  HTTPClient http;
  String postData;
  postData = "body_temp=" + String(body_temp) + "&room_temp=" + String(room_temp) + "&ecg_data=" + String(ecg_data);
    
  http.begin("http://192.168.43.113:5000/data"); //Change `54.179.164.125` to your Private IP, keep the `:5000`         
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Remain the same 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
  Serial.println(httpCode);   //httpCode == 200 means request made successfully
  http.end();  //Close connection
    delay(5000);  //Post Data at every 5 seconds
}
