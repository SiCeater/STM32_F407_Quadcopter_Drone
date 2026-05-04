#include "control.h"

void start_control_loop()
{
    HAL_TIM_Base_Start_IT(&htim7); // 400Hz loop
    if (debug)
        print_to_console("\ncontrol loop          : started", 32);
}

/**
 * @brief routine de controle du drone dans l'espace
 *
 */
void control()
{
}
