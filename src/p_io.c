#include "p_io.h"

extern void _io_sleep(int16_t msec, int16_t tpms);

void io_sleep(int16_t msec)
{
	_io_sleep(msec, IO_TPMS);
}
