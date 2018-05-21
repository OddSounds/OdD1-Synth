#include "Osc.h"
#include "ADC.h"

#include "WaveTables.h"
#include <stdlib.h>

uint8_t oscsync = 0;
volatile osc_t osc1, osc2;

volatile uint8_t NextOsc1LevelReady, NextOsc2LevelReady;
volatile NextOsc1WaveReady, NextOsc2WaveReady;

uint8_t Osc1WaveChanged, Osc2WaveChanged;
uint8_t Osc1LevelChanged, Osc2LevelChanged;

uint16_t NextOsc1Waveform, NextOsc2WaveForm;
uint16_t NextOsc1Level, NextOsc2Level;

volatile uint16_t Osc1Level, Osc2Level;

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
	
	Osc1WaveChanged = Osc2WaveChanged = 1;
	Osc1LevelChanged = Osc2LevelChanged = 1;
	
	Osc1Level = Osc2Level = 0;
	NextOsc1LevelReady = NextOsc2LevelReady = 0;
	
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
	
}

void Osc_ChangeScale2(uint16_t scale)
{
	
}

//46% used. Aiming for 80% MAXIMUM
ISR(TIMER0_OVF_vect)
{
	uint16_t osc1Out, osc2Out;
	uint16_t fraction, whole;
	int16_t mixOut;
	sbi(PORTD, PORTD5); //Timing start
	
	osc1Out = osc2Out = mixOut = 0;
	
	osc1.phaseaccum += osc1.tuningword;
	osc2.phaseaccum += osc2.tuningword;
	
	//Maybe don't do this here
	osc1.waveform = *byte_addr(AnalogReading[ANALOG_OSC1_WAVEFORM], 1);
	osc1.wavemix = *byte_addr(AnalogReading[ANALOG_OSC1_WAVEFORM], 0);
	
	osc2.waveform = *byte_addr(AnalogReading[ANALOG_OSC2_WAVEFORM], 1);
	osc2.wavemix = *byte_addr(AnalogReading[ANALOG_OSC2_WAVEFORM], 0);
	
	//Grab osc1 waveform
	//Reusing fraction and whole. Sue me.
	fraction = whole = 0;
	*byte_addr(fraction, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc1.waveform] + (uint8_t)(*osc1.index + osc1.phase));
	*byte_addr(whole, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc1.waveform + 1] + (uint8_t)(*osc1.index + osc1.phase));
	
	if(Osc1WaveChanged)
	{
		//Mix waveform 1
		fraction *= (0x0100 - osc1.wavemix);
		whole *= osc1.wavemix;
		whole += fraction;
		*byte_addr(osc1Out, 0) = *byte_addr(whole, 1);
		
		Osc1WaveChanged = 0;
	}
	
	//Scale osc1
	if(Osc1LevelChanged)
	{
		fraction = *byte_addr(osc1Out, 0) * *byte_addr(Osc1Level, 0);
		whole = *byte_addr(osc1Out, 0) * *byte_addr(Osc1Level, 1);
		osc1Out = *byte_addr(fraction, 1);
		osc1Out += *byte_addr(whole, 0);
		
		Osc1LevelChanged = 0;
	}
	
	//Grab osc2 waveform
	fraction = whole = 0;
	*byte_addr(fraction, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc2.waveform] + (uint8_t)(*osc2.index + osc2.phase));
	*byte_addr(whole, 0) = pgm_read_byte(analogWaveTable + waveformOffset[osc2.waveform + 1] + (uint8_t)(*osc2.index + osc2.phase));
	
	//Mix waveform 2
	if(Osc2WaveChanged)
	{
		fraction *= (0x0100 - osc2.wavemix);
		whole *= osc2.wavemix;
		whole += fraction;
		*byte_addr(osc2Out, 0) = *byte_addr(whole, 1);	
		
		Osc2WaveChanged = 0;
	}
	
	if(Osc2LevelChanged)
	{
		fraction = *byte_addr(osc2Out, 0) * *byte_addr(Osc2Level, 0);
		whole = *byte_addr(osc2Out, 0) * *byte_addr(Osc2Level, 1);
		osc2Out = *byte_addr(fraction, 1);
		osc2Out += *byte_addr(whole, 0);
		
		Osc2LevelChanged = 0;
	}
	
	//Mix the signals
	mixOut = osc1Out;
	mixOut -= (Osc1Level >> 1) - 1; //Offset
	mixOut += osc2Out;
	mixOut -= (Osc2Level >> 1) - 1; //Offset
	mixOut >>= 1;

	//Hard clip
	if(mixOut > 128)
		mixOut = 127;
	else if(mixOut < -127)
		mixOut = -127;
		
	//Restore offset
	mixOut += 0x7F;
	
	OCR0A = *byte_addr(mixOut, 0);
	
	cbi(PORTD, PORTD5); //Timing stop
}