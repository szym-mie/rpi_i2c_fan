#include "d_led2.h"
 
void 
led2_init(struct led2 *led2)
{
	*IO_DD(led2->port) |= led2->pin_r | led2->pin_g;
}

void 
led2_send(struct led2 *led2, enum led2_color color)
{
	uint8_t col_r = color & LED2_R_MASK ? led2->pin_r : 0;
	uint8_t col_g = color & LED2_G_MASK ? led2->pin_g : 0;
	*IO_OUT(led2->port) &= ~(led2->pin_r | led2->pin_g);
	*IO_OUT(led2->port) |= col_r | col_g;
}
