/*
  SerialManager.h - Library to communicate through serial
  Created by Cyrill Guillemot, December 24, 2017.
*/

#include "Arduino.h"
#include "SerialManager.h"

SerialManager::SerialManager(int baud_rate_param)
{
    baud_rate = baud_rate_param;
    start_char = '$';
    end_char = '\n';
}


void SerialManager::init()
{
    SER.begin(baud_rate);
}

int SerialManager::handle_packet(int packet[])
{
    if(!SER.available())
        return -1;

    if(receive_packet()!=0)
        return -1;

    if(process_packet(packet)!=0)
        return -1;

    clear_buffer();
    return 0;
}

int SerialManager::receive_packet()
{
    char new_char = SER.read();

    if(new_char!=start_char)
        return 1;

    int idx = 0;
    bool is_packet_complete = true;
    int timer_start = millis();
    int timer_dt = millis()-timer_start;

    new_char = SER.read();
    while(new_char!=end_char)
    {
        if(idx>BUF_SIZE || timer_dt>SERIAL_TIMEOUT)
        {
            is_packet_complete = false;
            break;
        }
        packet_buffer[idx++] = new_char;
        new_char = SER.read();
        timer_dt = millis()-timer_start;
    }

    if(!is_packet_complete)
    {
        SER.println("Error (timeout or packet too long)- Packet dropped");
        return 1;
    }

    return 0;
}

int SerialManager::process_packet(int fields[])
{
    int idx = 0;
    char* field = strtok(packet_buffer, ",");
    while (field != 0)
    {
        fields[idx++] = atoi(field);
        field = strtok(0, ",");
    }

    return (idx==3) ? 0 : 1;
}

int SerialManager::clear_buffer()
{
    for(int i=0; i<sizeof(packet_buffer); i++)
        packet_buffer[i] = (char)0;
}

