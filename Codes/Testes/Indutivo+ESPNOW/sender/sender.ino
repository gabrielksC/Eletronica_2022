#include <esp_now.h>
#include <WiFi.h>
#include <SoftwareSerial.h> 
#define pinVEL 36 // Pino de interrupção para rotação da roda

unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade  
volatile byte pulsosVEL = 0; //contador de pulsos para velocidade
float VEL = 0; //velocidade em km/h
float RAIO_RODA = 0.266;

// REPLACE WITH YOUR RECEIVER MAC Address
// 0C:B8:15:F8:A3:88
uint8_t broadcastAddress[] = {0x0C, 0xB8, 0x15, 0xF8, 0xA3, 0x88};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  float Velocidade = 0; //velocidade em km/h
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void velocidade()
{
  if((millis() - Velocidade_millisInicial) > 1000){
    
    noInterrupts();

    VEL = (pulsosVEL*0.04625*2*3.14*RAIO_RODA*3.6); // Calculo da velocidade
    pulsosVEL = 0;
    Velocidade_millisInicial = millis();
    
    interrupts();
  }
}
void tacometro() 
{
  pulsosVEL++; // Função chamada no pino de interrupção
}

void espnow_setup()
{
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  attachInterrupt (digitalPinToInterrupt(pinVEL), tacometro, RISING); //Interrupção para ler pulso da velocidade
  espnow_setup();
}
 
void loop() {

  velocidade();
  myData.Velocidade = VEL;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  Serial.println(myData.Velocidade);
}