

/***************************************************
* Module name: main.c
*
* Copyright 2020 Company CDAC(T)
* All Rights Reserved.
*
*  The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
*
*
* Module Description:
* SPI test pgm
*
***************************************************/

/*  Include section
*
*
***************************************************/

#include "stdlib.h"
#include "config.h"
#include "gpio.h"
#include "uart.h"


/** @fn main
 * @brief Lit all leds based on the switch status.
 * @details In this pgm the GPIO_0 pins from 1 to 7 are configured as OUTPUT and assumes that LEDs are connected in those pins.
	    And the pins 8 to 15 are configured as as INPUT and assumes that switches are connected there. 
	    This pgm continuosly reads the status of switches and either lits or turns off leds based on the value read from switch.
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main ()
{
	UC uart_error;
	US pin_val = 0;
	US pin_data0 = 0, pin_data1 = 0, pin_data2 = 0,pin_data3 = 0;
	UC repeat = 0,rx = 0;
	
	while(1)
	{
		printf("\n\r GPIO TEST PGM");
		printf("\n\r *************");

		printf("\n\r SW2(MSB)      SW1       SW0(LSB)        LED");

		printf("\n\r   0            0         0              ALL LEDs OFF   ");
		printf("\n\r   0            0         1              LD0 (RED)   ");
		printf("\n\r   0            1         0              LD0 (GREEN)   ");
		printf("\n\r   0            1         1              LD0 (BLUE)   ");

		printf("\n\r   1            0         0              LD1 (RED)   ");
		printf("\n\r   1            0         1              LD1 (GREEN)   ");
		printf("\n\r   1            1         0              LD1 (BLUE)   ");
		printf("\n\r   1            1         1              LD16,17,18 are ON  ");




		printf("\n\r Use Slide Switches SW2(MSB), SW1, SW0(LSB)");
		printf("\n\r Press any key to Start");
		rx = uart_getchar(0, &uart_error);

		while(!repeat)
		{

			pin_data0 = GPIO_read_pin(29); //SW0 LSB
			pin_data1 = GPIO_read_pin(30); //SW1
			pin_data2 = GPIO_read_pin(31); //SW2 MSB

			printf("\n\r SW 2 : ");
			if(pin_data2 == 1)
				printf("\n\r HIGH");
			else if(pin_data2 == 0)
				printf("\n\r LOW");

			printf("\n\r SW 1  : ");
			if(pin_data1 == 1)
				printf("\n\r HIGH");
			else if(pin_data1 == 0)
				printf("\n\r LOW");

			printf("\n\r SW 0  : ");
			if(pin_data0 == 1)
				printf("\n\r HIGH");
			else if(pin_data0 == 0)
				printf("\n\r LOW");


			if((pin_data2 == 0) && (pin_data1 == 0) && (pin_data0 == 0))
			{
				printf("\n\r SW2 : 0, SW1 : 0  SW0 : 0");
				GPIO_write_pin(19,OFF_LED);
				GPIO_write_pin(20,OFF_LED);
				GPIO_write_pin(21,OFF_LED);

				GPIO_write_pin(22,OFF_LED);
				GPIO_write_pin(23,OFF_LED);
				GPIO_write_pin(24,OFF_LED);

				GPIO_write_pin(16,OFF_LED);
				GPIO_write_pin(17,OFF_LED);
				GPIO_write_pin(18,OFF_LED);
				//printf("\n\r Press any key");
				//rx = uart_getchar(0, &uart_error);
			}
			if((pin_data2 == 0) && (pin_data1 == 0) && (pin_data0 == 1))
			{
				printf("\n\r SW2 : 0, SW1 : 0  SW0 : 1 ");
				GPIO_write_pin(19,ON_LED);
				GPIO_write_pin(20,OFF_LED);
				GPIO_write_pin(21,OFF_LED);

				GPIO_write_pin(22,OFF_LED);
				GPIO_write_pin(23,OFF_LED);
				GPIO_write_pin(24,OFF_LED);

				GPIO_write_pin(16,OFF_LED);
				GPIO_write_pin(17,OFF_LED);
				GPIO_write_pin(18,OFF_LED);

				//printf("\n\r Press any key");
				//rx = uart_getchar(0, &uart_error);
			}

			if((pin_data2 == 0) && (pin_data1 == 1) && (pin_data0 == 0))
			{
				printf("\n\r SW2 : 0, SW1 : 1  SW0 : 0 ");
				GPIO_write_pin(19,OFF_LED);
				GPIO_write_pin(20,ON_LED);
				GPIO_write_pin(21,OFF_LED);

				GPIO_write_pin(22,OFF_LED);
				GPIO_write_pin(23,OFF_LED);
				GPIO_write_pin(24,OFF_LED);

				GPIO_write_pin(16,OFF_LED);
				GPIO_write_pin(17,OFF_LED);
				GPIO_write_pin(18,OFF_LED);

				//printf("\n\r Press any key");
				//rx = uart_getchar(0, &uart_error);
			}
			if((pin_data2 == 0) && (pin_data1 == 1) && (pin_data0 == 1))
			{

				printf("\n\r SW2 : 0, SW1 : 1  SW0 : 1 ");
				GPIO_write_pin(19,OFF_LED);
				GPIO_write_pin(20,OFF_LED);
				GPIO_write_pin(21,ON_LED);

				GPIO_write_pin(22,OFF_LED);
				GPIO_write_pin(23,OFF_LED);
				GPIO_write_pin(24,OFF_LED);

				GPIO_write_pin(16,OFF_LED);
				GPIO_write_pin(17,OFF_LED);
				GPIO_write_pin(18,OFF_LED);

				//printf("\n\r Press any key");
				//rx = uart_getchar(0, &uart_error);
			}
			if((pin_data2 == 1) && (pin_data1 == 0) && (pin_data0 == 0))
			{
				printf("\n\r SW2 : 1, SW1 : 0  SW0 : 0 ");
				GPIO_write_pin(19,OFF_LED);
				GPIO_write_pin(20,OFF_LED);
				GPIO_write_pin(21,OFF_LED);

				GPIO_write_pin(22,ON_LED);
				GPIO_write_pin(23,OFF_LED);
				GPIO_write_pin(24,OFF_LED);

				GPIO_write_pin(16,OFF_LED);
				GPIO_write_pin(17,OFF_LED);
				GPIO_write_pin(18,OFF_LED);

				//printf("\n\r Press any key");
				//rx = uart_getchar(0, &uart_error);
			}

			if((pin_data2 == 1) && (pin_data1 == 0) && (pin_data0 == 1))
			{
				printf("\n\r SW2 : 1, SW1 : 0  SW0 : 1 ");
				GPIO_write_pin(19,OFF_LED);
				GPIO_write_pin(20,OFF_LED);
				GPIO_write_pin(21,OFF_LED);

				GPIO_write_pin(22,OFF_LED);
				GPIO_write_pin(23,ON_LED);
				GPIO_write_pin(24,OFF_LED);

				GPIO_write_pin(16,OFF_LED);
				GPIO_write_pin(17,OFF_LED);
				GPIO_write_pin(18,OFF_LED);

				//printf("\n\r Press any key");
				//rx = uart_getchar(0, &uart_error);
			}
			if((pin_data2 == 1) && (pin_data1 == 1) && (pin_data0 == 0))
			{
				printf("\n\r SW2 : 1, SW1 : 1  SW0 : 0 ");
				GPIO_write_pin(19,OFF_LED);
				GPIO_write_pin(20,OFF_LED);
				GPIO_write_pin(21,OFF_LED);

				GPIO_write_pin(22,OFF_LED);
				GPIO_write_pin(23,OFF_LED);
				GPIO_write_pin(24,ON_LED);

				GPIO_write_pin(16,OFF_LED);
				GPIO_write_pin(17,OFF_LED);
				GPIO_write_pin(18,OFF_LED);

				//printf("\n\r Press any key");
				//rx = uart_getchar(0, &uart_error);
			}
			if((pin_data2 == 1) && (pin_data1 == 1) && (pin_data0 == 1))
			{
				printf("\n\r SW2 : 1, SW1 : 1  SW0 : 1 ");
				GPIO_write_pin(19,OFF_LED);
				GPIO_write_pin(20,OFF_LED);
				GPIO_write_pin(21,OFF_LED);

				GPIO_write_pin(22,OFF_LED);
				GPIO_write_pin(23,OFF_LED);
				GPIO_write_pin(24,OFF_LED);

				GPIO_write_pin(16,ON_LED);
				GPIO_write_pin(17,ON_LED);
				GPIO_write_pin(18,ON_LED);
				repeat = 1;
				//printf("\n\r Press any key");
				//rx = uart_getchar(0, &uart_error);
			}
		}
	}
	
}




