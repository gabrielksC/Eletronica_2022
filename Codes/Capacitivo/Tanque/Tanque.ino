const int Sinal_1 = 8; //PINO DIGITAL UTILIZADO PELO SENSOR
const int Sinal_2 = 12; //PINO DIGITAL UTILIZADO PELO LED
 
void setup(){
  Serial.begin(115200);
  
  int result = 0;
  pinMode(Sinal_1, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(Sinal_2, INPUT); //DEFINE O PINO COMO ENTRADA
  attachInterrupt (Sinal_1, funcao_ISR, CHANGE); //Interrupção para ler pulso RPM
  attachInterrupt (Sinal_2, funcao_ISR, CHANGE); //Interrupção para ler pulso RPM
 
}
void loop(){
  bool status_1 = digitalRead(Sinal_1);
  bool status_2 = digitalRead(Sinal_2);
  Serial.println(status_1 + ' ' + status_2 + ' ' + result);
}

void IRAM_ATTR funcao_ISR()
{
  if(status_1 == HIGH && status_2 == HIGH) result = 2;
  else if (status_1 == HIGH && status_2 == LOW) result = 1;
  else if (status_1 == LOW && status_2 == LOW) result = 0;
  return result;
}
 