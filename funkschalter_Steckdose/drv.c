/*
 * drv.c
 *
 * Created: 10.01.2023 19:45:38
 *  Author: Microbert
 */ 
#ifndef	F_CPU
#define F_CPU	8000000UL
#endif

#include <util/delay.h>
#include <avr/interrupt.h>

#include "drv.h"

void Drv_SleepEnable()
{
	MCUCR |= (1 << SE); /* powerdown mode | Sleep Enable */
}

void Drv_SleepDisable()
{
	MCUCR &= ~(1 << SE); /* Sleep Disable */
}


void Drv_InterruptsEnable()
{
	sei();
}

void Drv_InterruptsDisable()
{
	cli();
}

void Drv_SendPulse(uint16_t t_high, uint16_t t_low)
{
	setHigh(PORTB, TX_DATA);
	Drv_Delay_us(t_high*2);
	setLow(PORTB, TX_DATA);
	Drv_Delay_us(t_low*2);
}

void Drv_InitPCINT()
{
	ADCSRA &= ~(1 << ADEN);	//turn off ADC
	GIMSK |= (1 << PCIE); //PCINT creates interrupt
	PCMSK |= (1 << PCINT1) | (1 << PCINT2);
}

void Drv_InitGPIOs()
{
	setOutput(DDRB, TX_DATA);
	setOutput(DDRB, TX_POWER_PIN);
	setHigh(PORTB, OFF_BTN_PIN);
	setHigh(PORTB, ON_BTN_PIN);
}

uint8_t Drv_GetInputsPINB()
{	
	uint8_t result = PINB;	/* only read in pins 3 to 1 */
	result = result & 0x0E;	/* invert the results because of Pull-Up resistors (inverted logic) */
	return result;
}

void Drv_SetOutputPORTB(uint8_t pin)
{
	setHigh(PORTB,pin);
}

void Drv_ClearOutputPORTB(uint8_t pin)
{
	setLow(PORTB,pin);
}

