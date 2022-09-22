
void SD_setup() {

  // Initialize SD card
  SD.begin(SD_CS);  
  while(!SD.begin(SD_CS)) {
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
  File file = SD.open("/datalog.txt");
  if(!file) {
    writeFile(SD, "/datalog.csv", "angleX , angleY , angleZ , gyroX , gyroY , gyroZ , temp_obj , temp_amb\n");
  }
  file.close();
}

// Write the sensor readings on the SD card
void SD_loop() {
  dataMessage =  String(currentAngleX_A) + " , " + String(currentAngleY_A) + " , " + String(currentAngleZ_A) + " , " + String(currentGyroX_A) + " , " + String(currentGyroY_A) + " , " + String(currentGyroZ_A) + " , " + String(temp_obj) + " , " + String(temp_amb) + " , " + String(VEL) + " , " + String(RPM) + "\n";
  // Serial.print("Save data: ");
  // Serial.println(dataMessage);
  appendFile(SD, "/datalog.csv", dataMessage.c_str());
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
  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(!file.print(message)) {
    Serial.println("Append failed");
  }
  file.close();
}
