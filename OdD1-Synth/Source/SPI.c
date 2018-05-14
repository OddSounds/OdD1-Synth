#include "SPI.h"

void SPI_Init()
{
	SPCR = (1 << MSTR) | (1 << CPOL) | (1 << CPHA); //Mode 1,1, Master, F_CPU/4
	SPSR = (1 << SPI2X); //Double SPI speed F_CPU/2
	
	sbi(SPCR, SPE);
}

uint8_t SPI_transfer(uint8_t c)
{
	SPDR = c;
	
	while(!(SPSR & (1 << SPIF)));
	
	return SPDR;
}