

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
#include "led.h"
#include "gpio.h"


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
	US i,sw_status = 0;

	while(1)
	{
		//Turn ON LEDs 5, 6, 7 at GPIO pins 16,17,18 respectively.

		on_LED(PIN_16);
		on_LED(PIN_17);
		on_LED(PIN_18);

		for(i=0; i< 0xffff;i++); // Delay

		//Turn OFF LEDs 5, 6, 7 at GPIO pins 16,17,18 respectively.

		off_LED(PIN_16);
		off_LED(PIN_17);
		off_LED(PIN_18);

		for(i=0; i< 0xffff;i++); // Delay

		
	}
	
}




