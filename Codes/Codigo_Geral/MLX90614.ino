
unsigned long Temp_millisInicial = 0; //tempo inicial para temperatura 

double temp_amb; 
double temp_obj; 

void mlx_loop(){
  if((millis()-Temp_millisInicial) > 1000){
  temp_amb = mlx.readAmbientTempC();
  temp_obj = mlx.readObjectTempC();
  Temp_millisInicial = millis();
  }
}