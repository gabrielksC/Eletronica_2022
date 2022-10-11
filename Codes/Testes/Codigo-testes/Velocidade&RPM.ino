

void velocidade()
{
  if((millis() - Velocidade_millisInicial) > 1000){
    
    noInterrupts();
    float VEL_anterior = VEL;
    VEL = (pulsosVEL*0.04625*2.0*3.14*RAIO_RODA*3.6); // Calculo da velocidade
    // VEL = (pulsosVEL*0.04625*PERIMETRO_RODA*3.6); // Calculo da velocidade
    RPM = (pulsosRPM/2.0 /*numero de pulsos da curva de onda do motor*/)*60.0; // Calculo do RPM do motor
    DISTANCIA += (VEL/3.6); //METROS
    ACC = (VEL - VEL_anterior);
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