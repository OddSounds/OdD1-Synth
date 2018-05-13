#include "PinDefs.h"

#include "ADC.h"


int main(void)
{
	ADC_Init();
	
    while (1) 
    {
		ADC_Update();
    }
}

