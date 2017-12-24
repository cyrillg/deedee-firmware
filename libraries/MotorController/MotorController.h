/*
  MotorController.h - Library for moving a 2 wheels mobile
  robot using PWM DC control.
  Created by Cyrill Guillemot, December 24, 2017.
*/

#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"

class MotorController
{
    public:
        MotorController();
        void send_speeds(int speed_left, int speed_right);
        int get_max_motor_speed();
        void set_max_motor_speed(int value);
    private:
        int direction_pin_left;
        int speed_pin_left;
        int speed_pin_right;
        int direction_pin_right;
        int max_motor_speed;

        void setup_control_pins();
        void set_motor_directions(int speed_left, int speed_right);
        void set_motor_speeds(int speed_left, int speed_right);
};

#endif
