const int DIODA = 2;
const int FOTOREZISTOR = A0;

void setup() {
  Serial.begin(9600);
  pinMode(DIODA, OUTPUT);
}

void loop() {
  float u = (analogRead(FOTOREZISTOR) / 1023.0) * 5.0;
  float u2 = 5 - u;
  float r2 = 2200000;
  float i = u2 / r2;
  float r = u / i; 
  if (r > 50000000){
    digitalWrite (DIODA, HIGH);
  } else{
    digitalWrite (DIODA, LOW);
  }

  Serial.print("U = ");
  Serial.print(u);
  Serial.print(", R = ");
  Serial.println(r);

  delay(200);
}
