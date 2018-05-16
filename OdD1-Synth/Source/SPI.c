#include "SPI.h"

uint8_t SPIRXBuffer[SPI_RX_BUFFER_SIZE];
uint8_t SPITXBuffer[SPI_TX_BUFFER_SIZE];

uint8_t qin, qout, qcount;
uint8_t TransferInProgress;

#define pushq(q, qindex, qcount, qsize, v)	\
{											\
	if(qcount < qsize)						\
	{										\
		q[qindex] = v;						\
											\
		qcount++;							\
		qindex++;							\
		if(qindex > qsize)					\
			qindex = 0;						\
	}										\
}											\

#define popq(q, qindex, qcount, qsize, v)	\
{											\
	if(qcount < qsize)						\
	{										\
		v = q[qindex];						\
											\
		qcount++;							\
		qindex++;							\
		if(qindex > qsize)					\
			qindex = 0;						\
	}										\
}											\

void SPI_Init()
{
	SPCR = (1 << MSTR) | (1 << CPOL) | (1 << CPHA); //Mode 1,1, Master, F_CPU/4
	SPSR = (1 << SPI2X); //Double SPI speed F_CPU/2
	
	qcount = qin = qout = 0;
	TransferInProgress = 0;
	sbi(SPCR, SPE);
}

void SPI_Background()
{
}

uint8_t SPI_transfer(uint8_t c)
{
	SPDR = c;
	
	while(!(SPSR & (1 << SPIF)));
	
	return SPDR;
}