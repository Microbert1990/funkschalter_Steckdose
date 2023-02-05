/*
 * rc.c
 *
 * Created: 10.01.2023 19:51:37
 *  Author: Microbert
 */ 

#ifndef	F_CPU
#define F_CPU	8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "rc.h"

#include "global.h"
#include "hal.h"
#include "eeprom_memory.h"

void Rc_SendMsg(uint8_t cmd)
{
	
	Hal_RCTransceiverOn();
	_delay_ms(20);
	Hal_SendData(cmd, 25);
	_delay_ms(20);
	Hal_SendData(cmd, 25);
	_delay_ms(20);
	Hal_SendData(cmd, 25);
	_delay_ms(20);
}