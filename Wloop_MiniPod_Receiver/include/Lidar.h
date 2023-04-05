#ifndef LIDAR_H
#define LIDAR_H

class Lidar {

private:

    float distance;
    float target;

public:

    // Default constructor
    Lidar();

    // Set a new target distance
    void setTarget(float newTarget);

};

#endif