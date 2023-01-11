/*
 * funkschalter_Steckdose.c
 *
 * Created: 07.01.2023 00:39:50
 * Author : Microbert
 */ 

#ifndef	F_CPU
#define F_CPU	8000000UL
#endif


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "hwcfg.h"
#include "hwabs.h"
#include "drv.h"
#include "rc.h"

void send_byte(uint32_t);
void init_PCINT();

#define ON_CMD	0x01FDC990
#define OFF_CMD 0x01FDC988


// TODO: Set up State Machine
// TODO: Recording of new Signals with Receiver
int main(void)
{	
	Hwcfg_Init();
	while(1)
    {	
		if( Hwabs_GetInput() == 2){
			Hwabs_RCTransmitterOn();
			_delay_ms(20);
			Hwabs_SendData(ON_CMD, 25);
			_delay_ms(20);
			Hwabs_SendData(ON_CMD, 25);
			_delay_ms(20);
			Hwabs_SendData(ON_CMD, 25);
			_delay_ms(20);
		}
		else if( Hwabs_GetInput() == OFF_BTN_PIN) {
			Hwabs_RCTransmitterOn();
			_delay_ms(20);
			Hwabs_SendData(OFF_CMD, 25);
			_delay_ms(20);
			Hwabs_SendData(OFF_CMD, 25);
			_delay_ms(20);
			Hwabs_SendData(OFF_CMD, 25);
			_delay_ms(20);
		}
		
		Hwabs_RCTransmitterOff();
		
		Hwabs_SetInterrupts(true);
		Hwabs_Powerdown();
		Hwabs_SetInterrupts(false);
	}
}




