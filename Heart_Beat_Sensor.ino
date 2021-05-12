const int Sensor_PIN= A1;
const int ledpin=13;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12, OUTPUT);
pinMode(ledpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(A1));
digitalWrite(ledpin,HIGH);
digitalWrite(12, HIGH);
Serial.println(analogRead(A1));
delay(1000);
Serial.println(analogRead(A1));
digitalWrite(ledpin, LOW);
digitalWrite(12 , LOW);
Serial.println(analogRead(A1));
delay(1000);
}
