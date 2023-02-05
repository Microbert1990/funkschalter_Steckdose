/*
 * hwspec.c
 *
 * Created: 10.01.2023 19:45:38
 *  Author: Microbert
 */ 

#include <avr/interrupt.h>

#include "hwspec.h"

void Hwspec_SleepEnable()
{
	MCUCR |= (1 << SE); /* powerdown mode | Sleep Enable */
}

void Hwspec_SleepDisable()
{
	MCUCR &= ~(1 << SE); /* Sleep Disable */
}


void Hwspec_InterruptsEnable()
{
	sei();
}

void Hwspec_InterruptsDisable()
{
	cli();
}

void Hwspec_SendPulse(uint16_t t_high, uint16_t t_low)
{
	setHigh(PORTB, TX_DATA);
	Hwspec_Delay_us(t_high*2);
	setLow(PORTB, TX_DATA);
	Hwspec_Delay_us(t_low*2);
}

void Hwspec_InitPCINT()
{
	ADCSRA &= ~(1 << ADEN);	//turn off ADC
	GIMSK |= (1 << PCIE); //PCINT creates interrupt
	PCMSK |= (1 << PCINT1) | (1 << PCINT2);
}

void Hwspec_InitGPIOs()
{
	setOutput(DDRB, TX_DATA);
	setOutput(DDRB, TX_POWER_PIN);
	setHigh(PORTB, OFF_BTN_PIN);
	setHigh(PORTB, ON_BTN_PIN);
}

uint8_t Hwspec_GetInputsPINB()
{	
	uint8_t result = PINB;	/* only read in pins 3 to 1 */
	result = result & 0x0E;	/* invert the results because of Pull-Up resistors (inverted logic) */
	return result;
}

void Hwspec_SetOutputPORTB(uint8_t pin)
{
	setHigh(PORTB,pin);
}

void Hwspec_ClearOutputPORTB(uint8_t pin)
{
	setLow(PORTB,pin);
}

