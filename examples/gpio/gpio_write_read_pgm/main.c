

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
	US pin_val = 0;

	while(1)
	{
		pin_val = GPIO_read_pin(GPIO_0,PIN_8); // Set 8th pin as input and read its value
		if(pin_val == 0x0100)
			GPIO_write_pin(GPIO_0,PIN_0,0x1); // Lit LED at bit 0.
		else
			GPIO_write_pin(GPIO_0,PIN_0,0x0); // Turn Off LED at bit 0.



		pin_val = GPIO_read_pin(GPIO_0,PIN_9); // Set 9th pin as input and read its value
		if(pin_val)
			GPIO_write_pin(GPIO_0,PIN_1,0x2); // Lit LED at bit 1.
		else
			GPIO_write_pin(GPIO_0,PIN_1,0x0); // Turn Off LED at bit 1.


		pin_val = GPIO_read_pin(GPIO_0,PIN_10); // Set 10th pin as input and read its value
		if(pin_val)
			GPIO_write_pin(GPIO_0,PIN_2,0x4); // Lit LED at bit 2
		else
			GPIO_write_pin(GPIO_0,PIN_2,0x0); // Turn Off LED at bit 2.



		pin_val = GPIO_read_pin(GPIO_0,PIN_11); // Set 11th pin as input and read its value
		if(pin_val)
			GPIO_write_pin(GPIO_0,PIN_3,0x8); // Lit LED at bit 3.
		else
			GPIO_write_pin(GPIO_0,PIN_3,0x0); // Turn Off LED at bit 3.


		pin_val = GPIO_read_pin(GPIO_0,PIN_12); // Set 12th pin as input and read its value
		if(pin_val)
			GPIO_write_pin(GPIO_0,PIN_4,0x10); // Lit LED at bit 4.
		else
			GPIO_write_pin(GPIO_0,PIN_4,0x0); // Turn Off LED at bit 4.



		pin_val = GPIO_read_pin(GPIO_0,PIN_13); // Set 13th pin as input and read its value
		if(pin_val)
			GPIO_write_pin(GPIO_0,PIN_5,0x20); // Lit LED at bit 5.
		else
			GPIO_write_pin(GPIO_0,PIN_5,0x0); // Turn Off LED at bit 5.



		pin_val = GPIO_read_pin(GPIO_0,PIN_14); // Set 14th pin as input and read its value
		if(pin_val)
			GPIO_write_pin(GPIO_0,PIN_6,0x40); // Lit LED at bit 6.
		else
			GPIO_write_pin(GPIO_0,PIN_6,0x0); // Turn Off LED at bit 6.



		pin_val = GPIO_read_pin(GPIO_0,PIN_15); // Set 15th pin as input and read its value
		if(pin_val)
			GPIO_write_pin(GPIO_0,PIN_7,0x80); // Lit LED at bit 7.
		else
			GPIO_write_pin(GPIO_0,PIN_7,0x0); // Turn Off LED at bit 7.
	}
	
}




