#include "p_isr.h"

#define ISR_MCUCR_ISC_MASK (ISC01|ISC00)

void 
isr_set_int0_trig(enum isr_int0_trig trig)
{
	*MCUCR &= ~ISR_MCUCR_ISC_MASK;
	*MCUCR |= trig;
}

void 
isr_set_pcint0_pin(uint8_t pin)
{
	*PCMSK |= pin;
}

void 
isr_clr_pcint0_pin(uint8_t pin)
{
	*PCMSK &= ~pin;
}

void 
isr_en_int(enum isr_int i)
{
	*GIMSK = i;
}

void
isr_clr_int(enum isr_int i)
{
	*GIFR = i;
}
