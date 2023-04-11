#ifndef LIDAR_H
#define LIDAR_H

class Lidar {

private:
    VL53L1X sensor;
    int distance;
    float target;

public:

    // Default constructor
    Lidar();

    // Initialization sequence
    void initialize(uint8_t XShutPin, int I2CAddress);

    // Set a new target distance
    void setTarget(float newTarget);
    // Read current distance value, stores it in "distance" and returns the value
    int measureDistance();
    // Lidar steer values
    int steer();

};

#endif