int znak;
const int SMER_A1 = 8;
const int SMER_A2 = 11;
const int RYCHLOST_A = 9;
const int SMER_B1 = 12;
const int SMER_B2 = 13;
const int RYCHLOST_B = 10;

void setup() {
 Serial.begin(9600);
 pinMode (SMER_A1, OUTPUT);
 pinMode (SMER_A2, OUTPUT);
 pinMode (RYCHLOST_A, OUTPUT);
 pinMode (SMER_B1, OUTPUT);
 pinMode (SMER_B2, OUTPUT);
 pinMode (RYCHLOST_B, OUTPUT);
}

void loop(){
  if(Serial.available()>0) {znak = Serial.read();}
  switch (znak){
    case 'A': dopredu();
      Serial.println(" idem dopredu"); break;
    case 'B': doprava();
      Serial.println(" idem doprava"); break;
    case 'C': dolava();
      Serial.println(" idem dolava"); break;
    case 'D': dozadu();
      Serial.println(" idem dozadu"); break;
    case 'E': vypniA(), vypniB();
      Serial.println(" zastavam..."); break;
     
  }
  znak =0;
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

void smerA(int vpred) {      // vpred = 1 ak chces ist dopredu, vpred = 0 ak chces ist dozadu
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
  
