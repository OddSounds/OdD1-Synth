#ifndef SPI_H_
#define SPI_H_

#include "PinDefs.h"

void SPI_Init();

uint8_t SPI_transfer(uint8_t c);

#endif /* SPI_H_ */