/*
 * global.h
 *
 * Created: 15.01.2023 12:51:35
 *  Author: Microbert
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

typedef struct {
	uint8_t *command;
	uint8_t cmd_length;
	uint8_t mem_addr;
	uint8_t addr_length;
} RC_CMD_t;

RC_CMD_t On_Cmd;
RC_CMD_t Off_Cmd;


#endif /* GLOBAL_H_ */