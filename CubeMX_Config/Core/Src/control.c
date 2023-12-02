 #include "control.h"

void start_control_loop()
{
    HAL_TIM_Base_Start_IT(&htim7);
    if(debug)
        print_to_console("\ncontrol loop          : started",32);
}

/**
 * @brief routine de controle du drone dans l'espace
 * 
 */
void control()
{
    if (!connected_flag)
        connection_lost_routine();
    else
    {
        onboard_led_on();
        decode_trame();
        if (debug)
            print_received_data();
        if((trame_decodee[0]>100)&&(trame_decodee[0]<200))
            set_motors(((trame_decodee[0]-100)*2.5),((trame_decodee[0]-100)*2.5),((trame_decodee[0]-100)*2.5),((trame_decodee[0]-100)*2.5));
        else
            set_motors(0,0,0,0);
    }
}
 