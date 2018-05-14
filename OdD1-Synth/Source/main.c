#include "PinDefs.h"

#include "ADC.h"
#include "SPI.h"

int main(void)
{
	ADC_Init();
	SPI_Init();
	
    while (1) 
    {
		ADC_Update();
		ADC_UpdateMux();
    }
}

