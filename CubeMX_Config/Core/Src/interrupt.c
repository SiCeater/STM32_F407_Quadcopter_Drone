#include "interrupt.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim6) // 10Hz security loop
    {
      // connected_flag = false;
      decode_trame();
      //print_received_data();
    }

    if((htim==&htim7)&&(remote_already_seen)) // 400Hz control loop
    {
      // control();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart==&huart1)
  {
    // TIM6->CNT=0;
    // remote_already_seen = true;
    // connected_flag = true;
    test_uart2();
    HAL_UART_Receive_IT (&huart1, transmit, 7);
    onboard_led_on();
  }
}