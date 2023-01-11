/*
 * hwcfg.c
 *
 * Created: 10.01.2023 19:49:46
 *  Author: Microbert
 */ 
#include "hwcfg.h"
#include "drv.h"

void Hwcfg_Init()
{	
	Drv_InitGPIOs();
	Drv_InitPCINT();
}