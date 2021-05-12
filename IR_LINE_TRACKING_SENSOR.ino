int sensorPin = A1; // select the input pin
int sensorValue = 0; // variable to store the value coming from the sensor
int BUILTIN_LED =13;
void setup ()
{
 pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
 Serial.begin (9600);
  pinMode(12, OUTPUT);
}
 
void loop ()
{
 sensorValue = analogRead (sensorPin);
 Serial.println (sensorValue, DEC); //debug
 if(sensorValue <= 100)
 {
 digitalWrite (BUILTIN_LED, HIGH); //led off
 digitalWrite(12, HIGH);//for buzzer
 delay(1000);
 digitalWrite(12, LOW);//for buzzer  
 }
 digitalWrite (BUILTIN_LED, LOW); //led on - default
}
 
