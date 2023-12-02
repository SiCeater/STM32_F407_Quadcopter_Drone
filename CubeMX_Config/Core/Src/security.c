#include "security.h"

void start_security_loop()
{
    HAL_TIM_Base_Start_IT(&htim6);
    if(debug)
        print_to_console("\nsecurity loop         : started",32);
}

void connection_lost_routine()
{
    if (debug)
        print_to_console("\nremote connection lost !\n",26);

    onboard_led_off();
    
    while(!connected_flag)
    {
        set_motors(0,0,0,0);
    }
}