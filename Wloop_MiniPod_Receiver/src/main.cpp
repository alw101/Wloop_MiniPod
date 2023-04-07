#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "Constants.h"
#include "Drivetrain.h"

// Create a drivetrain object (which is the pod duh)
Drivetrain pod;

// Data structure of received package
typedef struct dataPack {
  int jStick_x;
  int jStick_y;
  int BLDCPower;
} dataPack;

// Create structured dataPack object
dataPack data;

//Callback when data is received
void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));
  // Code that will run everytime data is received -----------------------------------------------

  pod.setSteer(data.jStick_x, -data.jStick_x);
  pod.setTravel(data.jStick_y);
  pod.setBLDCSpeed(data.BLDCPower);
  

  /*switch(pod.getMode()) {
    case 1: // Manual mode


      break;
    case 2: // Manual + auto-guidance


      break;
    default: // Stops the pod


  }*/

}

void setup() {

  Serial.begin(9600);

  pod.initializeAll();

  // Set ESP32 controller board as WiFi station
  WiFi.mode(WIFI_STA);
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Do not write the main code here, this loop only handles signal loss
  // Pod behavior should be specified in the ESP-NOW callback function
}