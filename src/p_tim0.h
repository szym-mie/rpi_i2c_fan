#ifndef _P_TIM0_H_
#define _P_TIM0_H_

#include <stdint.h>

#include "p_io.h"

#define TIM0_OC0A_PIN IO_P2 
#define TIM0_OC0A_PORT IO_PB 
#define TIM0_OC0B_PIN IO_P7 
#define TIM0_OC0B_PORT IO_PA 
#define TIM0_OC1A_PIN IO_P6 
#define TIM0_OC1A_PORT IO_PA 
#define TIM0_OC1B_PIN IO_P5 
#define TIM0_OC1B_PORT IO_PA 

enum tim0_com
{
	TIM0_NC=0,
	TIM0_TOG=1,
	TIM0_CLR=2,
	TIM0_SET=3
};

enum tim0_wgm
{
	TIM0_NORM=0,
	TIM0_PC_PWM_FF=1,
	TIM0_CTC=2,
	TIM0_FS_PWM_FF=3,
	TIM0_PC_PWM_OC=5,
	TIM0_FS_PWM_OC=7
};

enum tim0_cs
{
	TIM0_STOP=0,
	TIM0_DIV_1=1,
	TIM0_DIV_8=2,
	TIM0_DIV_64=3,
	TIM0_DIV_256=4,
	TIM0_DIV_1024=5,
	TIM0_EXT_RISE=6,
	TIM0_EXT_FALL=7
};

enum tim0_int
{
	TIM0_OCIE_A=OCIE0A,
	TIM0_OCIE_B=OCIE0B,
	TIM0_TOIE=TOIE0
};

void tim0_init(void);
void tim0_set_cmpa(uint8_t t);
void tim0_set_cmpb(uint8_t t);
void tim0_set_coma(enum tim0_com com);
void tim0_set_comb(enum tim0_com com);
void tim0_set_wgm(enum tim0_wgm wgm);
void tim0_set_cs(enum tim0_cs cs);
void tim0_set_cnt(uint8_t t);

/*
 * set enable mask for interrupts - use bitwise ORs to create mask
 */
void tim0_en_int(enum tim0_int i);

/*
 * clear interrupt flag for particular interrupt or a mask
 */
void tim0_clr_int(enum tim0_int i);

#endif/*_P_TIM0_H_*/
