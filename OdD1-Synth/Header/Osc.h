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



#endif /* OSC_H_ */