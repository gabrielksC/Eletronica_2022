// espnow
#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
// 94:B5:55:2D:0B:08
uint8_t broadcastAddress[] = {0x98, 0xB5, 0x55, 0x2D, 0x0B, 0x08};

typedef struct struct_message {
  String transmition_message;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

// SD CARD
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <time.h>
#define SD_CS 5
String dataMessage;

// Define o endereço utilizado pelo Adaptador I2C
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

// RPM E VELOCIDADE
#include <SoftwareSerial.h>
#define pinVEL 33 // // Pino de interrupção para rotação da roda
#define pinRPM 30 // Pino de interrupção para rotação do motor
 
volatile byte pulsosVEL = 0; //contador de pulsos para velocidade
volatile byte pulsosRPM = 0; //contador de pulsos para velocidade
float RPM = 0; //frequencia de rotacoes em RPM
float VEL = 0; //velocidade em km/h
const float RAIO_RODA = 0.266;

// TEMP
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); 
double temp_amb; 
double temp_obj; 

// GIROSCOPIO
#include <Wire.h>
#include <MPU6050_light.h>
const int MPU1 = 0x68;
const int MPU2 = 0x69;
float currentAngleX_A, currentAngleY_A, currentAngleZ_A, currentGyroX_A, currentGyroY_A, currentGyroZ_A;
// float currentAngleX_B, currentAngleY_B, currentAngleZ_B;
MPU6050 mpuA(Wire);
// MPU6050 mpuB(Wire);

void setup() {
 Serial.begin(115200);

 mlx.begin();
 mpu_setup();
 SD_setup();
 espnow_setup();
 
//  lcd.begin(20, 4);
 lcd.init();
 lcd.backlight();

  pinMode(pinVEL, INPUT);
 attachInterrupt (pinVEL, tacometro, RISING); //Interrupção para ler pulso da velocidade

  pinMode(pinRPM, INPUT);
 attachInterrupt (pinRPM, tacometro, RISING); //Interrupção para ler pulso RPM
 
//  attachInterrupt (digitalPinToInterrupt(pinRPM), RPMmotor, RISING); //Interrupção para ler pulso do RPM
 
}

void loop() {
  
  mlx_loop();
  velocidade();
  mpu_loop();
  espnow_loop();
  SD_loop();
  display();

  Serial.print(temp_obj);
  Serial.print(" , ");
  Serial.print(temp_amb);
  Serial.print(" , ");
  Serial.print(RPM);
  Serial.print(" , ");
  Serial.print(VEL);
  Serial.print(" , ");
  Serial.print(currentAngleX_A);
  Serial.print(" , ");
  Serial.print(currentAngleY_A);
  Serial.print(" , ");
  Serial.print(currentAngleZ_A);
  Serial.println();

}