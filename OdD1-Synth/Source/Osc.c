#include "Osc.h"
#include "ADC.h"

#include "WaveTables.h"

extern uint16_t AnalogReading;

uint8_t oscsync = 0;
volatile osc_t osc1, osc2;

#define byte_addr(v, o)		((uint8_t*)&v + o)

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
	osc2.phase = 128;
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
	int16_t osc1Out, osc2Out;
	int16_t mixOut;
	
	osc1Out = osc2Out = mixOut = 0;
	
	osc1.phaseaccum += osc1.tuningword;
	osc2.phaseaccum += osc2.tuningword;
	
	//Grab the wave
	*byte_addr(osc1Out, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc1.waveform] + (uint8_t)(*byte_addr(osc1.phaseaccum, 2) + osc1.phase));
	*byte_addr(osc2Out, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc2.waveform] + (uint8_t)(*byte_addr(osc2.phaseaccum, 2) + osc2.phase));
	
	if(*byte_addr(osc1Out, 0) & 0x80)
		*byte_addr(osc1Out, 1) = 0xFF;
	
	if(*byte_addr(osc2Out, 0) & 0x80)
		*byte_addr(osc2Out, 1) = 0xFF;	
	
	//Mix the signals
	mixOut = osc1Out;
	mixOut += osc2Out;
	mixOut >>= 1; //Divide by 2
	
	//Clip
	if((*byte_addr(mixOut, 1) & 0x80) && *byte_addr(mixOut, 1) != 0xFF)
		*byte_addr(mixOut, 0) = 0x80;
		
	if(!(*byte_addr(mixOut, 1) & 0x80) && *byte_addr(mixOut, 1) != 0)
		*byte_addr(mixOut, 0) = 0x7F;
	
	*byte_addr(mixOut, 0) += 0x80; //Add a zero offset
	
	OCR2A = *byte_addr(mixOut, 0);
	OCR2B = 0;
}