#include "Constants.h"
#include <ESP32Servo.h>
#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

class Drivetrain {

private:

    // Settings
    bool bidirectional; // false by default, can be changed
    uint8_t mode; // 0 by default, sets the run mode

    // For BLDC motors
    Servo BLDCMotors[NUM_BLDC_PAIRS]; // Array of BLDC motors
    int BLDCSignals[NUM_BLDC_PAIRS]; // Array containing PWM signals

    // For servomotors
    Servo servos[NUM_SERVO]; // Array of servomotors
    float servoPositions[NUM_SERVO]; // Array containing servo positions/angle (degrees)
    float k_sensitivity; // Determines the responsiveness of vector control (min: 0, max: 1)
    
public:

    // Default constructor
    Drivetrain();

    // Boot sequence
    void initializeAll();
    // Set the pod's mode (idle, manual, auto-guidance, etc.)
    void setMode(uint8_t newMode);
    // Get the pod's current mode
    uint8_t getMode();
    // Run the motors & servos, call everytime values are updated
    void runAll();
    // stop all BLDC motors and reset servo positions
    void stopAll();

    // BLDC methods ------------------------------------------------------------------------------

    // Check out-of-bounds speed inputs
    int checkSpeed(int speed);
    // Set the speed of a specific motor (min: 0, max: 100)
    void setBLDCSpeed(int BLDCMotorPair, int speed);
    // Set the speed of all motors (min: 0, max: 100)
    void setBLDCSpeed(int speed);
    // Change to bidirectional mode -> Could fuck up steering, but won't break the pod (hopefully?)
    void bidirectionalControl (bool newMode);
    // Conversion to PWM signal
    int speedToPWM(int speed);

    // Servo methods -----------------------------------------------------------------------------

    // Check out-of-bounds steering inputs
    int checkSteer(int steerValue);
    // Set sensitivity value if it's not responsive enough for some reason -_-
    void setSensitivity (float newSensitivityValue);
    // Set the linear travel direction forward/backward (min: -100, max: 100)
    void setTravel(int direction);
    // Set the front and back steering values (min: -100, max: 100)
    // negative -> steer left
    // positive -> steer right
    void setSteer(int frontValue, int rearValue);
    // resets the servo positions
    void resetServos();
    
};

#endif