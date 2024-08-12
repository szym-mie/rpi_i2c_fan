#include "p_tim0.h"

void 
tim0_init(void)
{
	tim0_set_wgm(TIM0_CTC);
	tim0_set_cs(TIM0_STOP);
	tim0_set_coma(TIM0_NC);
	tim0_set_comb(TIM0_NC);
	tim0_set_cnt(0x00);
}

void 
tim0_set_cmpa(uint8_t t)
{
	*OCR0A = t;
}

void 
tim0_set_cmpb(uint8_t t)
{
	*OCR0B = t;
}

#define TIM0_COMA_OFFSET 6
#define TIM0_COMA_MASK (COM0A1|COM0A0)
#define TIM0_COMB_OFFSET 4
#define TIM0_COMB_MASK (COM0B1|COM0B0)

void 
tim0_set_coma(enum tim0_com com)
{
	*TCCR0A &= ~TIM0_COMA_MASK;
	*TCCR0A |= com<<TIM0_COMA_OFFSET;
}

void 
tim0_set_comb(enum tim0_com com)
{
	*TCCR0A &= ~TIM0_COMB_MASK;
	*TCCR0A |= com<<TIM0_COMB_OFFSET;
}

#define TIM0_WGMA_GETTER(WGM) ((WGM>>0) & 0x3)
#define TIM0_WGMB_GETTER(WGM) ((WGM>>2) & 0x1)

#define TIM0_WGMA_OFFSET 0
#define TIM0_WGMA_MASK (WGM00|WGM01)
#define TIM0_WGMB_OFFSET 3
#define TIM0_WGMB_MASK (WGM02)

void 
tim0_set_wgm(enum tim0_wgm wgm)
{
	*TCCR0A &= ~TIM0_WGMA_MASK;
	*TCCR0A |= TIM0_WGMA_GETTER(wgm)<<TIM0_WGMA_OFFSET;
	*TCCR0B &= ~TIM0_WGMB_MASK;
	*TCCR0B |= TIM0_WGMB_GETTER(wgm)<<TIM0_WGMB_OFFSET;
}

#define TIM0_CS_MASK (CS02|CS01|CS00)

void 
tim0_set_cs(enum tim0_cs cs)
{
	*TCCR0B &= ~TIM0_CS_MASK;
	*TCCR0B |= cs;
}

void 
tim0_set_cnt(uint8_t t)
{
	*TCNT0 = t;
}

void 
tim0_en_int(enum tim0_int i)
{
	*TIMSK = i;
}

void
tim0_clr_int(enum tim0_int i)
{
	*TIFR = i;
}
