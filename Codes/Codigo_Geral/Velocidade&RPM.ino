unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade 

volatile byte pulsosVEL = 0; //contador de pulsos para velocidade
volatile byte pulsosRPM = 0; //contador de pulsos para velocidade
unsigned int RPM = 0; //frequencia de rotacoes em RPM
unsigned int VEL = 0; //velocidade em km/h
float RAIO_RODA = 0.266;

void velocidade()
{
  if((millis() - Velocidade_millisInicial) > 1000){
    
    noInterrupts();

    VEL = (pulsosVEL*0.04625*2*3.14*RAIO_RODA*3.6); // Calculo da velocidade
    RPM = (pulsosRPM/2 /*numero de pulsos da curva de onda do motor*/)*60; // Calculo do RPM do motor

    Serial.print ("  VEL = ");
    Serial.println (VEL);

    pulsosVEL = 0;
    pulsosRPM = 0;

    Velocidade_millisInicial = millis();
    
    interrupts();
  }
}

void tacometro() 
{
  pulsosVEL++; // Função chamada no pino de interrupção
}

void RPMmotor() 
{
  pulsosRPM++; // Função chamada no pino de interrupção
}