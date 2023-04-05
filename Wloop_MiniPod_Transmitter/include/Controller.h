#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {

private:

    int x_val;
    int y_val;
    int potPower;

public:

    // Default contructor
    Controller();

    // returns the value of the joystick's x-axis (min: -100, max: 100)
    int getxVal();
    // returns the value of the joystick's y-axis (min: -100, max: 100)
    int getyVal();
    // returns the value of the potentiometer (min: 0, max: 100)
    int getPower();

};
#endif