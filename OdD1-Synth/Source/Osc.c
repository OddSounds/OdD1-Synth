#include "Osc.h"
#include "ADC.h"

extern uint16_t AnalogReading;

uint8_t oscsync = 0;
volatile osc_t osc1, osc2;

void l_NoiseUpdate()
{
	
}

void Osc_Init()
{
	//Set oscillator outputs
	
	//Initialize oscillators
	osc1.note = osc2.note = 44;
	osc1.phaseaccum = osc2.phaseaccum = 0;
	osc1.tuningword = osc2.tuningword = pgm_read_dword(keyFreq + osc1.note + KEY_OFFSET);
	
	// Timer2 PWM Mode set to Phase Correct PWM
	cbi (TCCR2A, COM2A0);  // clear Compare Match
	sbi (TCCR2A, COM2A1);

	sbi (TCCR2A, WGM20);  // Mode 1  / Phase Correct PWM
	cbi (TCCR2A, WGM21);
	cbi (TCCR2B, WGM22);
	
	sbi (TIMSK2,TOIE2);	
	
	//Start the timer
	// Timer2 Clock Prescaler to : 1
	sbi (TCCR2B, CS20);
	cbi (TCCR2B, CS21);
	cbi (TCCR2B, CS22);	
}

ISR(TIMER2_OVF_vect)
{
	osc1.phaseaccum += osc1.tuningword;
	osc2.phaseaccum += osc2.tuningword;
	
	OCR2A = 0;
	OCR2B = 0;
}