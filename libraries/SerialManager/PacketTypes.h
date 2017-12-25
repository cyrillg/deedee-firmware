/*
  PacketTypes.h - Definition of the packet types received and sent by Arduino
  Created by Cyrill Guillemot, December 25, 2017.
*/

#ifndef PacketTypes_h
#define PacketTypes_h

#include "Arduino.h"

#define KNOWN_TYPE_RANGE 1
#define MMC 0

static int packet_sizes[] = {3};

struct MotorCmd {
    int speed_left;
    int speed_right;
};

#endif
