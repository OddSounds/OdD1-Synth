#include "ADC.h"

#include "PinDefs.h"

uint16_t AnalogReading[TOTAL_ANALOG_READINGS];
uint8_t CurrentChannel;

void ADC_Init()
{
	//Setup ADC
	ADMUX = 0; //ADC0 mux input, left adjust
	sbi(ADMUX, REFS0); //AVCC Reference
	sbi(ADCSRA, ADPS2); //Div 16
	sbi(ADCSRA, ADEN); //Enable ADC
	DIDR0 = (1 << ADC0D) | (1 << ADC1D); //Disable digital input A0, A1
	
	//Setup the MUX
	
	//Set the MUX
	CurrentChannel = 0;
	cbi(ADMUX, MUX0);
	
	//Start first conversion
	sbi(ADCSRA, ADSC);
}

void ADC_Update()
{
	//Is conversion ready?
	if(!(ADCSRA & (1 << ADSC)))
	{
		*((uint8_t*)&AnalogReading[CurrentChannel]) = ADCL;
		*((uint8_t*)&AnalogReading[CurrentChannel] + 1) = ADCH;
		CurrentChannel++;
	
		if(CurrentChannel > TOTAL_ANALOG_READINGS)
			CurrentChannel = 0;
	
		//Switch to the next mux
		if(CurrentChannel & 0x01)
			sbi(ADMUX, MUX0);
		else
			cbi(ADMUX, MUX0);
	
		//Start next reading
		sbi(ADCSRA, ADSC);
	}
}