

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
#include "adc.h"
#include "stdlib.h"
#include "config.h"



/** @fn main
 * @brief Generate a delay in polling mode.
 * @details In this pgm the timers0,timers1 & timers2 are loaded with values and waits for interrupt in polling mode.
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main (void)
{
	UI adc_data = 0;
	while(1)
	{
				
		printf("\n Reading ADC Channel 1 data");
		adc_data = adc_analogRead(A0);
	
		printf("\n Reading ADC Channel 2 data");
		adc_data = adc_analogRead(A1);
	
		printf("\n Reading ADC Channel 3 data");
		adc_data = adc_analogRead(A2);
	
		printf("\n Reading ADC Channel 4 data");
		adc_data = adc_analogRead(A3);
	}
}




