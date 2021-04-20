 
 const int ledpin=13;
 const int soundpin=A4;
 const int threshold = 200; // sets threshold value for sound sensor
void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);// for buzzer to produce sound beem
  pinMode(ledpin, OUTPUT);
  pinMode(soundpin, INPUT);
}
void loop() {
  int soundsens = analogRead(soundpin); // reads analog data from sound sensor
  if (soundsens >= threshold) {
    digitalWrite(ledpin,HIGH); //turns led on
    digitalWrite(12, HIGH);//for buzzer
    delay(1000);
  }
  else {
    digitalWrite(ledpin, LOW);
    digitalWrite(12 , LOW); //for buzzer 
  }
}
