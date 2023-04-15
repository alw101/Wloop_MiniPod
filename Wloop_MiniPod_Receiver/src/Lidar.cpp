#include <Wire.h>
#include <VL53L1X.h>
#include "Constants.h"
#include "Lidar.h"

Lidar::Lidar() {
    target = 100; // Default target distance is 100 mm
    sensorNum = 0;
}

void Lidar::initialize(int sensorNum) {
    xShutPin = xShutPin[sensorNum];

    // Disable/reset all sensors by driving their XSHUT pins low.
        pinMode(xShutPin, OUTPUT);
        digitalWrite(xShutPin, LOW);

    // Enable, initialize, and start each sensor, one by one.
        // Stop driving this sensor's XSHUT low. This should allow the carrier
        // board to pull it high. hen wait a bit for the sensor to start up.
        pinMode(xShutPin, INPUT);
        delay(10);

        sensor.setTimeout(500);
        if (sensor.init()) {
            Serial.print("Failed to detect and initialize sensor ");
            Serial.println(sensorNum);
        }

        // Each sensor must have its address changed to a unique value other than
        // the default of 0x29 (except for the last one, which could be left at
        // the default). To make it simple, we'll just count up from 0x2A.
        sensor.setAddress(0x2A + sensorNum);
        sensor.startContinuous(50);
}

void Lidar::setTarget(float newTarget) {
    target = newTarget;
}

float Lidar::measureDistance() {
    uint16_t distance = sensor.read();
}