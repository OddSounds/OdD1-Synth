#include "Osc.h"
#include "ADC.h"

#include "WaveTables.h"
#include <stdlib.h>

uint8_t oscsync = 0;
volatile osc_t osc1, osc2;

volatile uint8_t NextOsc1LevelReady, NextOsc2LevelReady;
volatile uint8_t NextOsc1WaveReady, NextOsc2WaveReady;

uint16_t NextOsc1Waveform, NextOsc2Waveform;
uint16_t NextOsc1Level, NextOsc2Level;

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
	osc1.phase = osc2.phase = 0;
	osc1.level = osc2.level = 0;
	osc1.tuningword = osc2.tuningword = pgm_read_dword(keyFreq + osc1.note + KEY_OFFSET);
	osc1.index = byte_addr(osc1.phaseaccum, 2);
	osc2.index = byte_addr(osc2.phaseaccum, 2);
		
	NextOsc1LevelReady = NextOsc2LevelReady = 0;
	NextOsc1WaveReady = NextOsc2WaveReady = 0;
	
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

void Osc_ChangeWave1(uint16_t wave)
{
	NextOsc1WaveReady = 0;
	NextOsc1Waveform = wave;
	NextOsc1WaveReady = 1;
}

void Osc_ChangeScale1(uint16_t scale)
{
	NextOsc1LevelReady = 0;
	NextOsc1Level = scale;
	NextOsc1LevelReady = 1;
}

void Osc_ChangeWave2(uint16_t wave)
{
	NextOsc2WaveReady = 0;
	NextOsc2Waveform = wave;
	NextOsc2WaveReady = 1;
}

void Osc_ChangeScale2(uint16_t scale)
{
	NextOsc2LevelReady = 0;
	NextOsc2Level = scale;
	NextOsc2LevelReady = 1;	
}

//69% of 510 cycles (LFO/ADSR/NOISE)
ISR(TIMER0_OVF_vect)
{
	uint16_t osc1Out, osc2Out;
	uint16_t fraction, whole;
	int16_t mixOut;
	uint32_t mixindex;
	sbi(PORTD, PORTD5); //Timing start
	
	osc1Out = osc2Out = mixOut = 0;
	
	osc1.phaseaccum += osc1.tuningword;
	osc2.phaseaccum += osc2.tuningword;
	
	//Grab osc1 waveform
	//Reusing fraction and whole. Sue me.
	fraction = whole = 0;
	mixindex = analogWaveTable + (uint8_t)(*osc1.index + osc1.phase);
	*byte_addr(fraction, 0) = pgm_read_byte(mixindex + waveformOffset[osc1.waveform]);
	*byte_addr(whole, 0) = pgm_read_byte(mixindex + waveformOffset[osc1.waveform + 1]);
	
	//Mix waveform 1
	fraction *= osc1.wavemix;
	whole *= osc1.wavemixnext;
	whole += fraction;
	*byte_addr(osc1Out, 0) = *byte_addr(whole, 1);
	
	//Scale osc1
	fraction = *byte_addr(osc1Out, 0) * *byte_addr(osc1.level, 0);
	whole = *byte_addr(osc1Out, 0) * *byte_addr(osc1.level, 1);
	osc1Out = *byte_addr(fraction, 1);
	osc1Out += *byte_addr(whole, 0);
	
	
	//Grab osc2 waveform
	fraction = whole = 0;
	mixindex = analogWaveTable + (uint8_t)(*osc2.index + osc2.phase);
	*byte_addr(fraction, 0) = pgm_read_byte(mixindex + waveformOffset[osc2.waveform]);
	*byte_addr(whole, 0) = pgm_read_byte(mixindex + waveformOffset[osc2.waveform + 1]);
	
	//Mix waveform 2
	fraction *= osc2.wavemix;
	whole *= osc2.wavemixnext;
	whole += fraction;
	*byte_addr(osc2Out, 0) = *byte_addr(whole, 1);	
	
	fraction = *byte_addr(osc2Out, 0) * *byte_addr(osc2.level, 0);
	whole = *byte_addr(osc2Out, 0) * *byte_addr(osc2.level, 1);
	osc2Out = *byte_addr(fraction, 1);
	osc2Out += *byte_addr(whole, 0);
	
	
	//Mix the signals
	mixOut = osc1Out;
	mixOut -= (osc1.level >> 1) - 1; //Offset
	mixOut += osc2Out;
	mixOut -= (osc2.level >> 1) - 1; //Offset
	mixOut >>= 1;

	//Hard clip
	//Better way?
	if(mixOut > 128)
		mixOut = 127;
	else if(mixOut < -127)
		mixOut = -127;
		
	//Restore offset
	mixOut += 0x7F;
	
	OCR0A = *byte_addr(mixOut, 0);
	
	if(NextOsc1WaveReady)
	{
		osc1.waveform = *byte_addr(NextOsc1Waveform, 1);
		osc1.wavemix = 0x0100 - *byte_addr(NextOsc1Waveform, 1);
		osc1.wavemixnext = *byte_addr(NextOsc1Waveform, 1);
		NextOsc1WaveReady = 0;
	}
	
	if(NextOsc1LevelReady)
	{
		osc1.level = NextOsc1Level;
		NextOsc1LevelReady = 0;
	}
	
	if(NextOsc2WaveReady)
	{
		osc2.waveform = *byte_addr(NextOsc2Waveform, 1);
		osc2.wavemix = 0x0100 - *byte_addr(NextOsc2Waveform, 1);
		osc2.wavemixnext = *byte_addr(NextOsc2Waveform, 1);
		NextOsc2WaveReady = 0;
	}	
	
	if(NextOsc2LevelReady)
	{
		osc2.level = NextOsc2Level;
		NextOsc2LevelReady = 0;
	}	
	
	cbi(PORTD, PORTD5); //Timing stop
}