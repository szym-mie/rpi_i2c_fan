#ifndef _T85_H_
#define _T85_H_

#define IO_REG(IO_ADDR) ((volatile uint8_t *) IO_ADDR) 

#define SREG IO_REG(0x3F) /* reference page 8 */

#define I (1<<7)
#define T (1<<6)
#define H (1<<5)
#define S (1<<4)
#define V (1<<3)
#define N (1<<2)
#define Z (1<<1)
#define C (1<<0)

#define SPH IO_REG(0x3E) /* reference page 11 */

#define SP9 (1<<1)
#define SP8 (1<<0)

#define SPL IO_REG(0x3D) /* reference page 11 */

#define SP7 (1<<7)
#define SP6 (1<<6)
#define SP5 (1<<5)
#define SP4 (1<<4)
#define SP3 (1<<3)
#define SP2 (1<<2)
#define SP1 (1<<1)
#define SP0 (1<<0)

#define GIMSK IO_REG(0x3B) /* reference page 51 */

#define INT0 (1<<6)
#define PCIE (1<<5)

#define GIFR IO_REG(0x3A) /* reference page 52 */

#define INTF0 (1<<6)
#define PCIF (1<<5)

#define TIMSK IO_REG(0x39) /* reference page 102 */

#define OCIE1A (1<<6)
#define OCIE1B (1<<5)
#define OCIE0A (1<<4)
#define OCIE0B (1<<3)
#define TOIE1 (1<<2)
#define TOIE0 (1<<1)

#define TIFR IO_REG(0x38) /* reference page 81 */

#define OCF1A (1<<6)
#define OCF1B (1<<5)
#define OCF0A (1<<4)
#define OCF0B (1<<3)
#define TOV1 (1<<2)
#define TOV0 (1<<1)

#define SPMCSR IO_REG(0x37) /* reference page 145 */

#define RSIG (1<<5)
#define CTPB (1<<4)
#define RFLB (1<<3)
#define PGWRT (1<<2)
#define PGERS (1<<1)
#define SPMEN (1<<0)

#define MCUCR IO_REG(0x35) /* reference page 64 */

#define BODS (1<<7)
#define PUD (1<<6)
#define SE (1<<5)
#define SM1 (1<<4)
#define SM0 (1<<3)
#define BODSE (1<<2)
#define ISC01 (1<<1)
#define ISC00 (1<<0)

#define MCUSR IO_REG(0x34) /* reference page 44, */

#define WDRF (1<<3)
#define BORF (1<<2)
#define EXTRF (1<<1)
#define PORF (1<<0)

#define TCCR0B IO_REG(0x33) /* reference page 79 */

#define FOC0A (1<<7)
#define FOC0B (1<<6)
#define WGM02 (1<<3)
#define CS02 (1<<2)
#define CS01 (1<<1)
#define CS00 (1<<0)

#define TCNT0 IO_REG(0x32) /* reference page 80 */


#define OSCCAL IO_REG(0x31) /* reference page 31 */


#define TCCR1 IO_REG(0x30) /* reference page 100 */

#define CTC1 (1<<7)
#define PWM1A (1<<6)
#define COM1A1 (1<<5)
#define COM1A0 (1<<4)
#define CS13 (1<<3)
#define CS12 (1<<2)
#define CS11 (1<<1)
#define CS10 (1<<0)

#define TCNT1 IO_REG(0x2F) /* reference page 102 */


#define OCR1A IO_REG(0x2E) /* reference page 102 */


#define OCR1C IO_REG(0x2D) /* reference page 102 */


#define GTCCR IO_REG(0x2C) /* reference page 101 */

#define TSM (1<<7)
#define PWM1B (1<<6)
#define COM1B1 (1<<5)
#define COM1B0 (1<<4)
#define FOC1B (1<<3)
#define FOC1A (1<<2)
#define PSR1 (1<<1)
#define PSR0 (1<<0)

#define OCR1B IO_REG(0x2B) /* reference page 92 */


