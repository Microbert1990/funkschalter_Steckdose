/*
 * drv.h
 *
 * Created: 10.01.2023 19:46:25
 *  Author: Microbert
 */ 


#ifndef DRV_H_
#define DRV_H_

#include <avr/io.h>

#define true 1
#define false 0

/* GPIOs */
#define TX_DATA			4		/* data pin of rc-transmitter */
#define RX_DATA			3		/* data pin of rc-receiver */
#define ON_BTN_PIN		2		/* 'on' button */
#define OFF_BTN_PIN		1		/* 'off' button  */
#define TX_POWER_PIN	0		/* controls power supply for rc-transmitter */

/* Pin manipulation functions */
#define setOutput(ddr, pin)	((ddr) |= (1 << (pin)))		/* setting data direction register bit for 'pin' to output */
#define setLow(port, pin)	((port) &= ~(1 << (pin)))	/* setting 'pin' low (deactivates pull-up resistor when pin is configured as input) */
#define setHigh(port, pin)	((port) |= (1 << (pin)))	/* setting 'pin' high (activates pull-up resistor when pin is configured as input) */
#define pulse(port, pin)	do { \
	setHigh((port), (pin)); \
	setLow((port), (pin)); \
	} while (0)											/* set 'pin' high and immediately set it low to create a short pulse */

#define SLEEP	__asm__ __volatile__ ("sleep")			/* sleep mode command is only accesseble via assembler command */

void Drv_SleepEnable();
void Drv_SleepDisable();
void Drv_InterruptsEnable();
void Drv_InterruptsDisable();

/* Warning! BLACK MAGIC */

static inline void __attribute__((always_inline)) Drv_Delay_us(uint16_t count)
{
	/* this loop takes 4 * count + 3 ticks */
	/* 1us equals 8 ticks at 8 MHz CPU-Clk */
	/* explanation at https://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/Assembler_und_Inline-Assembler */
	
	asm volatile (	"1:"           "\n\t"		
					"sbiw %0,1"    "\n\t"
					"brcc 1b"
					: "+w" (count));
};

void Drv_SendPulse(uint16_t t_high, uint16_t t_low);
void Drv_InitPCINT();
void Drv_InitGPIOs();

uint8_t Drv_GetInputsPINB();
void Drv_SetOutputPORTB(uint8_t pin);
void Drv_ClearOutputPORTB(uint8_t pin);

#endif /* DRV_H_ */