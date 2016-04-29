#define trigPin 2
#define echoPin 3

int znak;
const int SMER_A1 = 8;
const int SMER_A2 = 11;
const int RYCHLOST_A = 9;
const int SMER_B1 = 12;
const int SMER_B2 = 13;
const int RYCHLOST_B = 10;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(SMER_A1, OUTPUT);
  pinMode(SMER_A2, OUTPUT);
  pinMode(RYCHLOST_A, OUTPUT);
  pinMode(SMER_B1, OUTPUT);
  pinMode(SMER_B2, OUTPUT);
  pinMode(RYCHLOST_B, OUTPUT);
}

boolean dopreduSmer = 0;
boolean zapnuty = 1;

void loop() {
  prikazZTabletu();
  if (zapnuty) {
    testVzdialenost();
  }
  delay(200);
}

void prikazZTabletu() {
  znak = 0;
  if(Serial.available()>0) {znak = Serial.read();}
  switch (znak){
  case 'A': 
    dopredu();
    Serial.println(" idem dopredu");
    dopreduSmer = 1;
    break;
  case 'C':
    doprava();
    Serial.println(" idem doprava");
    dopreduSmer = 0;
    break;
  case 'B':
    dolava();
    Serial.println(" idem dolava");
    dopreduSmer = 0;
    break;
  case 'D':
    dozadu();
    Serial.println(" idem dozadu");
    dopreduSmer = 0;
    break;
  case 'E': 
    vypniA(), vypniB();
    Serial.println(" zastavam...");
    dopreduSmer = 0;
  break;
  case 'F': 
    zapnuty = true;
    Serial.println("asistent narazu zapnuty");
    break;
  case 'G':
    zapnuty = false;
    Serial.println("asistent narazu vypnuty");
    break;
  }
}

void testVzdialenost() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 25000);
  distance = (duration/2) / 29.1;
  if (distance >= 400 '' distance <= 0) {
    //nic
  } else if (distance < 50) {
    Serial.print(distance);
    Serial.println(" cm POZOR PREKAZKA BLIZSIE AKO 50CM BRZDIT ALEBO ZMENIT SMER ");
    if (distance < 15 && dopreduSmer) {
      zastav();
    }
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
}

void dopredu() {
  smerA(1);
  smerB(1);
  zapniA();
  zapniB();
}
void dozadu() {
  smerA(0);
  smerB(0);
  zapniA();
  zapniB();
}
void doprava() {
  smerA(1);
  smerB(0);
  zapniA();
  zapniB();
  rychlostA(150);
  rychlostB(150);
}
void dolava() {
  smerA(0);
  smerB(1);
  zapniA();
  zapniB();
  rychlostA(150);
  rychlostB(150);
}
void zastav() {
  vypniA();
  vypniB();
}
void smerA(int vpred) { // vpred = 1 ak chces ist dopredu, vpred = 0 ak chces ist dozadu
  if (vpred != 0) {
    digitalWrite(SMER_A1, LOW);
    digitalWrite(SMER_A2, HIGH);
  } else {
    digitalWrite(SMER_A1, HIGH);
    digitalWrite(SMER_A2, LOW);
  }
}
void zapniA() {
  digitalWrite(RYCHLOST_A, HIGH);
}
void vypniA() {
  digitalWrite(RYCHLOST_A, LOW);
}
void rychlostA(int kolko) {
  analogWrite(RYCHLOST_A, kolko);
}
void smerB(int vpred) {
  if (vpred != 0) {
    digitalWrite(SMER_B1, LOW);
    digitalWrite(SMER_B2, HIGH);
  } else {
    digitalWrite(SMER_B1, HIGH);
    digitalWrite(SMER_B2, LOW);
  }
}
void zapniB() {
  digitalWrite(RYCHLOST_B, HIGH);
}
void vypniB() {
  digitalWrite(RYCHLOST_B, LOW);
}
void rychlostB(int kolko) {
  analogWrite(RYCHLOST_B, kolko);
}



