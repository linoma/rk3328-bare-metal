#include "uart.h"


int rk_uart_init(){
	return 0;
}

void rk_uart_sendbyte(unsigned char byte){
    while((UART2_USR & (0x01 << 1)) == 0);
    UART2_THR = byte;
}

void rk_uart_puts(char *s) {
    while(*s) {
        if(*s=='\n')
            rk_uart_sendbyte('\r');
        rk_uart_sendbyte(*s++);
    }
}