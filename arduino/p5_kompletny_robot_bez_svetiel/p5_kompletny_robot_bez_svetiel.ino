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
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (SMER_A1, OUTPUT);
  pinMode (SMER_A2, OUTPUT);
  pinMode (RYCHLOST_A, OUTPUT);
  pinMode (SMER_B1, OUTPUT);
  pinMode (SMER_B2, OUTPUT);
  pinMode (RYCHLOST_B, OUTPUT);
}
boolean dopreduSmer = 0;
boolean zapnutyAsistentNarazu = 1;
int jeZapnutyACC = 0;
void loop(){
  prikazZTabletu();
  if (zapnutyAsistentNarazu) {
    testVzdialenost();
  }
  delay (200);
}

int ktoraRychlost = 0;

void prikazZTabletu(){
  znak = 0;
  if(Serial.available()>0) {znak = Serial.read();}
  switch (znak){
    case 'A': dopredu();
      Serial.println(" idem dopredu"); 
      dopreduSmer = 1;
      break;
    case 'C': doprava();
      Serial.println(" idem doprava"); 
      dopreduSmer = 0;break;
    case 'B': dolava();
      Serial.println(" idem dolava"); 
      dopreduSmer = 0;break;
    case 'D': dozadu();
      Serial.println(" idem dozadu"); 
      dopreduSmer = 0;
      break;
    case 'E': vypniA(), vypniB();
      Serial.println(" zastavam...");
       dopreduSmer = 0;
       break;
    case 'F': zapnutyAsistentNarazu = true;
      Serial.println("asistent narazu zapnuty");
      break;
    case 'G': zapnutyAsistentNarazu = false;
      Serial.println("asistent narazu vypnuty");
      break;
    case 'H': rychlostA(255); rychlostB(255); ktoraRychlost = 1; 
      Serial.println("nastaveny tempomat \"najrychlejsie\"");
      break;
    case 'I': rychlostA(200); rychlostB(200); ktoraRychlost = 3;
      Serial.println("nastaveny tempomat \"rychlo\"");
      break;
    case 'J': rychlostA(150); rychlostB(150); ktoraRychlost = 5;
      Serial.println("nastaveny tempomat \"stredne\"");
      break;
    case 'K': rychlostA(100); rychlostB(100); ktoraRychlost = 7;
      Serial.println("nastaveny tempomat \"pomaly\"");
      break;
    case 'O': rychlostA(225); rychlostB(225); ktoraRychlost = 2; 
      Serial.println("nastaveny tempomat \"stredne rychlo\"");
      break;
    case 'P': rychlostA(175); rychlostB(175); ktoraRychlost = 4; 
      Serial.println("nastaveny tempomat \"viac stredne\"");
      break;
    case 'Q': rychlostA(125); rychlostB(125); ktoraRychlost = 6; 
      Serial.println("nastaveny tempomat \"menej stredne\"");
      break;
    case 'R': rychlostA(75); rychlostB(75); ktoraRychlost = 8; 
      Serial.println("nastaveny tempomat \"najpomalsie\"");
      break;
    case 'L': jeZapnutyACC = 1;
      Serial.println("nastaveny ACCtempomat doprava ");
      break;
    case 'M': jeZapnutyACC = 2;
      Serial.println("nastaveny ACCtempomat dolava ");
      break;
    case 'N': jeZapnutyACC = 0;
      Serial.println("vypnuty acc ");
      break;
  }
}

long duration, distance;

void testVzdialenost() {
  zistiVzdialenost();
  if (distance >= 400 || distance <= 0) {
    Serial.println ("ste pridaleko alebo priblizko k prekazke");
  } else if (distance < 50) { 
    Serial.print(distance);
    if (jeZapnutyACC == 1) {
      otacajSaKymJePrekazkaDoprava();
    }else if (jeZapnutyACC == 2){
      otacajSaKymJePrekazkaDolava();
    }else{
      Serial.println(" cm POZOR PREKAZKA BLIZSIE AKO 50CM BRZDIT ALEBO ZMENIT SMER ");
      if (distance < 25 && dopreduSmer) {
         zastav();
      }
    }
  }
}  
 void dopredu() {
  smerA(1);
  smerB(1);
  akaRychlost(255);
}
void dozadu() {
  smerA(0);
  smerB(0);
  akaRychlost(255);
}
void doprava() {
  smerA(1);
  smerB(0);
  akaRychlost(150);
}
void dolava() {
  smerA(0);
  smerB(1);
  akaRychlost(150);
}

/*
 * Co robi:
 * nastavy rychlost motorov
 * 
 * Vstupy:
 * rychlostBezTempomatu je cislo oznacujuce rychlost bez tempomatu  
 */
void akaRychlost(int rychlostBezTempomatu){
  switch (ktoraRychlost) {
    case 1: rychlostA(255); rychlostB(255); break;
    case 2: rychlostA(225); rychlostB(225); break;
    case 3: rychlostA(200); rychlostB(200); break;
    case 4: rychlostA(175); rychlostB(175); break;
    case 5: rychlostA(150); rychlostB(150); break;
    case 6: rychlostA(125); rychlostB(125); break;
    case 7: rychlostA(100); rychlostB(100); break;
    case 8: rychlostA(75); rychlostB(75); break;
    case 0: rychlostA(rychlostBezTempomatu); rychlostB(rychlostBezTempomatu); break;
  }
}

void otacajSaKymJePrekazkaDoprava(){
  doprava();
  otacajSaKymJePrekazka();
}

void otacajSaKymJePrekazkaDolava(){
  dolava();
  otacajSaKymJePrekazka();
}

void otacajSaKymJePrekazka(){
  rychlostA(100);
  rychlostB(100);
  while (distance <= 50) {
    zistiVzdialenost();
    delay(200);  
  }
  Serial.println("Nasiel som volnu cestu.");
  dopredu();
}

void zistiVzdialenost(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 25000);
  distance = (duration/2) / 29.1;// distance = (duration * 17) / 1000;
  Serial.print("Vzdialenost = ");
  Serial.print(distance);
  Serial.println(" cm");
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
   
   

