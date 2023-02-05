/*
 * hwcfg.c
 *
 * Created: 10.01.2023 19:49:46
 *  Author: Microbert
 */ 
#include "hwcfg.h"
#include "hwspec.h"

void Hwcfg_Init()
{	
	Hwspec_InitGPIOs();
	Hwspec_InitPCINT();
	Hal_InitCmds();
}