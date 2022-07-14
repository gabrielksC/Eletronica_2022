#include <esp_now.h>
#include <WiFi.h>

#include <SoftwareSerial.h> 
#define pinVEL 36 // Pino de interrupção para rotação da roda

unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade  
volatile byte pulsosVEL = 0; //contador de pulsos para velocidade
float RAIO_RODA = 0.266;

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  float VEL = 0; //velocidade em km/h
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

void velocidade()
{
  if((millis() - Velocidade_millisInicial) > 1000){
    
    noInterrupts();

    myData.VEL = (pulsosVEL*0.04625*2*3.14*RAIO_RODA*3.6); // Calculo da velocidade
    pulsosVEL = 0;

    Velocidade_millisInicial = millis();
    
    interrupts();
  }
}

void tacometro() 
{
  pulsosVEL++; // Função chamada no pino de interrupção
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  attachInterrupt (digitalPinToInterrupt(pinVEL), tacometro, RISING); //Interrupção para ler pulso da velocidade

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
 
void loop() {
  velocidade();
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(500);
}