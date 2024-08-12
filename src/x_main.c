#include <stdint.h>

#include "p_io.h"
#include "d_led2.h"
#include "p_tim0.h"
#include "p_i2c.h"

#define I2C_ADDR 0x91

enum recv_state
{
	ST_IDLE,
};

enum recv_cmd
{
	CMD_NOP=0x00,
};

struct led2 status_out;

void
on_next_byte(uint8_t byte)
{
	led2_send(&status_out, byte & 0x03);
	tim0_set_cmpb(byte>>2);
}

int
main(void)
{
	status_out.port = IO_PB;
	status_out.pin_r = IO_P4;
	status_out.pin_g = IO_P5;

	led2_init(&status_out);
	led2_send(&status_out, LED2_R_COL);

	tim0_init();
	tim0_set_cs(TIM0_DIV_8);	
	tim0_set_wgm(TIM0_PC_PWM_OC);
	tim0_set_cmpa(64);
	tim0_set_comb(TIM0_SET);
	
	i2c_init_slave();
	i2c_listen(I2C_ADDR, on_next_byte);

	return 0;
}
