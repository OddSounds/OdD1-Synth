#include "UART.h"
#include <stdlib.h>
#include <string.h>

#define BAUD	115200
#define MYUBRR	F_CPU/16/BAUD-1

#define pushq(q, qIndex, qCount, qSize, v)	\
{											\
	if(qCount < qSize)						\
	{										\
		q[qIndex] = v;						\
		qCount++;							\
		qIndex++;							\
		if(qIndex >= qSize)					\
		qIndex = 0;							\
	}										\
}											\

#define popq(q, qIndex, qCount, qSize, v)	\
{											\
	if(qCount > 0)							\
	{										\
		v = q[qIndex];						\
		qCount--;							\
		qIndex++;							\
		if(qIndex >= qSize)					\
		qIndex = 0;							\
	}										\
}											\


volatile char RXBuffer[UART_RX_BUFFER_SIZE];
volatile unsigned int rxin, rxout, rxcount;

volatile char TXBuffer[UART_TX_BUFFER_SIZE];
volatile unsigned int txin, txout, txcount;

void UART_begin(unsigned long baud)
{
	uint16_t ubrr = (F_CPU / 4 / baud - 1) / 2;
	sbi(UCSR0A, U2X0);
	
	if(ubrr > 4095)
	{
		ubrr = (F_CPU / 8 / baud - 1) / 2;
		cbi(UCSR0A, U2X0);
	}
	
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)(ubrr);
	
	UART_flush();
	
	cbi(DDRD, PORTD0);
	sbi(DDRD, PORTD1);
	
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXCIE0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, RXEN0);
	
	sei();
}

void UART_end()
{
	while(txcount > 0 || !(UCSR0A & (1 << UDRE0)))
	{
		__asm("nop");
	}
	
	UART_flush();
	cbi(UCSR0B, TXCIE0);
	cbi(UCSR0B, RXCIE0);
	cbi(UCSR0B, TXEN0);
	cbi(UCSR0B, RXEN0);
}

//TX Functions Start
void UART_putc(char c)
{
	cbi(UCSR0B, TXCIE0);
	pushq(TXBuffer, txin, txcount, UART_TX_BUFFER_SIZE, c);
	sbi(UCSR0B, TXCIE0);
	
	//Prime the pump
	if(UCSR0A & (1 << UDRE0))
		popq(TXBuffer, txout, txcount, UART_TX_BUFFER_SIZE, UDR0);
}

void UART_puts(char* s, unsigned int len)
{
	unsigned int i;
	
	cbi(UCSR0B, TXCIE0);
	for(i = 0; i < len && txcount < UART_TX_BUFFER_SIZE; i++)
		pushq(TXBuffer, txin, txcount, UART_TX_BUFFER_SIZE, s[i]);
	sbi(UCSR0B, TXCIE0);

	if(UCSR0A & (1 << UDRE0))
		popq(TXBuffer, txout, txcount, UART_TX_BUFFER_SIZE, UDR0);
}

void UART_putn(int n)
{
	char numstr[10], sign = 0;
	char index = 9;
	
	memset(numstr, 0, sizeof(numstr));
	
	if(n < 0)
		sign = 1;
	
	n = abs(n);
	
	while(n > 0)
	{
		numstr[index] = (char)(n % 10) + '0';
		n /= 10;
		index--;
	}
	
	if(sign)
	{
		numstr[index] = '-';
		index--;
	}
	
	UART_puts(numstr + index + 1, 10 - (index + 1));
}
//TX Functions End

//RX Functions Start
unsigned int UART_count()
{
	unsigned char ret = 0;
	
	cbi(UCSR0B, RXCIE0);
	ret = rxcount;
	sbi(UCSR0B, RXCIE0);
	
	return ret;
}

char UART_getc()
{
	char c = 0xFF;
	
	cbi(UCSR0B, RXCIE0);
	popq(RXBuffer, rxout, rxcount, UART_RX_BUFFER_SIZE, c);
	sbi(UCSR0B, RXCIE0);
	
	return c;
}

void UART_gets(char* s, unsigned int len)
{
	unsigned int i;
	
	cbi(UCSR0B, RXCIE0);
	for(i = 0; i < len && rxcount > 0; i++)
		popq(RXBuffer, rxout, rxcount, UART_RX_BUFFER_SIZE, s[i]);
	sbi(UCSR0B, RXCIE0);	
}
//RX Functions End

//Utility Functions Start
void UART_flush()
{
	rxin = rxout = rxcount = 0;
	txin = txout = txcount = 0;
}
//Utility Functions End

//ISR
ISR(USART_RX_vect)
{
	pushq(RXBuffer, rxin, rxcount, UART_RX_BUFFER_SIZE, UDR0);
}

ISR(USART_TX_vect)
{
	popq(TXBuffer, txout, txcount, UART_TX_BUFFER_SIZE, UDR0);
}