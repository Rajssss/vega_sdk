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
#include "encoding.h"

/*  Define section
* 
*
***************************************************/
#if __riscv_xlen == 64
#define UART_0_IRQ		1
#define UART_1_IRQ		2
#define UART_2_IRQ		3
#define SPI_0_IRQ		6
#define SPI_1_IRQ		7
#define I2C_0_IRQ		8
#define I2C_1_IRQ		9
#define TIMER_0_IRQ		10
#define TIMER_1_IRQ		11
#define TIMER_2_IRQ		12
#else
#define UART_0_IRQ		0
#define UART_1_IRQ		1
#define UART_2_IRQ		2
#define SPI_0_IRQ		3
#define SPI_1_IRQ		4
#define I2C_0_IRQ		5
#define I2C_1_IRQ		6
#define TIMER_0_IRQ		7
#define TIMER_1_IRQ		8
#define TIMER_2_IRQ		9
#endif


typedef void (*fp)(void); //Declares a type of a void function that accepts an void

typedef struct interrupt_reg
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
}INTR_REG;

#define intr_regs (*((volatile INTR_REG *)0x20010000))
/*  Function declaration section
* 
*
***************************************************/
void enable_irq(void);
void interrupt_enable(UC intr_number);
void irq_register_handler(UC irq_no, void (*irq_handler)());
//void interrupt_handler(void);
void interrupt_handler(uintptr_t cause, uintptr_t epc, uintptr_t regs[32]);
#endif	/* _INTERRUPT_H */	



