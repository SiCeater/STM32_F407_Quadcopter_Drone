#include "global.h"

uint8_t transmit[7]={0,0,0,0,0,0,0}; 
uint8_t trame_decodee[6]={0,0,0,0,0,0};
bool connected_flag = false;
bool debug = false;
bool remote_already_seen = false;