#ifndef PINDEFS_H_
#define PINDEFS_H_

#define F_CPU	16000000UL

#include <avr/io.h>
#include <stdint.h>

#define sbi(port,bit)	(port) |= (1 << (bit))
#define cbi(port,bit)	(port) &= ~(1 << (bit))

#endif /* PINDEFS_H_ */