#include "PinDefs.h"

#include <util/delay.h>

#include "ADC.h"
#include "SPI.h"
#include "UART.h"

int main(void)
{
	ADC_Init();
	SPI_Init();
	
	UART_begin(115200);
	
    while (1) 
    {
		ADC_Update();
		ADC_UpdateMux();		
    }
}

