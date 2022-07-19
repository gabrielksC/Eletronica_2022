#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050_light.h>

// Define o endereço utilizado pelo Adaptador I2C
LiquidCrystal_I2C lcd(0x27,20,4);

// RPM E VELOCIDADE
#define pinVEL 2 // // Pino de interrupção para rotação da roda
#define pinRPM 3 // Pino de interrupção para rotação do motor
unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade 
volatile byte pulsosVEL = 0; //contador de pulsos para velocidade
volatile byte pulsosRPM = 0; //contador de pulsos para velocidade
unsigned int RPM = 0; //frequencia de rotacoes em RPM
unsigned int VEL = 0; //velocidade em km/h
float RAIO_RODA = 0.266;

// TEMP
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
unsigned long Temp_millisInicial = 0; //tempo inicial para temperatura 
double temp_amb; 
double temp_obj; 

// GIROSCOPIO
// Endereco I2C do sensor MPU-6050
const int MPU1 = 0x68;
const int MPU2 = 0x69;
float currentAngleX_A, currentAngleY_A, currentAngleZ_A, currentGyroX_A, currentGyroY_A, currentGyroZ_A;
float currentAngleX_B, currentAngleY_B, currentAngleZ_B;

MPU6050 mpuA(Wire);
// MPU6050 mpuB(Wire);
unsigned long int Mpu_millisInicial = 0; // tempo inicial para aceleração

void setup() {
 Serial.begin(115200);

 mlx.begin();
 mpu_setup();

//  lcd.begin(20, 4);
 lcd.init();
 lcd.backlight();

 attachInterrupt (digitalPinToInterrupt(pinVEL), tacometro, RISING); //Interrupção para ler pulso da velocidade
 attachInterrupt (digitalPinToInterrupt(pinRPM), RPMmotor, RISING); //Interrupção para ler pulso do RPM
 
}

void loop() {
  
  mlx_loop();
  velocidade();
  mpu_loop();
  display();
}