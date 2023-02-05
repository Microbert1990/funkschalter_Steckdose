/*
 * eeprom_memory.h
 *
 * Created: 15.01.2023 12:50:59
 *  Author: Microbert
 */ 


#ifndef EEPROM_MEMORY_H_
#define EEPROM_MEMORY_H_

#include "global.h"

#define ON_CMD_EEP_ADDR 0x00
#define OFF_CMD_EPP_ADDR 0x20

void EEP_LoadCommand(RC_CMD_t *cmd);


#endif /* EEPROM_MEMORY_H_ */