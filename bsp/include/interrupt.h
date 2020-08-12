#ifndef _INTERRUPT_H
#define _INTERRUPT_H

/***************************************************
* Module name: spi.h
*
* Copyright 2020 Company CDAC(T).
* All Rights Reserved.
*
*  The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
*
*
* Module Description:
* SPI registers and function declarations
*
***************************************************/

/*  Include section
*
***************************************************/

#include "config.h"
#include "stdlib.h"


/*  Define section
* 
*
***************************************************/
typedef void (*fp)(void); //Declares a type of a void function that accepts an void

typedef struct ext_intr_reg
{
#if __riscv_xlen == 64
	UL   RAW_INTR; 		//0x00
	UL   INTR_EN; 		//0x08
	UL   INTR_STATUS; 	//0x10
#else
	UI   RAW_INTR; 		//0x00
	UI   dummy0; 		//0x04
	UI   INTR_EN; 		//0x08
	UI   dummy1; 		//0x0c
	UI   INTR_STATUS; 	//0x10
#endif
}EXT_INTR_REG;

#define ext_intr_regs (*((volatile EXT_INTR_REG *)0x20010000))
/*  Function declaration section
* 
*
***************************************************/
void enable_irq(void);
void external_interrupt_enable(UC intr_number);
void initialize_external_interrupt_table(void);
void external_interrupt_handler(void);

#endif	/* _INTERRUPT_H */	



