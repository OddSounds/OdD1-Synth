#ifndef ADC_H_
#define ADC_H_

#include "PinDefs.h"

#define NUM_ADC_INPUT	4
#define MIN_ADC_CHANGE	5

//How many knobs do I need?
typedef enum
{
	ANALOG_OSC1_WAVEFORM = 0,
	ANALOG_OSC2_WAVEFORM,
	ANALOG_OSC1_DUTY_CYCLE,
	ANALOG_OSC2_DUTY_CYCLE,
	ANALOG_OSC1_OCTAVE,
	ANALOG_OSC2_OCTAVE,
	ANALOG_DETUNE_FINE,
	ANALOG_DETUNE_COARSE,
	ANALOG_DETUNE_PHASE,
	ANALOG_OSC1_LEVEL,
	ANALOG_OSC2_LEVEL,
	ANALOG_NOISE_LEVEL,
	ANALOG_LFO_WAVEFORM,
	ANALOG_LFO_RATE,
	ANALOG_LFO_DEPTH,
	ANALOG_FILTER1_CUTOFF,
	ANALOG_FILTER2_CUTOFF,
	ANALOG_FILTER_RES,
	ANALOG_DELAY_TIME,
	ANALOG_ATTACK_RATE,
	ANALOG_DECAY_RATE,
	ANALOG_SUSTAIN_LEVEL,
	ANALOG_RELEASE_RATE,
	ANALOG_SEQUENCE_RATE,
	ANALOG_SEQUENCE_SWING,
	ANALOG_DO_NOT_READ, //Handle wrap around mux switching
	TOTAL_ANALOG_READINGS //This many - 1
}ANALOG_READING;

void ADC_Init();

void ADC_Update();
void ADC_UpdateMux();

#endif /* ADC_H_ */