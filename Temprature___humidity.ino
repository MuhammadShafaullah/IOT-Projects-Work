#include "dht.h"
#define dht_apin A1 // Analog Pin sensor is connected to
 const int ledpinG=13; 
  const int ledpinR=10;
dht DHT;
 
void setup(){
 
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(ledpinG, OUTPUT);
  pinMode(ledpinR, OUTPUT);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 
}//end "setup()"
 
void loop(){
  //Start of Program 
 
    DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    if (DHT.temperature>=38) {
       
         Serial.println("Alrt Temp high ):");
         digitalWrite(ledpinR,HIGH); //turns led on
         digitalWrite(12, HIGH);//for buzzer
         delay(2000);
         digitalWrite(ledpinR,LOW); //turns led on
         digitalWrite(12, LOW);
      } 
      else{
        digitalWrite(ledpinG,HIGH);
          delay(1000);
          digitalWrite(ledpinG,LOW);
        } 
//      if (DHT.temperature<=35) {
//           
//      Serial.println("Alrt Temp  Normal (:");
//      digitalWrite(ledpinG,HIGH); //turns led on
//      digitalWrite(12, HIGH);//for buzzer
//      delay(4000);
//      digitalWrite(ledpinG,LOW); //turns led on
//      digitalWrite(12, LOW);
//      }
//    

    
    delay(1000);//Wait 5 seconds before accessing sensor again.
  
  //Fastest should be once every two seconds.
 
}// end loop() 
