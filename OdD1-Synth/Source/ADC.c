#include "ADC.h"
#include <string.h>
#include <stdlib.h>

uint16_t AnalogReading[TOTAL_ANALOG_READINGS];
uint8_t CurrentChannel;
uint8_t Current01MuxChannel, Next01MuxChannel, Current23MuxChannel, Next23MuxChannel;

typedef void (*OnADCChange)(uint16_t);

OnADCChange ADCChangeHandler[TOTAL_ANALOG_READINGS];

pin_t ADC01Clk = {&PORTC, PORTC4};
pin_t ADC23Clk = {&PORTC, PORTC5};
pin_t ADCMuxReset = {&PORTD, PORTD7};

void l_ADCReset()
{
	CurrentChannel = 0;
	
	Current01MuxChannel = Next01MuxChannel = 0;
	Current23MuxChannel = Next23MuxChannel = 0;
	
	ClrPin(ADC01Clk);
	ClrPin(ADC23Clk);
	
	ClrPin(ADCMuxReset);
	SetPin(ADCMuxReset);
	
	sbi(ADMUX, MUX0);
	cbi(ADMUX, MUX1);
	cbi(ADMUX, MUX2);
	cbi(ADMUX, MUX3);	
}

void l_Increment01MuxChannel()
{
	SetPin(ADC01Clk);
	ClrPin(ADC01Clk);
}

void l_Increment23MuxChannel()
{
	SetPin(ADC23Clk);
	ClrPin(ADC23Clk);
}

void ADC_Init()
{
	//Setup ADC
	ADMUX = 0; //ADC0 mux input, left adjust
	sbi(ADMUX, REFS0); //AVCC Reference
	sbi(ADCSRA, ADPS2); //Div 16
	sbi(ADCSRA, ADEN); //Enable ADC
	DIDR0 = (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D) | (1 << ADC3D); //Disable digital input A0, A1, A2, A3
	
	memset(ADCChangeHandler, 0, sizeof(ADCChangeHandler));
	
	//Setup pins
	sbi(DDRC, PORTC4);
	sbi(DDRC, PORTC5);
	sbi(DDRD, PORTD7);
	
	//Set the MUX
	l_ADCReset();
	
	//Start first conversion
	sbi(ADCSRA, ADSC);
}

void ADC_Update()
{
	//Is conversion ready?
	if(!(ADCSRA & (1 << ADSC)))
	{
		uint16_t newreading;
		
		*((uint8_t*)&newreading) = ADCL;
		*((uint8_t*)&newreading + 1) = ADCH;
		
		if(ADCChangeHandler[CurrentChannel] && abs(AnalogReading[CurrentChannel] - newreading) > MIN_ADC_CHANGE)
			ADCChangeHandler[CurrentChannel](newreading);
		
		AnalogReading[CurrentChannel] = newreading;
		
		CurrentChannel++;
	
		if(CurrentChannel >= TOTAL_ANALOG_READINGS)
			CurrentChannel = 0;
	
		//Switch to the next input
		ADMUX &= 0xF0; //Just keep the upper nibble
		ADMUX |= CurrentChannel & 0x03; //Set the new input
		
		if(CurrentChannel < ANALOG_DO_NOT_READ) //Normal reading
		{
			//Using a 01 or 23 mux?
			//Ping-pong the readins where the 1st 2 happen on the 1st mux and the next 2 happen on the 2nd mux
			if(CurrentChannel & 0x02) //A 23 mux, update 01
				Next01MuxChannel = (CurrentChannel + 2) >> 2;
			else //A 01 mux, update 23
				Next23MuxChannel = (CurrentChannel + 2) >> 2;
		}
		else
		{
			//Handles issue where 1st mux channel on 1st mux would be invalid after wrap around because the switch hadn't happened yet
			//Create a bad reading that happens while a switch occurs
			//After this everything goes back to being normal
			l_ADCReset();	
		}
	
		//Start next reading
		sbi(ADCSRA, ADSC);
	}
}

void ADC_UpdateMux()
{
	if(Current01MuxChannel != Next01MuxChannel)
	{
		l_Increment01MuxChannel();
		Current01MuxChannel = Next01MuxChannel;
	}
	
	if(Current23MuxChannel != Next23MuxChannel)
	{
		l_Increment23MuxChannel();
		Current23MuxChannel = Next23MuxChannel;
	}		
}