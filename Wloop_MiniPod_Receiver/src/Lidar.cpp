#include <Wire.h>
#include <VL53L1X.h>
#include "Constants.h"
#include "Lidar.h"

Lidar::Lidar() {
    target = 150.0; // Default target distance is 150 mm
}

void Lidar::initialize(uint8_t XShutPin, int I2CAddress) {
    digitalWrite(XShutPin, LOW);
    pinMode(XShutPin, INPUT);
    delay(10);
    if (!sensor.init())
        while(1);
    sensor.setAddress(I2CAddress);
    sensor.startContinuous(20);
}

void Lidar::setTarget(float newTarget) {
    target = newTarget;
}

int Lidar::measureDistance() {
    distance = sensor.read();
    return distance;
}

int Lidar::steer() {
    distance = sensor.read();
    int error = (target-distance);
    if (error > target)
        error = target;
    else if (error <  -target)
        error = -target;
    return (error/target)*100*LIDAR_Kp;
}