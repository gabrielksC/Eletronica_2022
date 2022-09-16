
void mlx_loop(){
  if((millis()-Temp_millisInicial) > 100){
    temp_amb = mlx.readAmbientTempC();
    temp_obj = mlx.readObjectTempC();
    Temp_millisInicial = millis();
  }
}