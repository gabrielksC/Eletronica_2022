#include <Wire.h>
#include <Adafruit_MLX90614.h>
// #include <SoftwareSerial.h>
// #include <LiquidCrystal_I2C.h>

// Define o endereço utilizado pelo Adaptador I2C
// LiquidCrystal_I2C lcd(0x27,20,4);

#define pinVEL 2 // // Pino de interrupção para rotação da roda
#define pinRPM 3 // Pino de interrupção para rotação do motor

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
 Serial.begin(9600);

 mlx.begin();
 mpu_setup();

 attachInterrupt (digitalPinToInterrupt(pinVEL), tacometro, RISING); //Interrupção para ler pulso da velocidade
 attachInterrupt (digitalPinToInterrupt(pinRPM), RPMmotor, RISING); //Interrupção para ler pulso do RPM
 
}

void loop() {
  mpu_loop();
  mlx_loop();
  velocidade();
}

