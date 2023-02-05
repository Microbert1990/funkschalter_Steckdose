/*
 * hal.c
 *
 * Created: 10.01.2023 19:47:00
 *  Author: Microbert
 */ 

#include "hal.h"
#include "hwcfg.h"
#include "hwspec.h"
#include "global.h"
#include "eeprom_memory.h"

void Hal_SendData(uint32_t data, uint8_t length)
{
	uint8_t len = length;
	
	if(len > 0) {
		
		while(len--) {
			if((data >> len) & 1) {
				Hwspec_SendPulse(900, 350);
			} 
			else {
				Hwspec_SendPulse(300, 950);
			}
		}
	}
}

uint8_t Hal_GetInput()
{
	uint8_t result = 0;
	
	switch(Hwspec_GetInputsPINB()) {
		case 2:	
			result = SWITCH_OFF;
			break;
		case 4: 
			result = SWITCH_ON; 
			break;
		case 8:
			result = REC_CMD;
			break;
		default:
			break;
	}
	return result;
}

void Hal_RCTransceiverOn()
{
	Hwspec_SetOutputPORTB(TX_POWER_PIN);
}

void Hal_RCTransceiverOff()
{
	Hwspec_ClearOutputPORTB(TX_POWER_PIN);
}

void Hal_SetInterrupts(uint8_t value)
{
	value ? Hwspec_InterruptsEnable() : Hwspec_InterruptsDisable();
}

void Hal_Powerdown()
{
	SLEEP;
}

void Hal_InitCmds()
{
	On_Cmd.mem_addr = ON_CMD_EEP_ADDR;
	Off_Cmd.mem_addr = OFF_CMD_EPP_ADDR;
	
	EEP_LoadCommand(&On_Cmd);
	EEP_LoadCommand(&Off_Cmd);
	
}

int ISR(PCINT0_vect)
{
	Hwspec_SleepDisable();
	return 0;
}