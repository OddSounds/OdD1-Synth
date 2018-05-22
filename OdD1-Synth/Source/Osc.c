#include "Osc.h"
#include "ADC.h"

#include "WaveTables.h"
#include <stdlib.h>

uint8_t oscsync = 0;
osc_t osc1, osc2;

volatile uint8_t NextOsc1LevelReady, NextOsc2LevelReady;
volatile uint8_t NextOsc1WaveReady, NextOsc2WaveReady;

uint8_t NextOsc1Waveform[2], NextOsc2Waveform[2];
uint8_t NextOsc1Level[2], NextOsc2Level[2];

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
	osc1.wavemix = osc2.wavemix = 255;
	osc1.wavemixnext = osc2.wavemixnext = 0;
	osc1.phaseaccum = osc2.phaseaccum = 0;
	osc1.phase = osc2.phase = 0;
	osc1.level = osc2.level = 0x0140;
	osc1.tuningword = osc2.tuningword = pgm_read_dword(keyFreq + osc1.note + KEY_OFFSET);
	osc1.index = byte_addr(osc1.phaseaccum, 2);
	osc2.index = byte_addr(osc2.phaseaccum, 2);
	
	//Setup ADC events
	ADCChangeHandler[ANALOG_OSC1_WAVEFORM] = Osc_ChangeWave1;
	ADCChangeHandler[ANALOG_OSC2_WAVEFORM] = Osc_ChangeWave2;
	ADCChangeHandler[ANALOG_OSC1_DUTY_CYCLE] = Osc_ChangeLevel1;
	ADCChangeHandler[ANALOG_OSC2_DUTY_CYCLE] = Osc_ChangeLevel2;
		
	//Set flags for updating osc on first run
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
	if(*((uint16_t*)NextOsc1Waveform) != wave)
	{
		NextOsc1WaveReady = 0;
		*((uint16_t*)NextOsc1Waveform) = wave;
		NextOsc1WaveReady = 1;
	}
}

void Osc_ChangeLevel1(uint16_t level)
{
	if(*((uint16_t*)NextOsc1Level) != (level >> 1))
	{
		NextOsc1LevelReady = 0;
		*((uint16_t*)NextOsc1Level) = level >> 1;
		NextOsc1LevelReady = 1;
	}
}

void Osc_ChangeWave2(uint16_t wave)
{
	if(*((uint16_t*)NextOsc2Waveform) != wave)
	{
		NextOsc2WaveReady = 0;
		*((uint16_t*)NextOsc2Waveform) = wave;
		NextOsc2WaveReady = 1;
	}
}

void Osc_ChangeLevel2(uint16_t level)
{
	if(*((uint16_t*)NextOsc2Level) != (level >> 1))
	{
		NextOsc2LevelReady = 0;
		*((uint16_t*)NextOsc2Level) = level >> 1;
		NextOsc2LevelReady = 1;	
	}
}

//53% of 510 cycles (LFO/ADSR/NOISE)
ISR(TIMER0_OVF_vect)
{
	uint8_t osc1Out[2], osc2Out[2];
	uint8_t fraction[2], whole[2];
	uint8_t mixOut[2];
	uint32_t mixindex;
	sbi(PORTD, PORTD5); //Timing start
	
	osc1.phaseaccum += osc1.tuningword;	
	//Grab osc1 waveform
	//Reusing fraction and whole. Sue me.
	fraction[1] = whole[1] = 0;
	mixindex = (int)analogWaveTable + (uint8_t)(*osc1.index + osc1.phase);
	fraction[0] = pgm_read_byte(mixindex + waveformOffset[osc1.waveform]);
	whole[0] = pgm_read_byte(mixindex + waveformOffset[osc1.waveform + 1]);
	
	//Mix waveform 1
	*((uint16_t*)fraction) *= osc1.wavemix;
	*((uint16_t*)whole) *= osc1.wavemixnext;
	*((uint16_t*)whole) += *((uint16_t*)fraction);
	osc1Out[0] = whole[1];
	
	//Scale osc1
	*((uint16_t*)fraction) = osc1Out[0] * *byte_addr(osc1.level, 0);
	*((uint16_t*)whole) = osc1Out[0] * *byte_addr(osc1.level, 1);
	*((uint16_t*)osc1Out) = *byte_addr(fraction, 1);
	*((uint16_t*)osc1Out) += *byte_addr(whole, 0);
	
	
	osc2.phaseaccum += osc2.tuningword;
	//Grab osc2 waveform
	fraction[1] = whole[1] = 0;
	mixindex = (int)analogWaveTable + (uint8_t)(*osc2.index + osc2.phase);
	fraction[0] = pgm_read_byte(mixindex + waveformOffset[osc2.waveform]);
	whole[0] = pgm_read_byte(mixindex + waveformOffset[osc2.waveform + 1]);
	
	//Mix waveform 2
	*((uint16_t*)fraction) *= osc2.wavemix;
	*((uint16_t*)whole) *= osc2.wavemixnext;
	*((uint16_t*)whole) += *((uint16_t*)fraction);
	osc2Out[0] = whole[1];
	
	//Scale osc2
	*((uint16_t*)fraction) = osc2Out[0] * *byte_addr(osc2.level, 0);
	*((uint16_t*)whole) = osc2Out[0] * *byte_addr(osc2.level, 1);
	*((uint16_t*)osc2Out) = *byte_addr(fraction, 1);
	*((uint16_t*)osc2Out) += *byte_addr(whole, 0);
	
	
	//Mix the signals
	*((int16_t*)mixOut) = *((uint16_t*)osc1Out);
	*((int16_t*)mixOut) -= (osc1.level >> 1) - 1; //Offset
	*((int16_t*)mixOut) += *((uint16_t*)osc2Out);
	*((int16_t*)mixOut) -= (osc2.level >> 1) - 1; //Offset
	*((int16_t*)mixOut) >>= 1;

	//Restore offset
	*((int16_t*)mixOut) += 0x7F;

	//Hard clip
	//Better way?
	if(*((int16_t*)mixOut) > 0xFF)
		mixOut[0] = 0xFF;
	else if(*((int16_t*)mixOut) < 0)
		mixOut[0] = 0;
	
	OCR0A = mixOut[0];
	
	//Limit only 1 to be updated per cycle
	if(NextOsc1WaveReady)
	{
		osc1.waveform = NextOsc1Waveform[1];
		osc1.wavemix = ~NextOsc1Waveform[0];
		osc1.wavemixnext = NextOsc1Waveform[0];
		NextOsc1WaveReady = 0;
	}
	else if(NextOsc1LevelReady)
	{
		osc1.level = *((uint16_t*)NextOsc1Level);
		NextOsc1LevelReady = 0;
	}
	else if(NextOsc2WaveReady)
	{
		osc2.waveform = NextOsc2Waveform[1];
		osc2.wavemix = ~NextOsc2Waveform[0];
		osc2.wavemixnext = NextOsc2Waveform[0];
		NextOsc2WaveReady = 0;
	}	
	else if(NextOsc2LevelReady)
	{
		osc2.level = *((uint16_t*)NextOsc2Level);
		NextOsc2LevelReady = 0;
	}
	
	cbi(PORTD, PORTD5); //Timing stop
}