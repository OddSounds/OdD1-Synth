#ifndef DIGITALIO_H_
#define DIGITALIO_H_

#include "PinDefs.h"

typedef enum
{
	SWITCH_OSC_SYNC = 0,
	SWITCH_RING_MOD,
	SWITCH_MONO_DUO,
	
}EXPANDER_PIN;

void DigitalPins_Init();

void DigitalPins_Update();

#endif /* DIGITALIO_H_ */