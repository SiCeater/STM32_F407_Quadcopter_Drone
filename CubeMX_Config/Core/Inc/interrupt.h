#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "global.h"
#include "tim.h"
#include "usart.h"
#include "control.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif