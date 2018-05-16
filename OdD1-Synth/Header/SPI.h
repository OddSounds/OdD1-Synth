#ifndef SPI_H_
#define SPI_H_

#include "PinDefs.h"

#define SPI_TX_BUFFER_SIZE	128
#define SPI_RX_BUFFER_SIZE	128

void SPI_Init();

void SPI_Background();

uint8_t SPI_transfer(uint8_t c);

#endif /* SPI_H_ */