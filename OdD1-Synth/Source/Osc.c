#include "Osc.h"
#include "ADC.h"

#include "WaveTables.h"
#include <stdlib.h>

extern uint16_t* AnalogReading;

uint8_t oscsync = 0;
volatile osc_t osc1, osc2;

#define byte_addr(v, o)		((uint8_t*)&v + o)
#define short_addr(v, o)	((uint16_t*)&v + o)

void l_NoiseUpdate()
{
	
}

void Osc_Init()
{
	//Set oscillator outputs
	
	//Initialize oscillators
	osc1.note = osc2.note = 44;
	osc1.waveform = osc2.waveform = WAVE_SINE;
	osc1.phaseaccum = osc2.phaseaccum = 0;
	osc1.phase = 0;
	osc2.phase = 0;
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

//230 cycles
ISR(TIMER2_OVF_vect)
{
	uint16_t osc1Out, osc2Out, fraction, whole;
	int16_t mixOut;
	
	osc1Out = osc2Out = mixOut = 0;
	
	osc1.phaseaccum += osc1.tuningword;
	osc2.phaseaccum += osc2.tuningword;
	
	//Grab the wave
	*byte_addr(osc1Out, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc1.waveform] + (uint8_t)(*byte_addr(osc1.phaseaccum, 2) + osc1.phase));
	*byte_addr(osc2Out, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc2.waveform] + (uint8_t)(*byte_addr(osc2.phaseaccum, 2) + osc2.phase + SUB_PHASE_SHIFT));
	
	fraction = *byte_addr(osc1Out, 0) * *byte_addr(osc1Scalar, 0);
	whole = *byte_addr(osc1Out, 0) * *byte_addr(osc1Scalar, 1);
	osc1Out = *byte_addr(fraction, 1);
	osc1Out += *byte_addr(whole, 0);
	if(osc1Scalar < osc2Scalar)
		osc1Out += bias;
	
	fraction = *byte_addr(osc2Out, 0) * *byte_addr(osc2Scalar, 0);
	whole = *byte_addr(osc2Out, 0) * *byte_addr(osc2Scalar, 1);
	osc2Out = *byte_addr(fraction, 1);
	osc2Out += *byte_addr(whole, 0);
	if(osc2Scalar < osc1Scalar)
		osc2Out += bias;
	
	//Mix the signals
	mixOut = osc1Out;
	mixOut -= osc2Out;
	mixOut >>= 1; //Divide by 2
	
	if(mixOut < -128)
		mixOut = -128;
	else if(mixOut > 128)
		mixOut = 128;
		
	*byte_addr(mixOut, 0) += 0x80;
	
	OCR2A = *byte_addr(mixOut, 0);
	OCR2B = 0;
}