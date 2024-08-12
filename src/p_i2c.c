#include "p_i2c.h"

static void (*_i2c_on_recv_byte)(uint8_t byte);
static uint8_t _i2c_addr = 0x00;
static enum i2c_listen_state _i2c_listen_state;

#define STATUS(EXTRA, COUNT) (EXTRA | USIOIF | USIPF | USIDC | COUNT)

void 
i2c_init_slave(void)
{
	*IO_OUT(I2C_PORT) |= I2C_SCL_PIN;
	*IO_OUT(I2C_PORT) |= I2C_SDA_PIN;
	*IO_DD(I2C_PORT) |= I2C_SCL_PIN;
	*IO_DD(I2C_PORT) &= ~I2C_SDA_PIN;
	*USICR = USIWM1 | USICS1;
	/* clear status flags, set count at 0 */
	*USISR = STATUS(USISIF, 0x0);
}

void
i2c_listen(uint8_t addr, void (*on_recv_byte)(uint8_t byte))
{
	_i2c_addr = addr;
	_i2c_on_recv_byte = on_recv_byte;
	_i2c_listen_state = I2C_ST_RECV_ADDR;
	*USICR = USISIE | USIWM1 | USICS1;
}

ISR_VEC(USI_START_INT) 
{
	*IO_DD(I2C_PORT) &= ~I2C_SDA_PIN;

	for (;;)
	{
		uint8_t i2c_pins = *IO_IN(I2C_PORT);
		if (i2c_pins & I2C_SDA_PIN) 
		{
			*USICR = USIWM1 | USICS1;
			/* clear status flags, set count at 0 */
			*USISR = STATUS(USISIF, 0x0);
			break;
		}
		if (!(i2c_pins & I2C_SCL_PIN))
		{
			*USICR = USIOIE | USIWM0 | USIWM1 | USICS1;
			/* clear status flags, set count at 0 */
			*USISR = STATUS(USISIF, 0x0);
			break;
		}
	}
}

ISR_VEC(USI_OVF_INT)
{
	switch (_i2c_listen_state)
	{
		case I2C_ST_RECV_ADDR:
			if (*USIDR >> 1 == _i2c_addr)
			{
				_i2c_listen_state = I2C_ST_RECV_BYTE; 
				/* to send ACK */
				*USIDR = 0;
				*IO_DD(I2C_PORT) |= I2C_SDA_PIN;
			}
			else
			{
				/* to start cond */
				*USICR |= USISIE;
				*USICR &= ~USISIE;
			}
			*USISR = STATUS(0, 0x0);
			break;
		case I2C_ST_RECV_BYTE:
			_i2c_listen_state = I2C_ST_SEND_ACK;
			*IO_DD(I2C_PORT) &= ~I2C_SDA_PIN;
			*USISR = STATUS(0, 0x0);
			break;
		case I2C_ST_SEND_ACK:
			_i2c_listen_state = I2C_ST_RECV_BYTE;
			_i2c_on_recv_byte(*USIDR);
			*USIDR = 0;
			*IO_DD(I2C_PORT) &= ~I2C_SDA_PIN;
			/* set count to 14 */
			*USISR = STATUS(0, 0xe);
			break;
	}
}
