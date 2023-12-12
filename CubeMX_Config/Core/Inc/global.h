
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdint.h>
#include <stdbool.h>

extern uint8_t transmit[7];
extern uint8_t trame_decodee[6];
extern bool connected_flag;
extern bool debug;
extern bool remote_already_seen;
extern uint16_t top_left_motor;
extern uint16_t top_right_motor;
extern uint16_t bottom_left_motor;
extern uint16_t bottom_right_motor;

#endif
    
