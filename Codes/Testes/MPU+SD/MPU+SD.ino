#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <time.h>


#include <Wire.h>
#include <MPU6050_light.h>
const int MPU1 = 0x68;
const int MPU2 = 0x69;
float currentAngleX_A, currentAngleY_A, currentAngleZ_A, currentGyroX_A, currentGyroY_A, currentGyroZ_A;
// float currentAngleX_B, currentAngleY_B, currentAngleZ_B;
MPU6050 mpuA(Wire);
// MPU6050 mpuB(Wire);
#define SD_CS 5
String dataMessage;
time_t rawtime;
struct tm *info;
char buffer[80];


void setup() {
  Serial.begin(115200);
  time(&rawtime);

  info = localtime(&rawtime);

  strftime(buffer, 80, "%Hh-%Mm-%Ss_%d-%m-%Y", info);
  Wire.begin();

  mpuA.setAddress(MPU1);
  mpuA.begin();
  
  Serial.println(F("Calculating gyro offset, do not move MPU6050"));
  Serial.println(buffer);
  delay(1000);
  mpuA.calcGyroOffsets();
  Serial.println("Done.");

  SD.begin(SD_CS);  
  if(!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }
  Serial.println("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("ERROR - SD card initialization failed!");
    return;    // init failed
  }
  File file = SD.open("/data.txt");
  if(!file) {
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/data.txt", "ESP32 and SD Card \r\n");
  }
  else {
    Serial.println("File already exists");  
  }
  file.close();
}
void loop() {

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
    // Serial.println(" ");

    logSDCard();
}

// Write the sensor readings on the SD card
void logSDCard() {
  dataMessage =  String(currentAngleX_A) + ' ; ' + String(currentAngleY_A) + ' ; ' + String(currentAngleZ_A) + ' ; ' + String(currentGyroX_A) + ' ; ' + String(currentGyroY_A) + ' ; ' + String(currentGyroZ_A) + "\n";
  // Serial.print("Save data: ");
  // Serial.println(dataMessage);
  appendFile(SD, "/data.txt", dataMessage.c_str());
}
// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}
// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}