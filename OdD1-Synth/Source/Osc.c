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
	sbi(DDRB, PORTB1); //OSC0A
	sbi(DDRD, PORTD5); //Just used for timing
	
	//Initialize oscillators
	osc1.note = osc2.note = 50;
	osc1.waveform = osc2.waveform = WAVE_SINE;
	osc1.wavemix = osc2.wavemix = 255;
	osc1.wavemixnext = osc2.wavemixnext = 0;
	osc1.phaseaccum = osc2.phaseaccum = 0;
	osc1.phase = osc2.phase = 0;
	*((uint16_t*)osc1.level) = 0x0100;
	*((uint16_t*)osc2.level) = 0;
	osc1.tuningword = osc2.tuningword = 0x010000;
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
		
	// Timer1 PWM Mode set to fast PWM 9-bit
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
	TCCR1B = (1 << WGM12);
	TIMSK1 = (1 << TOIE1);
	
	sbi(TCCR1B, CS10);
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
ISR(TIMER1_OVF_vect)
{
	uint16_t oscA, oscB;
	uint16_t index;
	int32_t oscmix;
	sbi(PORTD, PORTD5); //Timing start
	
	osc1.phaseaccum += osc1.tuningword;	
	index = *((uint16_t*)&osc1.phaseaccum + 1) & 0x01FF;
	oscA = pgm_read_word(analogWaveTable + waveformOffset[osc1.waveform] + index);
	oscB = pgm_read_word(analogWaveTable + waveformOffset[osc1.waveform + 1] + index);
	oscmix = oscA;
	oscmix -= oscB;
	oscmix *= osc1.wavemix;
	oscmix = (int32_t)*((int16_t*)byte_addr(oscmix, 1));
	OCR1A = (uint16_t)(oscmix + oscB);
	//Grab osc1 waveform
	//Reusing fraction and whole. Sue me.
	/*fraction[1] = whole[1] = 0;
	mixindex = (int)analogWaveTable + (uint8_t)(*osc1.index + osc1.phase);
	fraction[0] = pgm_read_byte(mixindex + waveformOffset[osc1.waveform]);
	whole[0] = pgm_read_byte(mixindex + waveformOffset[osc1.waveform + 1]);
	
	//Mix waveform 1
	*((uint16_t*)fraction) *= osc1.wavemix;
	*((uint16_t*)whole) *= osc1.wavemixnext;
	*((uint16_t*)whole) += *((uint16_t*)fraction);
	osc1Out[0] = whole[1];*/
	
	
	osc2.phaseaccum += osc2.tuningword;
	index = *((uint16_t*)&osc2.phaseaccum + 1) & 0x01FF;
	oscA = pgm_read_word(analogWaveTable + waveformOffset[osc2.waveform] + index);
	oscB = pgm_read_word(analogWaveTable + waveformOffset[osc2.waveform + 1] + index);
	oscmix = oscA;
	oscmix -= oscB;
	oscmix *= osc2.wavemix;
	oscmix = (int32_t)*((int16_t*)byte_addr(oscmix, 1));
	OCR2A = (uint16_t)(oscmix + oscB);
	//Grab osc2 waveform
	/*fraction[1] = whole[1] = 0;
	mixindex = (int)analogWaveTable + (uint8_t)(*osc2.index + osc2.phase);
	fraction[0] = pgm_read_byte(mixindex + waveformOffset[osc2.waveform]);
	whole[0] = pgm_read_byte(mixindex + waveformOffset[osc2.waveform + 1]);
	
	//Mix waveform 2
	*((uint16_t*)fraction) *= osc2.wavemix;
	*((uint16_t*)whole) *= osc2.wavemixnext;
	*((uint16_t*)whole) += *((uint16_t*)fraction);
	osc2Out[0] = whole[1];*/
	
	//Limit only 1 to be updated per cycle
	if(NextOsc1WaveReady)
	{
		osc1.waveform = NextOsc1Waveform[1];
		osc1.wavemix = ~NextOsc1Waveform[0];
		NextOsc1WaveReady = 0;
	}
	else if(NextOsc2WaveReady)
	{
		osc2.waveform = NextOsc2Waveform[1];
		osc2.wavemix = ~NextOsc2Waveform[0];
		NextOsc2WaveReady = 0;
	}	
	
	cbi(PORTD, PORTD5); //Timing stop
}