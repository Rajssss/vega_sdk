

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
#include "timer.h"


/** @fn main
 * @brief Generate a delay in polling mode.
 * @details In this pgm the timers0,timers1 & timers2 are loaded with values and waits for interrupt in polling mode.
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main ()
{
	UC intr = 0;

	while(1)
	{
		intr = timer_put_delay(TIMER_0,0x200);			
		printf("\n TIMER 0 intr occurred");
			
		intr = timer_put_delay(TIMER_1,0x350);
		printf("\n TIMER 1 intr occurred");
	
		intr = timer_put_delay(TIMER_2,0x500);	
		printf("\n TIMER 2 intr occurred");			
	}
	
}




