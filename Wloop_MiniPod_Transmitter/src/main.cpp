#include <Arduino.h>
#include "Constants.h"
#include "Controller.h"
#include <esp_now.h>
#include <WiFi.h>

// Create controller object
Controller controllerPad;

// ESP-NOW setup -----------------------------------------------------------------------------------
// MAC address of the receiver board 
uint8_t receiverMACAddress[] = {0xC8, 0xF0, 0x9E, 0x9E, 0xE2, 0xD8};
// Data structure of package
typedef struct dataPack {
  int jStick_x;
  int jStick_y;
  int BLDCPower;
} dataPack;
// Create structured dataPack object
dataPack data;
// Peer info
esp_now_peer_info_t peerInfo;
// Callback function when sending data
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status:\t ");
  Serial.println(status);
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Message sent" : "Message failed");
}

// "Arduino" code ---------------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);

  // Set ESP32 controller board as WiFi station
  WiFi.mode(WIFI_STA);
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ERROR initializing ESP-NOW");
    return;
  }
  else
    Serial.println("Initialization complete");

  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, receiverMACAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  else
    Serial.println("Success: peer added");
}

void loop() {

  // Set the data to be sent
  data.jStick_x = controllerPad.getxVal();
  data.jStick_y = controllerPad.getyVal();
  data.BLDCPower = controllerPad.getPower();

  Serial.println(controllerPad.getxVal());

  // Send data pack to receiver (pod)
  esp_err_t status = esp_now_send(receiverMACAddress, (uint8_t*) &data, sizeof(data));
  if (status != ESP_OK) {
    Serial.println("Sending ERROR");
  }

  // Refresh/update speed
  delay(20);
}