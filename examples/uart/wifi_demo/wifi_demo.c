/***************************************************
 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 08-Nov-2019
 Filename		: uart_tx_rx.c
 Purpose		: UART interface
 Description		: transmission & reception with uart interface
 Author(s)		: Karthika P
 Email			: karthikap@cdac.in

 See LICENSE for license details.
 ***************************************************/
/**
 @file uart_tx_rx.c.c
 @brief Contains routines for UART interface
 @detail Includes software functions to initialize,
 configure, transmit and receive over UART
 */
/*  Include section
 ***************************************************/

#include "uart.h"
#include "stdlib.h"
#include "config.h"
#include "gpio.h"
#include <string.h>

/**
 @fn main
 @brief transmit and reception through uart
 @details 1 character is transmitted and received through uart
 @param[in] No input parameter.
 @param[Out] No ouput parameter.
 @return Void function.

 */
void main() {
	char error;       
	char str[100]={0,};
	unsigned char data='A';

	printf("Setting up Wifi Device 22\n\r");
	uart_set_baud_rate(UART_1,115200,40000000);

	while(1)
	{	
		//data = uart_getchar(UART_1, &error);	
		printf("+%c+\n", data);
	}	
	
}

