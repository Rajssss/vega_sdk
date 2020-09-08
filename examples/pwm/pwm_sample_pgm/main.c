

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
#include "pwmc.h"
#include "stdlib.h"
#include "config.h"
#include "debug_uart.h"


void pwmc_continuous_mode(UC channel_no,UC opc,UI period, UI on_offtime)
{
	UC rx = 0;
	PWMC_Set_Period(PWM_CH_0,period);
	PWMC_Set_OnOffTime(PWM_CH_0,on_offtime);
	PWMC_init(PWM_CH_0,PWM_CONTINUOUS_MODE,PWM_LEFT_ALIGN,PWM_LOC_INTR_DIS,opc,PWM_REPEAT_COUNT);

	PWMC_Enable();
}


/** @fn main
 * @brief Read all ADC channel values and display it via UART..
 * @details 
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main (void)
{
	UC rx = 0;
	UL selection;

	printf("\n\rSERVO MOTOR CONTROLLING ");
	printf("\n\r*********************** ");

	printf("\n\rConnect motor in CH0 ");

	while(1)
	{
		printf("\n\r01 .Turn by 0  degrees");
		printf("\n\r02 .Turn by 90 degrees");

		selection = get_decimal(2);
		switch (selection)
		{
			case 1:
				pwmc_continuous_mode(PWM_CH_0,PWM_OPC_LOW,800000,40000);
				break;

			case 2:
				pwmc_continuous_mode(PWM_CH_0,PWM_OPC_LOW,800000,60000);
				break;

			default:
				break;
		}
	}
}




