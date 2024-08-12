#ifndef _P_I2C_H_
#define _P_I2C_H_

#include <stdint.h>

#include "p_t85.h"
#include "p_io.h"
#include "p_isr.h"

#define I2C_PORT IO_PB
#define I2C_SDA_PIN IO_P1
#define I2C_SCL_PIN IO_P3

enum i2c_listen_state
{
	I2C_ST_RECV_ADDR,
	I2C_ST_RECV_BYTE,
	I2C_ST_SEND_ACK
};

void i2c_init_slave(void);
void i2c_listen(uint8_t addr, void (*on_recv_byte)(uint8_t byte));

#endif/*_P_I2C_H_*/
