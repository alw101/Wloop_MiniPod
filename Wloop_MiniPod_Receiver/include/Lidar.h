#ifndef LIDAR_H
#define LIDAR_H

class Lidar {

private:

    float distance;
    float target;
    VL53L1X sensor;
    xShutPin;
    sensorNum;


public:

    // Default constructor
    Lidar();

    // Initialization sequence
    void initialize();

    // Set a new target distance
    void setTarget(float newTarget);
    // Read current distance value, stores it in "distance" and returns the value
    float measureDistance();
    

};

#endif