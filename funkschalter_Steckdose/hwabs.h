/*
 * hwabs.h
 *
 * Created: 10.01.2023 19:47:13
 *  Author: Microbert
 */ 


#ifndef HWABS_H_
#define HWABS_H_

#include <avr/io.h>

void Hwabs_SendData(uint32_t data, uint8_t length);
uint8_t Hwabs_GetInput();
void Hwabs_RCTransmitterOn();
void Hwabs_RCTransmitterOff();

void Hwabs_SetInterrupts(uint8_t value);
void Hwabs_Powerdown();

#endif /* HWABS_H_ */