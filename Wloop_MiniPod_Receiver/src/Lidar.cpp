#include <Wire.h>
#include <VL53L1X.h>
#include "Constants.h"
#include "Lidar.h"

Lidar::Lidar() {
    target = 100; // Default target distance is 100 mm
}

void Lidar::initialize() {

}

void Lidar::setTarget(float newTarget) {
    target = newTarget;
}

float Lidar::measureDistance() {

}