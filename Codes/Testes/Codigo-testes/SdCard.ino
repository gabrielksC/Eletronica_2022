/*
 * SD Card Module Interfacing with ESP32 Wifi + Bluetooth Module
 * https://www.electroniclinic.com/
 */

#include "FS.h"
#include "SD.h"
#include <SPI.h>

#define SD_CS 5
String dataMessage;

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
  // Serial.printf("Appending to file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    // Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    // Serial.println("Message appended");
  } else {
    // Serial.println("Append failed");
  }
  file.close();
}


void SD_setup() {
  Serial.begin(115200);

  // Initialize SD card
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
  File file = SD.open("/dataMPU.txt");
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

// Write the sensor readings on the SD card
void logSDCard() {
  dataMessage =  String(currentAngleX_A) + String(currentAngleY_A) + String(currentAngleZ_A) + String(currentGyroX_A) + String(currentGyroY_A) + String(currentGyroZ_A) + "\n";
  // Serial.print("Save data: ");
  // Serial.println(dataMessage);
  appendFile(SD, "/data.txt", dataMessage.c_str());
}