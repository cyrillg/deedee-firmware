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

    clear_receive_buffer();
    clear_current_packet();
}


void SerialManager::init()
{
    SER.begin(baud_rate);
    DEBUG_SER.begin(baud_rate);
}

int SerialManager::receive_packet()
{
    if(!SER.available())
        return -1;

    if(store_packet()!=0)
    {
        clear_receive_buffer();
        return -1;
    }

    int packet_length;
    split_packet(packet_length);

    int packet_type;
    if(!is_valid_packet(packet_length, packet_type))
    {
        clear_receive_buffer();
        clear_current_packet();
        return -1;
    }

    clear_receive_buffer();

    return packet_type;
}

int SerialManager::retrieve_packet(MotorCmd &packet)
{
    packet.speed_left = current_packet[1];
    packet.speed_right = current_packet[2];
    clear_current_packet();
}

int SerialManager::store_packet()
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
        receive_buffer[idx++] = new_char;
        new_char = SER.read();
        timer_dt = millis()-timer_start;
    }

    if(!is_packet_complete)
    {
        DEBUG_SER.println("Error (timeout or packet too long)- Packet dropped");
        return 1;
    }

    return 0;
}

void SerialManager::split_packet(int &packet_length)
{
    int idx = 0;
    char* field = strtok(receive_buffer, ",");
    while(field != 0)
    {
        current_packet[idx++] = atoi(field);
        field = strtok(0, ",");
    }

    packet_length = idx;
}

bool SerialManager::is_valid_packet(int packet_length, int &packet_type)
{
    if(packet_length==0)
    {
        DEBUG_SER.println("Empty packet");
        return false;
    }

    packet_type = current_packet[0];

    if(!is_known_type(packet_type))
    {
        DEBUG_SER.println("Unkown packet type");
        return false;
    }

    if(packet_length<packet_sizes[packet_type])
    {
        DEBUG_SER.println("Incomplete frame");
        return false;
    }
    else if(packet_length>packet_sizes[packet_type])
    {
        DEBUG_SER.println("Too many fields in the frame");
        return false;
    }

    return true;
}

bool SerialManager::is_known_type(int packet_type)
{
    return packet_type<KNOWN_TYPE_RANGE;
}

void SerialManager::clear_receive_buffer()
{
    for(int i=0; i<BUF_SIZE; i++)
        receive_buffer[i] = (char)0;
}

void SerialManager::clear_current_packet()
{
    for(int i=0; i<MAX_FIELDS_SIZE; i++)
        current_packet[i] = (char)0;
}

