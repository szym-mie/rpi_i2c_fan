#ifndef _P_ISR_H_
#define _P_ISR_H_

#include <stdint.h>

#include "p_t85.h"
#include "p_io.h"

#define ISR_INT_ON() volatile asm("sei");
#define ISR_INT_OFF() volatile asm("cli");

#define ISR_VEC(V) \
	void V(void) __attribute__((__signal__, __used__, __externally_visible__)); \
	void V(void)

enum isr_int0_trig
{
	ISR_LOW=0,
	ISR_CHANGE=1,
	ISR_FALL=2,
	ISR_RISE=3
};

enum isr_int
{
	ISR_INT0=INT0,
	ISR_PCINT0=PCINT0
};

void isr_set_int0_trig(enum isr_int0_trig trig);
void isr_set_pcint0_pin(uint8_t pin);
void isr_clr_pcint0_pin(uint8_t pin);

/*
 * set enable mask for interrupts - use bitwise ORs to create mask
 */
void isr_en_int(enum isr_int i);

/*
 * clear interrupt flag for particular interrupt or a mask
 */
void isr_clr_int(enum isr_int i);

#endif/*_P_ISR_H_*/
