#include <SerialManager.h>
#include <MotorController.h>

#define BAUDRATE 9600

MotorController motors;
SerialManager serman(BAUDRATE);

void setup() {
    serman.init();
}

void loop() {
    int packet[3];
    int new_packet = serman.handle_packet(packet);
    if(new_packet==0)
    {
        Serial.print("Field: ");
        Serial.print(packet[0]);
        Serial.print(" ; Left speed: ");
        Serial.print(packet[1]);
        Serial.print(" ; Right speed: ");
        Serial.println(packet[2]);
        motors.send_speeds(packet[1], packet[2]);
    }
}

