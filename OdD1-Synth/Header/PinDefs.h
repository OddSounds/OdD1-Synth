#ifndef PINDEFS_H_
#define PINDEFS_H_

#define F_CPU	16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

typedef struct
{
	volatile uint8_t* port;
	uint8_t bit;
}pin_t;

#define SetPin(pin)		*(pin.port) |= (1 << pin.bit)
#define ClrPin(pin)		*(pin.port) &= ~(1 << pin.bit)
#define TglPin(pin)		*(pin.port) ^= (1 << pin.bit)

#define sbi(port,bit)	(port) |= (1 << (bit))
#define cbi(port,bit)	(port) &= ~(1 << (bit))

#endif /* PINDEFS_H_ */