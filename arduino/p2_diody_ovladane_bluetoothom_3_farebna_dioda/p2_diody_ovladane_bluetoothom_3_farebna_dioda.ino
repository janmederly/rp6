int znak;
void setup(){
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop(){
  if(Serial.available()>0) {znak = Serial.read();}
  switch (znak){
    case 201: digitalWrite(2,HIGH);
      Serial.println(" LED-1 zapnuta"); break;
    case 202: digitalWrite(2,LOW);
      Serial.println(" LED-1 vypnuta"); break;
    case 203: digitalWrite(3,HIGH);
      Serial.println(" LED-2 zapnuta"); break;
    case 204: digitalWrite(3,LOW);
      Serial.println(" LED-2 vypnuta"); break;
    case 205: digitalWrite(4,HIGH);
      Serial.println(" LED-3 zapnuta"); break;
    case 206: digitalWrite(4,LOW);
      Serial.println(" LED-3 vypnuta"); break;
    case 207: digitalWrite(5,HIGH);
      Serial.println(" Modra zapnuta"); break;
    case 208: digitalWrite(5,LOW);
      Serial.println(" Modra vypnuta"); break;
    case 209: digitalWrite(6,HIGH);
      Serial.println(" Zelena zapnuta"); break;
    case 210: digitalWrite(6,LOW);
      Serial.println(" Zelena vypnuta"); break;
    case 211: digitalWrite(7,HIGH);
      Serial.println(" cervena zapnuta"); break;
    case 212: digitalWrite(7,LOW);
      Serial.println(" cervena vypnuta"); break;
    
  }
  znak =0;
}

