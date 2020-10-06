

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

void main()
{
	printf("+-----[ LDR Sensor Demo ]-----+\n");
	printf("|                             |\n");
	printf("|    sensor DO ---> GPIO0     |\n");
	printf("|                             |\n");
	printf("+-----------------------------+\n\n");

	char LDR_Status;
	char prevStatus = 0xff;
	while (1)
	{
		LDR_Status = GPIO_read_pin(0);
		if (prevStatus != LDR_Status)
		{
			prevStatus = LDR_Status; // Saving state.
			if (LDR_Status)
			{
				printf("\rLight Status : Absent  ( )");
			}
			else
			{
				printf("\rLight Status : Present (*)");
			}
		}
	}
}
