const int TRIG_PIN = 2;
const int ECHO_PIN = 3;
const int SMER_A1 = 8;
const int SMER_A2 = 11;
const int RYCHLOST_A = 9;
const int SMER_B1 = 12;
const int SMER_B2 = 13;
const int RYCHLOST_B = 10;
const int PL_SMEROVKA = 29;
const int PP_SMEROVKA = 47;
const int ZL_SMEROVKA = 27;
const int ZP_SMEROVKA = 32;
const int L_STRETAVACIE = 45;
const int P_STRETAVACIE = 44;
const int P_DIALKOVE = 28;
const int L_DIALKOVE = 35;
const int P_ZADNE = 23;
const int L_ZADNE = 50;
const int P_BRZDNE = 22;
const int L_BRZDNE = 51;
const int SPIATOCKA = 49;
const int SILA_DENNYCH_SVETIEL = 20;
const int FOTOREZISTOR = A3;

void setup() {
  Serial.begin (9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode (SMER_A1, OUTPUT);
  pinMode (SMER_A2, OUTPUT);
  pinMode (RYCHLOST_A, OUTPUT);
  pinMode (SMER_B1, OUTPUT);
  pinMode (SMER_B2, OUTPUT);
  pinMode (RYCHLOST_B, OUTPUT);
  pinMode(PP_SMEROVKA, OUTPUT);
  pinMode(PL_SMEROVKA, INPUT);
  pinMode (ZP_SMEROVKA, OUTPUT);
  pinMode (ZL_SMEROVKA, OUTPUT);
  pinMode (L_STRETAVACIE, OUTPUT);
  pinMode (P_STRETAVACIE, OUTPUT);
  pinMode (P_DIALKOVE, OUTPUT);
  pinMode (L_DIALKOVE, OUTPUT);
  pinMode (P_ZADNE, OUTPUT);
  pinMode (L_ZADNE, OUTPUT);
  pinMode (P_BRZDNE, OUTPUT);
  pinMode (L_BRZDNE, OUTPUT);
  pinMode (SPIATOCKA, OUTPUT);
  svetla();
}

long citlivostL = 0; 
boolean jeZapnutyL = false;
long vbs = 0;
boolean dopreduSmer = 0;
boolean zapnutyAsistentNarazu = 1;
int jeZapnutyACC = 0;

void loop(){
  prikazZTabletu();
  if (zapnutyAsistentNarazu) {
    testVzdialenost();
  }
  if (jeZapnutyL) {
    lightAssist();
  }
  if (vbs > 0 && millis() >= vbs){
    digitalWrite(P_BRZDNE, LOW);
    digitalWrite(L_BRZDNE, LOW);
  }
  delay (200);
}

void lightAssist() {
  float u = (analogRead(FOTOREZISTOR) / 1023.0) * 5.0;
  float u2 = 5 - u;
  float r2 = 2200000;
  float i = u2 / r2;
  float r = u / i; 
  if (r > citlivostL) {
    digitalWrite(L_DIALKOVE, HIGH);
    digitalWrite(P_DIALKOVE, HIGH);
    analogWrite(L_STRETAVACIE, 255);
    analogWrite(P_STRETAVACIE, 255);
  } else {
    digitalWrite(L_DIALKOVE, LOW);
    digitalWrite(P_DIALKOVE, LOW);
    analogWrite(L_STRETAVACIE, SILA_DENNYCH_SVETIEL);
    analogWrite(P_STRETAVACIE, SILA_DENNYCH_SVETIEL);
  }
}

int ktoraRychlost = 0;

void prikazZTabletu(){
  int znak = 0;
  if(Serial.available()>0) {znak = Serial.read();}
  switch (znak) {
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
    case 'E': zastav();
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
      Serial.println("nastaveny tempomat \"stredne rychlo\"");
      break;
    case 'K': rychlostA(100); rychlostB(100); ktoraRychlost = 7;
      Serial.println("nastaveny tempomat \"pomaly\"");
      break;
    case 'O': rychlostA(225); rychlostB(225); ktoraRychlost = 2; 
      Serial.println("nastaveny tempomat \"velmi rychlo\"");
      break;
    case 'P': rychlostA(175); rychlostB(175); ktoraRychlost = 4; 
      Serial.println("nastaveny tempomat \"viac nez stredne rychlo\"");
      break;
    case 'Q': rychlostA(125); rychlostB(125); ktoraRychlost = 6; 
      Serial.println("nastaveny tempomat \"menej nez stredne rychlo\"");
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
    case 'S': analogWrite(L_STRETAVACIE, 255);
      analogWrite(P_STRETAVACIE, 255);
      jeZapnutyL = false;
      break;
    case 'T': analogWrite(L_STRETAVACIE, SILA_DENNYCH_SVETIEL);
      analogWrite(P_STRETAVACIE, SILA_DENNYCH_SVETIEL);
      break;
    case 'U': analogWrite(L_STRETAVACIE, 255);
      analogWrite(P_STRETAVACIE, 255);
      digitalWrite (L_DIALKOVE, HIGH);
      digitalWrite (P_DIALKOVE, HIGH);
      jeZapnutyL = false;
      break;
    case 'V':
      digitalWrite (L_DIALKOVE, LOW);
      digitalWrite (P_DIALKOVE, LOW);
      break;
    case 'W': 
      {
        jeZapnutyL = true;
        long cas = millis();
        while(Serial.available() <= 0 && millis()-cas < 1000) {
        }
        if (Serial.available() > 0) {
          int dalsi = Serial.read();
          citlivostL = (dalsi-'0'+1) * 8000000;
        }
      }
      break;
    case 'X': jeZapnutyL = false;
      digitalWrite (L_DIALKOVE, LOW);
      digitalWrite (P_DIALKOVE, LOW);
      analogWrite(L_STRETAVACIE, SILA_DENNYCH_SVETIEL);
      analogWrite(P_STRETAVACIE, SILA_DENNYCH_SVETIEL);
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
 void svetla(){
   digitalWrite(P_ZADNE, HIGH);
   digitalWrite(L_ZADNE, HIGH);
   digitalWrite(P_DIALKOVE, LOW);
   digitalWrite(L_DIALKOVE, LOW);
   digitalWrite(PP_SMEROVKA, LOW);
   digitalWrite(PL_SMEROVKA, LOW);
   digitalWrite(ZP_SMEROVKA, LOW);
   digitalWrite(ZL_SMEROVKA, LOW);
   digitalWrite(P_BRZDNE, LOW);
   digitalWrite(L_BRZDNE, LOW);
   digitalWrite(SPIATOCKA, LOW);
   analogWrite(L_STRETAVACIE, SILA_DENNYCH_SVETIEL);
   analogWrite(P_STRETAVACIE, SILA_DENNYCH_SVETIEL); 
 }
 void dopredu() {
  smerA(1);
  smerB(1);
  akaRychlost(255);
  digitalWrite(PP_SMEROVKA, LOW);
  digitalWrite(PL_SMEROVKA, LOW);
  digitalWrite(ZP_SMEROVKA, LOW);
  digitalWrite(ZL_SMEROVKA, LOW);
  digitalWrite(P_BRZDNE, LOW);
  digitalWrite(L_BRZDNE, LOW);
  digitalWrite(SPIATOCKA, LOW);
}
void dozadu() {
  smerA(0);
  smerB(0);
  akaRychlost(255);
  digitalWrite(SPIATOCKA, HIGH);
  digitalWrite(PP_SMEROVKA, LOW);
  digitalWrite(PL_SMEROVKA, LOW);
  digitalWrite(ZP_SMEROVKA, LOW);
  digitalWrite(ZL_SMEROVKA, LOW);
  digitalWrite(P_BRZDNE, LOW);
  digitalWrite(L_BRZDNE, LOW);
}
void doprava() {
  smerA(1);
  smerB(0);
  akaRychlost(150);
  digitalWrite(PP_SMEROVKA, HIGH);
  digitalWrite(ZP_SMEROVKA, HIGH);
  digitalWrite(PL_SMEROVKA, LOW);
  digitalWrite(ZL_SMEROVKA, LOW);
  digitalWrite(P_BRZDNE, LOW);
  digitalWrite(L_BRZDNE, LOW);
  digitalWrite(SPIATOCKA, LOW);
}
void dolava() {
  smerA(0);
  smerB(1);
  akaRychlost(150);
  digitalWrite(PL_SMEROVKA, HIGH);
  digitalWrite(ZL_SMEROVKA, HIGH);
  digitalWrite(PP_SMEROVKA, LOW);
  digitalWrite(ZP_SMEROVKA, LOW);
  digitalWrite(P_BRZDNE, LOW);
  digitalWrite(L_BRZDNE, LOW);
  digitalWrite(SPIATOCKA, LOW);
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

void zistiVzdialenost() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH, 25000);
  distance = (duration/2) * 0.034;
  Serial.print("Vzdialenost = ");
  Serial.print(distance);
  Serial.println(" cm");
}

void zastav() {
  vypniA();
  vypniB();
  digitalWrite(SPIATOCKA, LOW);
  digitalWrite(PP_SMEROVKA, LOW);
  digitalWrite(PL_SMEROVKA, LOW);
  digitalWrite(ZP_SMEROVKA, LOW);
  digitalWrite(ZL_SMEROVKA, LOW);
  digitalWrite(P_BRZDNE, HIGH);
  digitalWrite(L_BRZDNE, HIGH);
  vbs = millis() + 1500;
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
   
   

