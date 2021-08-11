#include "uart.h"

void rk_uart_sendbyte(unsigned char byte){
    while((UART2_USR & (0x01 << 1)) == 0);
    UART2_THR = byte;
}