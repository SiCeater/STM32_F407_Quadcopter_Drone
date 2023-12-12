#include "global.h"

uint8_t transmit[7]={0,0,0,0,0,0,0}; 
uint8_t trame_decodee[6]={0,0,0,0,0,0};
bool remote_already_seen = false;
bool connected_flag = false;
bool debug = true;
uint16_t top_left_motor=0;
uint16_t top_right_motor=0;
uint16_t bottom_left_motor=0;
uint16_t bottom_right_motor=0;
