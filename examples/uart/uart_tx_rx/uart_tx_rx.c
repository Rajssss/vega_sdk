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


/**
 @fn main
 @brief transmit and reception through uart
 @details 1 character is transmitted and received through uart
 @param[in] unsigned char(uart_number)
 @param[in] unsigned long(Baud_rate)
 @param[in] unsigned long(frame_value)
 @param[in] unsigned long(Uart_clock)
 @param[Out] No ouput parameter.
 @return Void function.

 */
void main() {
	char error;
	UC data;
	uart_configure(0, 9600, 83, 100000);

	uart_putchar(0, 't', &error);
	if (error) {
		switch (error) {
		case (char)UART_PARITY_ERROR:
			printf("Parity Error\n\r");
			break;
		case (char)UART_OVERRUN_ERROR:
			printf("Overrun Error\n\r");
			break;
		case (char)UART_FRAMING_ERROR:
			printf("Framing Error\n\r");
			break;
		}
	} else
		printf("no error\n\r");

	data = uart_getchar(0, &error);
	if (error) {
		switch (error) {
		case (char)UART_PARITY_ERROR:
			printf("Parity Error\n\r");
			break;
		case (char)UART_OVERRUN_ERROR:
			printf("Overrun Error\n\r");
			break;
		case (char)UART_FRAMING_ERROR:
			printf("Framing Error\n\r");
			break;
		}
	} else
		printf("no error\n\r");
}

