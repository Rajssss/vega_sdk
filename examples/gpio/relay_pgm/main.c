

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

#define HIGH 1
#define LOW  0

void main()
{
	printf("+--------[ Relay Demo ]-------+\n");
	printf("|                             |\n");
	printf("|       GPIO0 --->  Input     |\n");
	printf("|                             |\n");
	printf("+-----------------------------+\n\n");

	char mode = 0xff;
	while (1)
	{
			if (mode)
			{
				printf("\r Relay ON  [ .--. ]");
				GPIO_write_pin(0,HIGH);
			}
			else
			{
				printf("\r Relay OFF [ ./ . ]");
				GPIO_write_pin(0,LOW);
			}
		udelay(400000);
		mode = ~(mode);
	}
}
