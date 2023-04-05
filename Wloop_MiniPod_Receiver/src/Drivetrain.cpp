#include "Drivetrain.h"
#include <ESP32Servo.h>
#include "Constants.h"

// Class constructor
Drivetrain::Drivetrain() { 
    bidirectional = false; // False by default
    mode = 0; // 0 by default
    k_sensitivity = 0.8;
    // Initialize motor speeds
    for (int i = 0; i < NUM_BLDC_PAIRS; i++) {
        BLDCSignals[i] = IDLE_PWM;
    }
    // Initialize servo positions
    for (int i = 0; i < NUM_SERVO; i++) {
        servoPositions[i] = SERVO_INIT[i];
    }
}

void Drivetrain::initializeAll() {
    // Attach all BLDC motors
    for (int i = 0; i < NUM_BLDC_PAIRS; i++) {
        BLDCMotors[i].attach(BLDC_PINS[i]);
    }
    // Attach all servos
    for (int i = 0; i < NUM_SERVO; i++) {
        servos[i].attach(SERVO_PINS[i]);
    }
    // Idle
    stopAll();
}

void Drivetrain::setMode(uint8_t newMode) {
    mode = newMode;
}

uint8_t Drivetrain::getMode() {
    return mode;
}

void Drivetrain::runAll() {
    // Send signal to BLDC motors
    for (int i = 0; i < NUM_BLDC_PAIRS; i++) {
        BLDCMotors[i].writeMicroseconds(BLDCSignals[i]);
    }
    // Send signal to servos
    for (int i = 0; i < NUM_SERVO; i++) {
        servos[i].write(servoPositions[i]);
    }
}

void Drivetrain::stopAll() {
    // Set servos to initial positions
    for (int i = 0; i < NUM_SERVO; i++) {
        servoPositions[i] = SERVO_INIT[i];
    }
    // Set BLDC motors to idle
    setBLDCSpeed(0);
    
    // Send signal to all motors/servos
    runAll();
}

// BLDC methods ------------------------------------------------------------------------------
int Drivetrain::checkSpeed(int speed) {
    // Handle out-of-bounds signals
    if (speed > 100)
        return 100;
    else if (bidirectional && speed < -100) {
        return -100;
    }
    else if (speed < 0)
        return 0;
    return speed;
}

void Drivetrain::setBLDCSpeed(int BLDCMotorPair, int speed) {
    BLDCSignals[BLDCMotorPair] = speedToPWM(checkSpeed(speed));

    runAll();
}

void Drivetrain::setBLDCSpeed(int speed) {
    int PWMSignal = speedToPWM(checkSpeed(speed));
    for (int i = 0; i < NUM_BLDC_PAIRS; i++) {
        BLDCSignals[i] = PWMSignal;
    }

    runAll();
}

void Drivetrain::bidirectionalControl(bool newMode) {
    bidirectional = newMode;
}

int Drivetrain::speedToPWM(int speed) {
    if (bidirectional)
        return map(speed, -100, 100, BLDC_MIN_PWM, BLDC_MAX_PWM);
    else
        return map(speed, 0, 100, IDLE_PWM, BLDC_MAX_PWM);
}

// Servo methods -----------------------------------------------------------------------------
int Drivetrain::checkSteer(int steerValue) {
    if (steerValue > 100)
        return 100;
    else if (steerValue < -100)
        return -100;
    return steerValue;
}

void Drivetrain::setSensitivity (float newSensitivityValue) {
    k_sensitivity = newSensitivityValue;
}

void Drivetrain::setTravel(int direction) {
    // Adjust input
    direction = checkSteer(direction);
    direction *= k_sensitivity;
    // Signs for "direction" might need to be changed depending on the pod configuration
    servoPositions[2] = map(direction, -100, 100, SERVO_INIT[2]-MAX_ANGLE, SERVO_INIT[2]+MAX_ANGLE);
    servoPositions[3] = map(-direction, -100, 100, SERVO_INIT[3]-MAX_ANGLE, SERVO_INIT[3]+MAX_ANGLE);

    runAll();
}

void Drivetrain::setSteer(int frontValue, int rearValue) {
    // Adjust input
    frontValue = (checkSteer(frontValue))*k_sensitivity;
    rearValue = (checkSteer(rearValue))*k_sensitivity;
    // Once again, I might've fucked up the signs
    servoPositions[0] = map(frontValue, -100, 100, SERVO_INIT[0]-MAX_ANGLE, SERVO_INIT[0]+MAX_ANGLE);
    servoPositions[1] = map(frontValue, -100, 100, SERVO_INIT[1]-MAX_ANGLE, SERVO_INIT[1]+MAX_ANGLE);
    servoPositions[4] = map(-rearValue, -100, 100, SERVO_INIT[4]-MAX_ANGLE, SERVO_INIT[4]+MAX_ANGLE);
    servoPositions[5] = map(-rearValue, -100, 100, SERVO_INIT[5]-MAX_ANGLE, SERVO_INIT[5]+MAX_ANGLE);

    runAll();
}

void Drivetrain::resetServos() {
    for (int i = 0; i < NUM_SERVO; i++) {
        servoPositions[i] = SERVO_INIT[i];
    }

    runAll();
}