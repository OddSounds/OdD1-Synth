#include "UART.h"
#include <stdlib.h>
#include <string.h>

#define sbi(port,bit)	(port) |= (1 << (bit))
#define cbi(port,bit)	(port) &= ~(1 << (bit))

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


volatile char RXBuffer[UART_CHANNELS][UART_RX_BUFFER_SIZE];
volatile unsigned int rxin[UART_CHANNELS], rxout[UART_CHANNELS], rxcount[UART_CHANNELS];
volatile unsigned char rxchannel;

volatile char TXBuffer[UART_CHANNELS][UART_TX_BUFFER_SIZE];
volatile unsigned int txin[UART_CHANNELS], txout[UART_CHANNELS], txcount[UART_CHANNELS];
volatile unsigned char txchannel;

void UART_begin(unsigned long baud)
{
	unsigned long ubrr = F_CPU/16/baud;
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)(ubrr);
	
	memset(rxin, 0, sizeof(rxin));
	memset(rxout, 0, sizeof(rxout));
	memset(rxcount, 0, sizeof(rxcount));
	
	memset(txin, 0, sizeof(txin));
	memset(txout, 0, sizeof(txout));
	memset(txcount, 0, sizeof(txcount));
	
	txchannel = 0;
	rxchannel = 0;
	
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXCIE0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, RXEN0);
	
	sei();
}

void UART_end()
{
	while(txcount[txchannel] > 0 || !(UCSR0A & (1 << UDRE0)))
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
void UART_putc(char c, unsigned char channel)
{
	cbi(UCSR0B, TXCIE0);
	pushq(TXBuffer[channel], txin[channel], txcount[channel], UART_TX_BUFFER_SIZE, c);
	sbi(UCSR0B, TXCIE0);
	
	//Prime the pump
	if(UCSR0A & (1 << UDRE0))
	{
		txchannel = channel;
		popq(TXBuffer[channel], txout[channel], txcount[channel], UART_TX_BUFFER_SIZE, UDR0);
	}
}

void UART_puts(char* s, unsigned int len, unsigned char channel)
{
	unsigned int i;
	
	cbi(UCSR0B, TXCIE0);
	for(i = 0; i < len && txcount[channel] < UART_TX_BUFFER_SIZE; i++)
	pushq(TXBuffer[channel], txin[channel], txcount[channel], UART_TX_BUFFER_SIZE, s[i]);
	sbi(UCSR0B, TXCIE0);

	if(UCSR0A & (1 << UDRE0))
	{
		txchannel = channel;
		popq(TXBuffer[channel], txout[channel], txcount[channel], UART_TX_BUFFER_SIZE, UDR0);
	}
}

void UART_putn(int n, unsigned char channel)
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
	
	UART_puts(numstr + index + 1, 10 - (index + 1), channel);
}
//TX Functions End

//RX Functions Start
unsigned int UART_count(unsigned char channel)
{
	return rxcount[channel];
}

char UART_getc(unsigned char channel)
{
	char c = 0xFF;
	popq(RXBuffer[channel], rxout[channel], rxcount[channel], UART_RX_BUFFER_SIZE, c);
	
	return c;
}

void UART_gets(char* s, unsigned int len, unsigned char channel)
{
	unsigned int i;
	
	for(i = 0; i < len && rxcount > 0; i++)
	popq(RXBuffer[channel], rxout[channel], rxcount[channel], UART_RX_BUFFER_SIZE, s[i]);
}
//RX Functions End

//Utility Functions Start
void UART_flush()
{
	memset(rxin, 0, sizeof(rxin));
	memset(rxout, 0, sizeof(rxout));
	memset(rxcount, 0, sizeof(rxcount));
	
	memset(txin, 0, sizeof(txin));
	memset(txout, 0, sizeof(txout));
	memset(txcount, 0, sizeof(txcount));
}
//Utility Functions End

//ISR
ISR(USART_RX_vect)
{
	pushq(RXBuffer[rxchannel], rxin[rxchannel], rxcount[rxchannel], UART_RX_BUFFER_SIZE, UDR0);
}

ISR(USART_TX_vect)
{
	if(UART_CHANNELS > 0)
	{
		unsigned char i = txchannel;
		
		do
		{
			txchannel++;
			if(txchannel >= UART_CHANNELS)
			txchannel = 0;
		}while(i != txchannel && txcount[txchannel] == 0);
	}
	
	popq(TXBuffer[txchannel], txout[txchannel], txcount[txchannel], UART_TX_BUFFER_SIZE, UDR0);
}