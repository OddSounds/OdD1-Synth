#ifndef OSC_H_
#define OSC_H_
#include "PinDefs.h"

#include <avr/pgmspace.h>

#define SUB_PHASE_SHIFT		127

typedef struct
{
	uint8_t note, waveform, wavemix;
	uint8_t phase;
	uint32_t tuningword, phaseaccum;
	uint8_t* index;
}osc_t;

void Osc_Init();
void Osc_Reset();

void Osc_ChangeWave1(uint16_t wave);
void Osc_ChangeScale1(uint16_t scale);

void Osc_ChangeWave2(uint16_t wave);
void Osc_ChangeScale2(uint16_t scale);

#endif /* OSC_H_ */