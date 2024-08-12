#ifndef _P_IO_H_
#define _P_IO_H_

#include <stdint.h>

#include "p_t85.h"

#define IO_MHZ 8L
#define IO_TPMS (IO_MHZ * 1000UL)
#define IO_TPS (IO_TPMS * 1000UL)
#define IO_TICKS(NS) (NS * IO_MHZ / 4000UL)
#define IO_TSLEEP(NS) (IO_TICKS(NS) - 2)

#define IO_P1 (1<<0)
#define IO_P2 (1<<1)
#define IO_P3 (1<<2)
#define IO_P4 (1<<3)
#define IO_P5 (1<<4)
#define IO_P6 (1<<5)
#define IO_P7 (1<<6)
#define IO_P8 (1<<7)

#define IO_PB PINB

#define IO_IN(PORT) (PORT+0)
#define IO_OUT(PORT) (PORT+2)
#define IO_DD(PORT) (PORT+1)

#define IO_LOB(B) ((B>>0) & 255)
#define IO_HIB(B) ((B>>8) & 255)


/*
 * sleep about n milliseconds
 */
void io_sleep(int16_t msec);

/*
 * sleep for (n * 4 + 8) ticks of CPU time
 * use IO_TSLEEP() to get accurate amount of ticks regardless of CPU freq.
 */
extern void io_tsleep(uint8_t quadt);

#endif/*_P_IO_H_*/
