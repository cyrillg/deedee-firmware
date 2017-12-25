/*
  MotorController.h - Library for controlling a 2 wheels mobile robot using PWM.
  Created by Cyrill Guillemot, December 24, 2017.
*/

#include "Arduino.h"
#include "MotorController.h"

MotorController::MotorController()
{
    direction_pin_left = 4;
    speed_pin_left = 5;
    speed_pin_right = 6;
    direction_pin_right = 7;
    max_motor_speed = 255;

    setup_control_pins();
}

void MotorController::setup_control_pins()
{
    int i;
    for(i=4;i<=7;i++)
        pinMode(i, OUTPUT);
}


void MotorController::set_max_motor_speed(int value)
{
    max_motor_speed = value;
}

int MotorController::get_max_motor_speed()
{
    return max_motor_speed;
}


void MotorController::send_speeds(int speed_left, int speed_right)
{
    set_motor_directions(speed_left, speed_right);
    set_motor_speeds(speed_left, speed_right);
}

void MotorController::set_motor_directions(int speed_left, int speed_right)
{
    int direction_left = (speed_left>0) ? HIGH:LOW;
    int direction_right = (speed_right>0) ? HIGH:LOW;

    digitalWrite(direction_pin_left, direction_left);
    digitalWrite(direction_pin_right, direction_right);

    DEBUG_SER.print("Directions (L,R): (");
    DEBUG_SER.print(direction_left);
    DEBUG_SER.print(",");
    DEBUG_SER.print(direction_right);
    DEBUG_SER.println(")");
}

void MotorController::set_motor_speeds(int speed_left, int speed_right)
{
    speed_left = map(speed_left, 0, 100, 0, max_motor_speed);
    speed_right = map(speed_right, 0, 100, 0, max_motor_speed);

    speed_left = sign(speed_left) * min(abs(speed_left), max_motor_speed);
    speed_right = sign(speed_right) * min(abs(speed_right), max_motor_speed);

    analogWrite(speed_pin_left, speed_left);
    analogWrite(speed_pin_right, speed_right);

    DEBUG_SER.print("Speeds (L,R): (");
    DEBUG_SER.print(speed_left);
    DEBUG_SER.print(",");
    DEBUG_SER.print(speed_right);
    DEBUG_SER.println(")");
}

int MotorController::sign(int value)
{
    if(value > 0) return 1;
    if(value < 0) return -1;
    return 0;
}
