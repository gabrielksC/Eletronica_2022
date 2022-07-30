
void mpu_setup()
{
      Wire.begin();

    mpuA.setAddress(MPU1);
    mpuA.begin();
   
    Serial.println(F("Calculating gyro offset, do not move MPU6050"));
    delay(1000);
    mpuA.calcGyroOffsets();
    Serial.println("Done.");
    
    // Wire.begin();
    // mpuB.setAddress(mpub);
    // mpuB.begin();

    // Serial.println(F("Calculating gyro offset, do not move MPU6050"));
    // delay(1000);
    // mpuB.calcGyroOffsets();
    // Serial.println("Done.");
}
void mpu_loop()
{
  if((millis()-Mpu_millisInicial) > 1000){

     mpuA.update();
    currentAngleX_A = mpuA.getAngleX();
    currentAngleY_A = mpuA.getAngleY();
    currentAngleZ_A = mpuA.getAngleZ();
    currentGyroX_A = mpuA.getGyroX();
    currentGyroY_A = mpuA.getGyroY();
    currentGyroZ_A = mpuA.getGyroZ();

    // mpuB.update();
    // currentAngleX_B = mpuB.getAngleX();
    // currentAngleY_B = mpuB.getAngleY();
    // currentAngleZ_B = mpuB.getAngleZ();
    
    // Serial.print(currentAngleX_B);
    // Serial.print(" , ");
    // Serial.print(currentAngleY_B);
    // Serial.print(" , ");
    // Serial.print(currentAngleZ_B);
    // Serial.println(" ");

    Mpu_millisInicial = millis();
  }
}