#define TCCR0A IO_REG(0x2A) /* reference page 77 */

#define COM0A1 (1<<7)
#define COM0A0 (1<<6)
#define COM0B1 (1<<5)
#define COM0B0 (1<<4)
#define WGM01 (1<<1)
#define WGM00 (1<<0)

#define OCR0A IO_REG(0x29) /* reference page 80 */


#define OCR0B IO_REG(0x28) /* reference page 81 */


#define PLLCSR IO_REG(0x27) /* reference page 103 */

#define LSM (1<<7)
#define PCKE (1<<2)
#define PLLE (1<<1)
#define PLOCK (1<<0)

#define CLKPR IO_REG(0x26) /* reference page 32 */

#define CLKPCE (1<<7)
#define CLKPS3 (1<<3)
#define CLKPS2 (1<<2)
#define CLKPS1 (1<<1)
#define CLKPS0 (1<<0)

#define DT1A IO_REG(0x25) /* reference page 107 */

#define DT1AH3 (1<<7)
#define DT1AH2 (1<<6)
#define DT1AH1 (1<<5)
#define DT1AH0 (1<<4)
#define DT1AL3 (1<<3)
#define DT1AL2 (1<<2)
#define DT1AL1 (1<<1)
#define DT1AL0 (1<<0)

#define DT1B IO_REG(0x24) /* reference page 107 */

#define DT1BH3 (1<<7)
#define DT1BH2 (1<<6)
#define DT1BH1 (1<<5)
#define DT1BH0 (1<<4)
#define DT1BL3 (1<<3)
#define DT1BL2 (1<<2)
#define DT1BL1 (1<<1)
#define DT1BL0 (1<<0)

#define DTPS1 IO_REG(0x23) /* reference page 106 */

#define DTPS11 (1<<1)
#define DTPS10 (1<<0)

#define DWDR IO_REG(0x22) /* reference page 140 */


#define WDTCR IO_REG(0x21) /* reference page 45 */

#define WDIF (1<<7)
#define WDIE (1<<6)
#define WDP3 (1<<5)
#define WDCE (1<<4)
#define WDE (1<<3)
#define WDP2 (1<<2)
#define WDP1 (1<<1)
#define WDP0 (1<<0)

#define PRR IO_REG(0x20) /* reference page 36 */

#define PRTIM1 (1<<3)
#define PRTIM0 (1<<2)
#define PRUSI (1<<1)
#define PRADC (1<<0)

#define EEARH IO_REG(0x1F) /* reference page 20 */

#define EEAR8 (1<<0)

#define EEARL IO_REG(0x1E) /* reference page 21 */

#define EEAR7 (1<<7)
#define EEAR6 (1<<6)
#define EEAR5 (1<<5)
#define EEAR4 (1<<4)
#define EEAR3 (1<<3)
#define EEAR2 (1<<2)
#define EEAR1 (1<<1)
#define EEAR0 (1<<0)

#define EEDR IO_REG(0x1D) /* reference page 21 */


#define EECR IO_REG(0x1C) /* reference page 21 */

#define EEPM1 (1<<5)
#define EEPM0 (1<<4)
#define EERIE (1<<3)
#define EEMPE (1<<2)
#define EEPE (1<<1)
#define EERE (1<<0)

#define PORTB IO_REG(0x18) /* reference page 64 */

#define PORTB5 (1<<5)
#define PORTB4 (1<<4)
#define PORTB3 (1<<3)
#define PORTB2 (1<<2)
#define PORTB1 (1<<1)
#define PORTB0 (1<<0)

#define DDRB IO_REG(0x17) /* reference page 64 */

#define DDB5 (1<<5)
#define DDB4 (1<<4)
#define DDB3 (1<<3)
#define DDB2 (1<<2)
#define DDB1 (1<<1)
#define DDB0 (1<<0)

#define PINB IO_REG(0x16) /* reference page 64 */

