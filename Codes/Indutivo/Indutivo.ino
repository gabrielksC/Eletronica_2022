#include <SoftwareSerial.h> 
#define pinVEL 15 // Pino de interrupção para rotação da roda

unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade  
volatile byte pulsosVEL = 0; //contador de pulsos para velocidade
float VEL = 0; //velocidade em km/h
float RAIO_RODA = 0.266;
int contadorVEL = 0;

void velocidade()
{
  if((millis() - Velocidade_millisInicial) > 1000){
    
    noInterrupts();
    VEL = (pulsosVEL*0.04625*2*3.14*RAIO_RODA*3.6); // Calculo da velocidade

    Serial.print ("  VEL = ");
    Serial.println (VEL);
    pulsosVEL = 0;
    Velocidade_millisInicial = millis();
    
    interrupts();
  }
}

void tacometro() 
{
  pulsosVEL++; // Função chamada no pino de interrupção
}

void setup(){
  Serial.begin(9600);
  attachInterrupt (digitalPinToInterrupt(pinVEL), tacometro, RISING); //Interrupção para ler pulso da velocidade
}
void loop(){
  velocidade();
}