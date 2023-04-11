#include <Arduino.h>
#include "Controller.h"
#include "Constants.h"

Controller::Controller() {
    int x_val = 0;
    int y_val = 0;
    int potPower = 0;
}

int Controller::getxVal() {
    x_val = analogRead(JOYSTICK_X_PIN);
    x_val = map(x_val+X_OFFSET, 0, 4095, -100, 100);
    return x_val;
}

int Controller::getyVal() {
    y_val = analogRead(JOYSTICK_Y_PIN);
    y_val = map(y_val+Y_OFFSET, 0, 4095, -100, 100);
    return y_val;
}

int Controller::getPower() {
    potPower = analogRead(POTENTIOMETER_PIN);
    potPower = map(potPower, 0, 4095, 0, 100);
    return potPower;
}

void Controller::printAll() {
    Serial.print("x_axis: ");
    Serial.print(x_val);
    Serial.print("\ty_axis: ");
    Serial.print(y_val);
    Serial.print("\tpower: ");
    Serial.println(potPower);
}