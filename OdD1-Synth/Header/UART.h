#ifndef UART_H_
#define UART_H_

#include "PinDefs.h"

#define UART_TX_BUFFER_SIZE		128
#define UART_RX_BUFFER_SIZE		128

#define UART_CHANNELS			2

void UART_begin(unsigned long buad);
void UART_end();

void UART_putc(char c, unsigned char channel);
void UART_puts(char* s, unsigned int len, unsigned char channel);
void UART_putn(int n, unsigned char channel);

unsigned int UART_count(unsigned char channel);
char UART_getc(unsigned char channel);
void UART_gets(char* s, unsigned int len, unsigned char channel);

void UART_flush();


#endif /* UART_H_ */