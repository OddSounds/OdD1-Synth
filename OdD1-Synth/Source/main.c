#include "PinDefs.h"

#include "ADC.h"
#include "SPI.h"
#include "UART.h"

int main(void)
{
	unsigned char i;
	
	ADC_Init();
	SPI_Init();
	
	UART_begin(115200);
	
    while (1) 
    {
		ADC_Update();
		ADC_UpdateMux();
		
		if(UART_count())
			UART_putc(UART_getc());
    }
}

