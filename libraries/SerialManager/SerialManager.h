/*
  SerialManager.h - Library to communicate through serial
  Created by Cyrill Guillemot, December 24, 2017.
*/

#ifndef SerialManager_h
#define SerialManager_h

#include "Arduino.h"

#define SER Serial
#define BUF_SIZE 128
#define SERIAL_TIMEOUT 100

class SerialManager
{
    public:
        SerialManager(int baud_rate_param);
        void init();
        int handle_packet(int packet[]);

    private:
        char packet_buffer[BUF_SIZE];
        int baud_rate;
        char start_char;
        char end_char;

        int receive_packet();
        int process_packet(int packet[]);
        int clear_buffer();
};

#endif
