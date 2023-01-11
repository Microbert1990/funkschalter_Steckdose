/*
 * hwabs.c
 *
 * Created: 10.01.2023 19:47:00
 *  Author: Microbert
 */ 

#include "hwabs.h"
#include "hwcfg.h"
#include "drv.h"

void Hwabs_SendData(uint32_t data, uint8_t length)
{
	uint8_t len = length;
	
	if(len > 0) {
		
		while(len--) {
			if((data >> len) & 1) {
				Drv_SendPulse(900, 350);
			} 
			else {
				Drv_SendPulse(300, 950);
			}
		}
	}
}

uint8_t Hwabs_GetInput()
{
	uint8_t result = 0;
	
	switch(Drv_GetInputsPINB()) {
		case 2:	
			result = OFF_BTN_PIN;
			break;
		case 4: 
			result = ON_BTN_PIN; 
			break;
		case 8:
			result = RX_DATA;
			break;
		case 6:
			result = 5;
			break;
		default:
			break;
	}
	return result;
}

void Hwabs_RCTransmitterOn()
{
	Drv_SetOutputPORTB(TX_POWER_PIN);
}

void Hwabs_RCTransmitterOff()
{
	Drv_ClearOutputPORTB(TX_POWER_PIN);
}

void Hwabs_SetInterrupts(uint8_t value)
{
	value ? Drv_InterruptsEnable() : Drv_InterruptsDisable();
}

void Hwabs_Powerdown()
{
	SLEEP;
}

int ISR(PCINT0_vect)
{
	Drv_SleepDisable();
	return 0;
}