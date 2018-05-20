#include "Osc.h"
#include "ADC.h"

#include "WaveTables.h"
#include <stdlib.h>

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
	sbi(DDRD, PORTD6); //OSC0A
	sbi(DDRD, PORTD5); //Just used for timing
	
	//Initialize oscillators
	osc1.note = osc2.note = 44;
	osc1.waveform = osc2.waveform = WAVE_SINE;
	osc1.phaseaccum = osc2.phaseaccum = 0;
	osc1.phase = 0;
	osc2.phase = 0;
	osc1.tuningword = osc2.tuningword = pgm_read_dword(keyFreq + osc1.note + KEY_OFFSET);
	osc1.index = byte_addr(osc1.phaseaccum, 2);
	osc2.index = byte_addr(osc2.phaseaccum, 2);
	
	// Timer2 PWM Mode set to Phase Correct PWM
	cbi (TCCR0A, COM0A0);  // clear Compare Match
	sbi (TCCR0A, COM0A1);

	sbi (TCCR0A, WGM00);  // Mode 1  / Phase Correct PWM
	cbi (TCCR0A, WGM01);
	cbi (TCCR0B, WGM02);
	
	sbi (TIMSK0,TOIE0);	
	
	//Start the timer
	// Timer0 Clock Prescaler to : 1
	sbi (TCCR0B, CS00);
	cbi (TCCR0B, CS01);
	cbi (TCCR0B, CS02);	
}

//230 cycles
ISR(TIMER0_OVF_vect)
{
	uint16_t osc1Out, osc2Out;
	uint16_t fraction, whole, bias;
	int16_t mixOut, osc1Scalar, osc2Scalar;
	sbi(PORTD, PORTD5);
	
	osc1Out = osc2Out = mixOut = 0;
	
	osc1.phaseaccum += osc1.tuningword;
	osc2.phaseaccum += osc2.tuningword;
	
	//Maybe don't do this here
	osc1.waveform = *byte_addr(AnalogReading[ANALOG_OSC1_WAVEFORM], 1);
	osc2.waveform = *byte_addr(AnalogReading[ANALOG_OSC2_WAVEFORM], 1);
	osc1Scalar = AnalogReading[ANALOG_OSC1_DUTY_CYCLE] >> 1;
	osc2Scalar = AnalogReading[ANALOG_OSC2_DUTY_CYCLE] >> 1;
	
	//Grab the wave
	*byte_addr(osc1Out, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc1.waveform] + (uint8_t)(*osc1.index + osc1.phase));
	*byte_addr(osc2Out, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc2.waveform] + (uint8_t)(*osc2.index + osc2.phase));
	
	//Scale each oscillator
	fraction = *byte_addr(osc1Out, 0) * *byte_addr(osc1Scalar, 0);
	whole = *byte_addr(osc1Out, 0) * *byte_addr(osc1Scalar, 1);
	osc1Out = *byte_addr(fraction, 1);
	osc1Out += *byte_addr(whole, 0);
	
	fraction = *byte_addr(osc2Out, 0) * *byte_addr(osc2Scalar, 0);
	whole = *byte_addr(osc2Out, 0) * *byte_addr(osc2Scalar, 1);
	osc2Out = *byte_addr(fraction, 1);
	osc2Out += *byte_addr(whole, 0);
	
	//Mix the signals
	mixOut = osc1Out;
	mixOut -= (osc1Scalar >> 1) - 1; //Offset
	mixOut += osc2Out;
	mixOut -= (osc2Scalar >> 1) - 1; //Offset

	//Hard clip
	if(mixOut > 128)
		mixOut = 127;
	else if(mixOut < -127)
		mixOut = -127;
		
	//Restore offset
	mixOut += 0x7F;
	
	OCR0A = *byte_addr(mixOut, 0);
	
	cbi(PORTD, PORTD5);
}