/***************************************************


 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 08-Jul-2020
 Filename		: i2c_scanner.c
 Purpose		: I2C scanner program
 Description		: i2c_scanner program to detect connected I2C device address
 Author(s)		: Premjith A V
 Email			: premjith@cdac.in

 See LICENSE for license details.
 ***************************************************/

/**
 @file i2c_scanner.c
 @brief contains routines for I2C scanner
 @detail Includes software functions declarations to initialize,

 */

#include "i2c.h"
#include "stdlib.h"

/**
 @fn main
 @brief writes and reads scanner with I2C interface
 @details Initializes configures I2C to write, read and compare data in scanner
 @param[in] No input parameters.
 @param[Out] No ouput parameter.
 @return Void function.

 */



void main() {

	printf("I2C Scanner\n\r");
	
	printf("Scanning ...\n\r");	

	for(UC address = 1; address < 127; address++ )
  	{
		i2c_start(I2C_0, 0x00, 0);
		int error = i2c_data_write(I2C_0, &address, 01);
		if(error==0)
		{ //writes slave address and set EEPROM to write mode
			printf("I2C Device found at address : %02x !\r\n",address);			
		}
		i2c_stop(I2C_0);

	}
	
	
	while (1)
		;
}

