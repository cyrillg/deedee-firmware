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

    Serial.print("Directions (L,R): (");
    Serial.print(direction_left);
    Serial.print(",");
    Serial.print(direction_right);
    Serial.println(")");
}

void MotorController::set_motor_speeds(int speed_left, int speed_right)
{
    speed_left = map(speed_left, 0, 100, 0, max_motor_speed);
    speed_right = map(speed_right, 0, 100, 0, max_motor_speed);

    speed_left = min(speed_left, max_motor_speed);
    speed_right = min(speed_right, max_motor_speed);

    analogWrite(speed_pin_left, speed_left);
    analogWrite(speed_pin_right, speed_right);

    Serial.print("Speeds (L,R): (");
    Serial.print(speed_left);
    Serial.print(",");
    Serial.print(speed_right);
    Serial.println(")");
}

