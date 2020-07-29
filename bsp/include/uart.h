
#ifndef __UART_H
#define __UART_H

/***************************************************
* File Name			: uart.h
* Project Code		: HDG 083
* Project Mnemonic	: Microprocessor Development Programme
* Product Name		: Dhruv64
* Module Name		: UART Firmware
* Description		: UART Routines
* Author		: Sreenadh S., Senior Engineer
* Revision History & 
* Date			: First written on 04/08
* 				: Modified on 7/19
* Modified by whom &
* Reasons   		: Karthika P , M Tech Intern
***************************************************/

/*  Include section
*
*
***************************************************/

//#include "registers.h"


/*  Defines section
*
*
***************************************************/

typedef unsigned char UC; //1 Byte
typedef unsigned short US; //2 Bytes
typedef unsigned int UI; //4 Bytes
typedef unsigned long UL; //8 Bytes


typedef struct
{
	UI UART_DR;
	UI UART_IE;
	UI UART_IIR_FCR;
	UI UART_LCR;
	UI Dummy;
	UI UART_LSR;
}UART_REG_TYPE;

#define UART_NO_ERROR 0
#define UART_PARITY_ERROR -1
#define UART_OVERRUN_ERROR -2
#define UART_FRAMING_ERROR -3

//Register address mapping

#define UartReg(i) (*((volatile UART_REG_TYPE *)(UART_BASE+ (0x100 * i))))
/*  Function declaration section
*
***************************************************/

void uart_init(UC uart_number);
void uart_configure(UC uart_number, UL Baud_rate, UL frame_value, UL Uart_clock);
void uart_putchar(UC uart_number, UC bTxCharacter, char *error);
UC uart_getchar(UC uart_number, char *error);
void uart_intr_enable(UC uart_number, UC tx_intr, UC rx_intr);

#endif /*__UART_H*/


