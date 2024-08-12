#ifndef _D_LED2_H_
#define _D_LED2_H_

#include <stdint.h>

#include "p_io.h"

#define LED2_R_MASK (1<<0)
#define LED2_G_MASK (1<<1)

enum led2_color
{
	LED2_BLANK=0,
	LED2_R_COL=1,	
	LED2_G_COL=2,
	LED2_Y_COL=3
};

struct led2
{
	volatile uint8_t *port;
	uint8_t pin_r;
	uint8_t pin_g;
};

void led2_init(struct led2 *led2);
void led2_send(struct led2 *led2, enum led2_color color);

#endif/*_D_LED2_H_*/
