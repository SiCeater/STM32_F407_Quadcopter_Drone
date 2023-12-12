#include "debug.h"

/**
 * @brief affichage des données reçues de la télécommande sur l'UART de debug (5)
 * 
 */
void print_received_data()
{
  char tab_uart_debug [50]={0};
  sprintf(tab_uart_debug,"\nX_D:%3d Y_D:%3d X_G:%3d Y_G:%3d B_D:%d B_G:%d",trame_decodee[0],trame_decodee[1],trame_decodee[2],trame_decodee[3],trame_decodee[4],trame_decodee[5]);
  HAL_UART_Transmit(&huart2,(uint8_t*)tab_uart_debug,44,1000);
}

void test_uart1() // 38400 baud
{
    uint8_t test='U';
    uint8_t retour_ligne=10;

    HAL_UART_Transmit(&huart1,&test,1,1000);
    HAL_UART_Transmit(&huart1,&retour_ligne,1,1000);
}

void test_uart2() // 460800 baud
{
    uint8_t test='U';
    uint8_t retour_ligne=10;

    HAL_UART_Transmit(&huart2,&test,1,1000);
    HAL_UART_Transmit(&huart2,&retour_ligne,1,1000);
}

void print_to_console(char *buffer, uint16_t buffer_size)
{
  HAL_UART_Transmit(&huart2,(uint8_t*)buffer,buffer_size,1000);
}