#include <MPU6050_light.h>
#include "Wire.h"

float currentAngleX_A, currentAngleY_A, currentAngleZ_A;
float currentAngleX_B, currentAngleY_B, currentAngleZ_B;

uint8_t mpua = 0x68;
// uint8_t mpub = 0x69;

MPU6050 mpuA(Wire);
// MPU6050 mpuB(Wire);

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    mpuA.setAddress(mpua);
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
void loop()
{
    mpuA.update();
    currentAngleX_A = mpuA.getAngleX();
    currentAngleY_A = mpuA.getAngleY();
    currentAngleZ_A = mpuA.getAngleZ();

    // mpuB.update();
    // currentAngleX_B = mpuB.getAngleX();
    // currentAngleY_B = mpuB.getAngleY();
    // currentAngleZ_B = mpuB.getAngleZ();

    Serial.print(currentAngleX_A);
    Serial.print(" , ");
    Serial.print(currentAngleY_A);
    Serial.print(" , ");
    Serial.print(currentAngleZ_A);
    Serial.print(" , ");
    // Serial.print(currentAngleX_B);
    // Serial.print(" , ");
    // Serial.print(currentAngleY_B);
    // Serial.print(" , ");
    // Serial.print(currentAngleZ_B);
    Serial.println(" ");
}