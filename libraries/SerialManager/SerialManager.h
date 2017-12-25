/*
  SerialManager.h - Library to communicate through serial
  Created by Cyrill Guillemot, December 24, 2017.
*/

#ifndef SerialManager_h
#define SerialManager_h

#include "Arduino.h"
#include "PacketTypes.h"

#define SER Serial
#define DEBUG_SER Serial1
#define BUF_SIZE 128
#define MAX_FIELDS_SIZE 10
#define SERIAL_TIMEOUT 100

class SerialManager
{
    public:
        SerialManager(int baud_rate_param);
        void init();
        int receive_packet();
        int retrieve_packet(MotorCmd &packet);

    private:
        int baud_rate;
        char start_char;
        char end_char;
        char receive_buffer[BUF_SIZE];
        int current_packet[MAX_FIELDS_SIZE];
        int current_packet_type;

        int store_packet();
        void split_packet(int &packet_length);
        bool is_valid_packet(int packet_length, int &packet_type);
        bool is_known_type(int packet_type);
        void clear_receive_buffer();
        void clear_current_packet();
};

#endif