#define PINB5 (1<<5)
#define PINB4 (1<<4)
#define PINB3 (1<<3)
#define PINB2 (1<<2)
#define PINB1 (1<<1)
#define PINB0 (1<<0)

#define PCMSK IO_REG(0x15) /* reference page 52 */

#define PCINT5 (1<<5)
#define PCINT4 (1<<4)
#define PCINT3 (1<<3)
#define PCINT2 (1<<2)
#define PCINT1 (1<<1)
#define PCINT0 (1<<0)

#define DIDR0 IO_REG(0x14) /* reference page 138 */

#define ADC0D (1<<5)
#define ADC2D (1<<4)
#define ADC3D (1<<3)
#define ADC1D (1<<2)
#define AIN1D (1<<1)
#define AIN0D (1<<0)

#define GPIOR2 IO_REG(0x13) /* reference page 10 */


#define GPIOR1 IO_REG(0x12) /* reference page 10 */


#define GPIOR0 IO_REG(0x11) /* reference page 10 */


#define USIBR IO_REG(0x10) /* reference page 115 */


#define USIDR IO_REG(0x0F) /* reference page 115 */


#define USISR IO_REG(0x0E) /* reference page 115 */

#define USISIF (1<<7)
#define USIOIF (1<<6)
#define USIPF (1<<5)
#define USIDC (1<<4)
#define USICNT3 (1<<3)
#define USICNT2 (1<<2)
#define USICNT1 (1<<1)
#define USICNT0 (1<<0)

#define USICR IO_REG(0x0D) /* reference page 116 */

#define USISIE (1<<7)
#define USIOIE (1<<6)
#define USIWM1 (1<<5)
#define USIWM0 (1<<4)
#define USICS1 (1<<3)
#define USICS0 (1<<2)
#define USICLK (1<<1)
#define USITC (1<<0)

#define ACSR IO_REG(0x08) /* reference page 120 */

#define ACD (1<<7)
#define ACBG (1<<6)
#define ACO (1<<5)
#define ACI (1<<4)
#define ACIE (1<<3)
#define ACIS1 (1<<1)
#define ACIS0 (1<<0)

#define ADMUX IO_REG(0x07) /* reference page 134 */

#define REFS1 (1<<7)
#define REFS0 (1<<6)
#define ADLAR (1<<5)
#define REFS2 (1<<4)
#define MUX3 (1<<3)
#define MUX2 (1<<2)
#define MUX1 (1<<1)
#define MUX0 (1<<0)

#define ADCSRA IO_REG(0x06) /* reference page 136 */

#define ADEN (1<<7)
#define ADSC (1<<6)
#define ADATE (1<<5)
#define ADIF (1<<4)
#define ADIE (1<<3)
#define ADPS2 (1<<2)
#define ADPS1 (1<<1)
#define ADPS0 (1<<0)

#define ADCH IO_REG(0x05) /* reference page 137 */


#define ADCL IO_REG(0x04) /* reference page 137 */


#define ADCSRB IO_REG(0x03) /* reference page 137 */

#define BIN (1<<7)
#define ACME (1<<6)
#define IPR (1<<5)
#define ADTS2 (1<<2)
#define ADTS1 (1<<1)
#define ADTS0 (1<<0)

/* interrupts */

#define IO_VEC(N) __vector_ ## N

#define RESET_INT IO_VEC(1)
#define INT0_INT IO_VEC(2)
#define PCINT0_INT IO_VEC(3)
#define TIM0_OVF_INT IO_VEC(6) 
#define EE_RDY_INT IO_VEC(7)
#define ANA_COMP_INT IO_VEC(8)
#define ADC_INT IO_VEC(9)
#define TIM0_COMPA_INT IO_VEC(11)
#define TIM0_COMPB_INT IO_VEC(12)
#define WDT_INT IO_VEC(13)
#define USI_START_INT IO_VEC(14)
#define USI_OVF_INT IO_VEC(15)

#endif/*_T85_H_*/
