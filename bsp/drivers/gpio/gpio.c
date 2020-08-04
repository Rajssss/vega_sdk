/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  gpio.c
 * Brief Description of file             :  Driver to control the GPIO.
 * Name of Author                        :  Sreeju G R
 * Email ID                              :  sreeju@cdac.in

  Copyright (C) 2020  CDAC(T). All rights reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.

***************************************************************************/

#include <include/stdlib.h>
#include <include/gpio.h>
#include <include/config.h>	//for datatypes


/** @fn GPIO_read_pin
 * @brief  Read GPIO pin value.
 * @details Read the GPIO pin value by setting the direction as INPUT.
 * @warning 
 * @param[in] unsigned char, unsigned short
 * @param[Out] Pin value as 16 bit data.
*/
US GPIO_read_pin(UC gpio_number,US pin_no) {

	US dir_data = 0;
	volatile US *gpio_0_dir_addr = (volatile US *)(GPIO_0_BASE_ADDRESS +0x40000) ;
	volatile US *gpio_1_dir_addr = (volatile US *)(GPIO_1_BASE_ADDRESS +0x40000) ;

	UL gen_gpio_0_addr,gen_gpio_1_addr;
	volatile US *gpio_0_data, *gpio_1_data;
	US read_data = 0;

	if(gpio_number == 0)
	{
		
		dir_data =  *gpio_0_dir_addr; 		// Address of the direction register.
		dir_data &= ~(pin_no);			//Clearing a bit configures the pin to be INPUT
		*gpio_0_dir_addr = dir_data;		// Data written to direction register.

		gen_gpio_0_addr = GPIO_0_BASE_ADDRESS;
		gen_gpio_0_addr+=(pin_no << 2);
		gpio_0_data = (US *)gen_gpio_0_addr;
		read_data = *gpio_0_data; 			// Read data from the address.
	}
	else if(gpio_number == 1)
	{
		
		dir_data =  *gpio_1_dir_addr;				// Address of the direction register.
		dir_data &= ~(pin_no);	
		*gpio_1_dir_addr = dir_data;					// Data written to direction register.


		gen_gpio_1_addr = GPIO_1_BASE_ADDRESS;
		gen_gpio_1_addr+=(pin_no << 2);
		gpio_1_data = (US *)gen_gpio_1_addr;
		read_data = *gpio_1_data;				// Read data from the address.
	}
	__asm__ __volatile__ ("fence");

	return (read_data & pin_no) ;   
}

/** @fn GPIO_write_pin
 * @brief  Write GPIO pin value.
 * @details Write the GPIO pin value by setting the direction as OUTPUT.
 * @warning 
 * @param[in] unsigned char, unsigned short, unsigned short
 * @param[Out] No output parameter.
*/
void GPIO_write_pin(UC gpio_number,US pin_no,US data) {

	US dir_data = 0;
	volatile US *gpio_0_dir_addr = (volatile US *)(GPIO_0_BASE_ADDRESS +0x40000) ;
	volatile US *gpio_1_dir_addr = (volatile US *)(GPIO_1_BASE_ADDRESS +0x40000) ;

	UL gen_gpio_0_addr,gen_gpio_1_addr;
	volatile US *gpio_0_data, *gpio_1_data;


	if(gpio_number == 0)
	{
		
		dir_data =  *gpio_0_dir_addr;	 		// Address of the direction register.
		dir_data |= pin_no;				//Setting a bit configures the pin to be OUTPUT
		*gpio_0_dir_addr = dir_data;			// Data written to direction register.

		gen_gpio_0_addr = GPIO_0_BASE_ADDRESS;
		gen_gpio_0_addr|=(pin_no << 2);
		gpio_0_data = (US *)gen_gpio_0_addr;
		*gpio_0_data = data;			// Write data to the address.
	}
	else if(gpio_number == 1)
	{
		
		dir_data =  *gpio_1_dir_addr;				// Address of the direction register.
		dir_data |= pin_no;									//Setting a bit configures the pin to be OUTPUT
		*gpio_1_dir_addr = dir_data;					// Data written to direction register.

		gen_gpio_1_addr = GPIO_1_BASE_ADDRESS;
		gen_gpio_1_addr|=(pin_no << 2);
		gpio_1_data = (US *)gen_gpio_1_addr;
		*gpio_1_data = data;			// Write data to the address.


	}
	__asm__ __volatile__ ("fence");

	return;   
}


