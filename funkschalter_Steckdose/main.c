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

#include "global.h"
#include "hwcfg.h"
#include "hal.h"
#include "hwspec.h"
#include "rc.h"
#include "eeprom_memory.h"

void send_byte(uint32_t);
void init_PCINT();

typedef enum STATES{
	INIT,
	IDLE,
	RECORDING,
	PROCESSING,
	SENDING,
	POWERDOWN
} State_t; 

State_t State;

// TODO: Set up State Machine
// TODO: Recording of new Signals with Receiver
int main(void)
{	
	uint8_t inputs = 0;
	switch(State)
	{
		case INIT:
			Hwcfg_Init();	/* Init hardware */
			State = IDLE;
			break;
		
		case IDLE:
			inputs = Hal_GetInput();	/* get button states */
			if(!inputs) {
				break;
			} else if(inputs == REC_CMD) {	/* both buttons pressed */
				State = RECORDING;
				break;
			} else {
				State = SENDING;
			break;
			}
		case RECORDING:
			Hal_RCTransceiverOn();
			break;
			
		case PROCESSING:
			break;
			
		case SENDING:
			if(inputs == SWITCH_OFF)
				Rc_SendMsg(SWITCH_OFF);
			else
				Rc_SendMsg(SWITCH_ON);
			
			Hal_RCTransceiverOff();
			State = POWERDOWN;
			break;
			
		case POWERDOWN:
			Hal_SetInterrupts(true);
			Hal_Powerdown();
			Hal_SetInterrupts(false);
			State = IDLE;
			break;
		
		default:	
			break;
	}
}




