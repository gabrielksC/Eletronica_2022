void velocidade()
{
  if((millis() - Velocidade_millisInicial) > 1000){
    
    noInterrupts();

    VEL = (pulsosVEL*0.04625*2*3.14*RAIO_RODA*3.6); // Calculo da velocidade
    RPM = (pulsosRPM/2 /*numero de pulsos da curva de onda do motor*/)*60; // Calculo do RPM do motor

    Serial.print(RPM);
    Serial.print(" , ");
    Serial.print(VEL);
    Serial.println(' ');

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