int Ledvermelho = 13;
int LedAmarela = 12;
int Ledverde = 9;


void setup() {
  pinMode(Ledvermelho, OUTPUT);
  pinMode(LedAmarela, OUTPUT);
  pinMode(Ledverde, OUTPUT);
  
}

void loop() {
  digitalWrite(Ledvermelho, HIGH);
  digitalWrite(LedAmarela, LOW);
  digitalWrite(Ledverde, LOW);
  delay(5000);

  digitalWrite(Ledvermelho, LOW);
  digitalWrite(LedAmarela, HIGH);
  digitalWrite(Ledverde, LOW);
  delay(2000);

  digitalWrite(Ledverde, HIGH);
  digitalWrite(LedAmarela, LOW);
  digitalWrite(Ledverde, LOW);
  delay(5000);
  
}
