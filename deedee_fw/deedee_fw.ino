#include <SerialManager.h>
#include <MotorController.h>

#define BAUDRATE 9600

MotorController motors;
SerialManager serman(BAUDRATE);

void setup() {
    serman.init();
}

void loop() {
    int packet_type = serman.receive_packet();
    if(packet_type>=0)
    {
        switch(packet_type)
        {
            case MMC:
                MotorCmd cmd;
                serman.retrieve_packet(cmd);
                motors.send_speeds(cmd.speed_left, cmd.speed_right);
                break;
        }
    }
}

