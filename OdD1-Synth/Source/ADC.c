#include "ADC.h"

uint16_t AnalogReading[TOTAL_ANALOG_READINGS];
uint8_t CurrentChannel;
uint8_t Current01MuxChannel, Next01MuxChannel, Current23MuxChannel, Next23MuxChannel;
uint8_t Current01Mux, Next01Mux, Current23Mux, Next23Mux;

void ADC_Init()
{
	//Setup ADC
	ADMUX = 0; //ADC0 mux input, left adjust
	sbi(ADMUX, REFS0); //AVCC Reference
	sbi(ADCSRA, ADPS2); //Div 16
	sbi(ADCSRA, ADEN); //Enable ADC
	DIDR0 = (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D) | (1 << ADC3D); //Disable digital input A0, A1, A2, A3
	
	//Setup the MUX
	
	//Set the MUX
	CurrentChannel = 0;
	
	Current01MuxChannel = Next01MuxChannel = 0;
	Current01Mux = Next01Mux = 0;
	
	Current23MuxChannel = Next23MuxChannel = 0;
	Current23Mux = Next23Mux = 0;	
	
	cbi(ADMUX, MUX0);
	cbi(ADMUX, MUX1);
	cbi(ADMUX, MUX2);
	cbi(ADMUX, MUX3);
	
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
	
		if(CurrentChannel >= TOTAL_ANALOG_READINGS)
			CurrentChannel = 0;
	
		//Switch to the next input
		ADMUX &= 0xF0;
		ADMUX |= CurrentChannel & 0x03;
		
		if(CurrentChannel < ANALOG_DO_NOT_READ) //Normal reading
		{
			//Using a 01 or 23 mux?
			//Ping-pong the readins where the 1st 2 happen on the 1st mux and the next 2 happen on the 2nd mux
			if(CurrentChannel & 0x02) //A 23 mux, update 01
			{
				//4 selections per mux, so take the next 2 highest bits
				Next01MuxChannel = ((CurrentChannel + 2) & 0x0C) >> 2;
				//Next highest bit selects which of the 2 ping-pong banks
				Next01Mux = ((CurrentChannel + 2) & 0x10) >> 4;
				//The +2 accounts for the 2 readings taken between ping-pong
			}
			else //A 01 mux, update 23
			{
				Next23MuxChannel = ((CurrentChannel + 2) & 0x0C) >> 2;
				Next23Mux = ((CurrentChannel + 2) & 0x10) >> 4;
			}
		}
		else
		{
			//Handles issue where 1st mux channel on 1st mux would be invalid after wrap around because the switch hadn't happened yet
			//Create a bad reading that happens while a switch occurs
			//After this everything goes back to being normal
			Current01MuxChannel = Next01MuxChannel = 0;
			Current01Mux = Next01Mux = 0;
			
			Current23MuxChannel = Next23MuxChannel = 0;
			Current23Mux = Next23Mux = 0;		
		}
	
		//Start next reading
		sbi(ADCSRA, ADSC);
	}
}

void ADC_UpdateMux()
{
	if(Current01MuxChannel != Next01MuxChannel)
	{
		Current01MuxChannel = Next01MuxChannel;
	}
	
	if(Current23MuxChannel != Next23MuxChannel)
	{
		Current23MuxChannel = Next23MuxChannel;
	}		
	
	if(Current01Mux != Next01Mux)
	{
		Current01Mux = Next01Mux;
	}
	
	if(Current23Mux != Next23Mux)
	{
		Current23Mux = Next23Mux;
	}	
}