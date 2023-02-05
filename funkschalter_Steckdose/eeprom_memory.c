/*
 * eeprom_memory.c
 *
 * Created: 15.01.2023 12:50:46
 *  Author: Microbert
 */ 

#include <avr/eeprom.h>
#include "eeprom_memory.h"

#include "global.h"

void EEP_LoadCommand(RC_CMD_t *Cmd)
{
	Cmd->cmd_length = eeprom_read_byte(Cmd->mem_addr);
	/* no command saved before */
	if(Cmd->cmd_length == 0) {
		Cmd->command = 0x00;
		Cmd->addr_length = 0x00;
		Cmd->cmd_length =0x00;
	}
	/* read command msg from eeprom as block of Cmd->addr_length bytes*/
	else {
		eeprom_read_block(Cmd->command, Cmd->mem_addr+1, Cmd->addr_length);
	}
}

void writeDataToEEPROM(uint8_t data, uint8_t address)
{
	eeprom_write_byte((uint8_t*)address, data);
}

uint8_t readDataFromEEPROM(uint8_t address)
{
	return eeprom_read_byte((const uint8_t*) address);
}