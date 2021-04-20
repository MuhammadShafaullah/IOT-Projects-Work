int Green = 3;
int Orange = 4;
int Red = 5;

void setup() {
  Serial.begin(9600);
  pinMode(Green,OUTPUT);
  pinMode(Orange,OUTPUT);
  pinMode(Red,OUTPUT);
  

}


char c;
String voice;

void loop() {
  if (Serial.available()>0)
  {
    voice="";
    voice=Serial.readString();
    Serial.print(voice+'\n');
  }

  if(voice=="green")
  {
        digitalWrite(Green,HIGH);         
  } else if(voice=="green off")
  {
    digitalWrite(Green,LOW);
  }

    if(voice=="orange")
  {
    digitalWrite(Orange,HIGH);
  } else if(voice=="orange off")
  {
     digitalWrite(Orange,LOW);
  }
   
   if(voice=="red")
  {
    digitalWrite(Red,HIGH);
  } else if(voice=="red off")
  {
    digitalWrite(Red,LOW);
  }
      if(voice=="turn off")
  {
    digitalWrite(Red,LOW);
     delay(1000);
    digitalWrite(Orange,LOW);
     delay(1000);
    digitalWrite(Green,LOW);
    delay(1000);
  }else if(voice=="turn on")
  {
    
      digitalWrite(Red,HIGH);
    delay(1000);
    digitalWrite(Orange,HIGH);
    delay(1000);
    digitalWrite(Green,HIGH);
    delay(1000);
    
    }

}
