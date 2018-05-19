#include "PinDefs.h"

#include "ADC.h"
#include "Osc.h"
#include "SPI.h"

int main(void)
{
	ADC_Init();
	SPI_Init();

	Osc_Init();
	
	sei();
	
    while (1) 
    {
		ADC_Update();
		ADC_UpdateMux();
    }
}

