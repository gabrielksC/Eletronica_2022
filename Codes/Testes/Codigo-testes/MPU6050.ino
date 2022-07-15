
void mpu_setup()
{
    Wire.begin();
    mpuA.setAddress(MPU1);
    mpuA.begin();
    delay(1000);
    mpuA.calcGyroOffsets();
    
    mpuB.begin();
    delay(1000);
    mpuB.setAddress(MPU2);
    mpuB.calcGyroOffsets();
}
void mpu_loop()
{
  if((millis()-Mpu_millisInicial) > 1000){

    mpuA.update();
    currentAngleX_A = mpuA.getAngleX();
    currentAngleY_A = mpuA.getAngleY();
    currentAngleZ_A = mpuA.getAngleZ();

    mpuB.update();
    currentAngleX_B = mpuB.getAngleX();
    currentAngleY_B = mpuB.getAngleY();
    currentAngleZ_B = mpuB.getAngleZ();

    Serial.print(currentAngleX_A);
    Serial.print(" , ");
    Serial.print(currentAngleY_A);
    Serial.print(" , ");
    Serial.print(currentAngleZ_A);
    Serial.print(" , ");
    Serial.print(currentAngleX_B);
    Serial.print(" , ");
    Serial.print(currentAngleY_B);
    Serial.print(" , ");
    Serial.print(currentAngleZ_B);
    Serial.println(" ");
 

    Mpu_millisInicial = millis();
  }
}