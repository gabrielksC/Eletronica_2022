void iniciaInfra(){
    // Initialize thermal IR sensor
  if (!therm.begin()){
    Serial.print("erro na inicialização infravermelho");
  }
  therm.setUnit(TEMP_C); // Set the library's units to Farenheit
  // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or TEMP_K for Kelvin.
}



void tempInfra() {
  iniciaInfra();
  delay(10);
  if (therm.read()){ // On success, read() will return 1, on fail 0.
    //Serial.print("Object: " + String(therm.object(), 2));
    //Serial.write('°'); // Degree Symbol
    //Serial.println("C");
    //Serial.print("Ambient: " + String(therm.ambient(), 2));
    //Serial.write('°'); // Degree Symbol
    //Serial.println("C");
    //Serial.println();
    temp_amb = therm.ambient(); 
    temp_obj = therm.object();     

  }
}
