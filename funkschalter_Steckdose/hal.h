/*
 * hwabs.h
 *
 * Created: 10.01.2023 19:47:13
 *  Author: Microbert
 */ 


#ifndef HAL_H_
#define HAL_H_

#include <avr/io.h>

#define SWITCH_OFF	1
#define SWITCH_ON	2
#define REC_CMD		3

void Hal_SendData(uint32_t data, uint8_t length);
uint8_t Hal_GetInput();
void Hal_RCTransceiverOn();
void Hal_RCTransceiverOff();

void Hal_SetInterrupts(uint8_t value);
void Hal_Powerdown();

void Hal_InitCmds();

#endif /* HAL_H_ */