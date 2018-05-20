#ifndef UART_H_
#define UART_H_

#include "PinDefs.h"

#define UART_TX_BUFFER_SIZE		128
#define UART_RX_BUFFER_SIZE		128

void UART_begin(unsigned long buad);
void UART_end();

void UART_putc(char c);
void UART_puts(char* s, unsigned int len);
void UART_putn(int n);

unsigned int UART_count();
char UART_getc();
void UART_gets(char* s, unsigned int len);

void UART_flush();


#endif /* UART_H_ */