#ifndef CONSTANTS_H
#define CONSTANTS_H

// Misc
const int NUM_BLDC_PAIRS = 4; // How many pairs of BLDC motors
const int NUM_SERVO = 6; // How many servos 

// PWM signals
const int BLDC_MIN_PWM = 1100; // Configure in BLHELI_S firmware
const int BLDC_MAX_PWM = 1900;
const int IDLE_PWM = (BLDC_MAX_PWM + BLDC_MIN_PWM)/2;//       Front
//                                                           |     | 
// BLDC motors pins                                BLDC_0_PIN       BLDC_0_PIN
const int BLDC_0_PIN = 32;//                                |       |     
const int BLDC_1_PIN = 16;//                       BLDC_0_PIN       BLDC_0_PIN
const int BLDC_2_PIN = 17;//       ------->        BLDC_2_PIN       BLDC_2_PIN
const int BLDC_3_PIN = 23;//                                 |     |
//                                                 BLDC_2_PIN       BLDC_2_PIN
// Array containing BLDC pinout                                Back
const int BLDC_PINS[NUM_BLDC_PAIRS] = {BLDC_0_PIN, BLDC_1_PIN, BLDC_2_PIN, BLDC_3_PIN};

// Servomotors pins                                  Front
const int STEER_0_PIN = 27;//                       |     |
const int STEER_1_PIN = 33;//             STEER_0_PIN     STEER_1_PIN
const int PROP_0_PIN = 26; //     ---->    PROP_0_PIN     PROP_1_PIN
const int PROP_1_PIN = 25; //                      |       |
const int STEER_2_PIN = 18;//             STEER_2_PIN     STEER_3_PIN
const int STEER_3_PIN = 19;//                         Back

// Servo array order is: steer_0, steer_1, prop_0, prop_1, steer_2, steer_3
const int SERVO_PINS[NUM_SERVO] = {STEER_0_PIN, STEER_1_PIN, PROP_0_PIN, PROP_1_PIN, STEER_2_PIN, STEER_3_PIN};
// Servomotors initial positions, same order as previous array
const float SERVO_INIT[NUM_SERVO] = {122, 63, 97, 101, 110, 69};
// Servomotors maximum angle (in degrees) allowed (+- from initial position)
const float MAX_ANGLE = 15;

//LIDAR pins 
const uint8_t NUM_LIDAR = 2;
const uint8_t X_SHUT_PINS[] = { 18, 19 };

#endif