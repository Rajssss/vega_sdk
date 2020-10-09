

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
#include "lcd.h"
#include "gpio.h"



/** @fn lcd_send_command
 * @brief Toggle leds LD5,LD6 & LD7.
 * @details Toggle LEDs at finite intervals.
 * @warning 
 * @param[in] UC cmd: Command to be written to LCD 
 * @param[Out] No output parameter 
*/
void lcd_init(void)
{
	GPIO_write_pin(3,LOW); 	// RS - Select Register.
	GPIO_write_pin(4,HIGH); // RW - Data read, Data write.
	GPIO_write_pin(5,LOW); 	// E - Enable Signal. (A start signal for reading or writing data.)

	GPIO_write_pin(6,LOW); 	// DB0 - LSB
	GPIO_write_pin(7,LOW); 	// DB1
	GPIO_write_pin(8,LOW); 	// DB2
	GPIO_write_pin(9,LOW); 	// DB3
	GPIO_write_pin(10,LOW); 	// DB4
	GPIO_write_pin(11,LOW); 	// DB5
	GPIO_write_pin(12,LOW); 	// DB6
	GPIO_write_pin(13,LOW); 	// DB7	- MSB
}



/** @fn lcd_send_command
 * @brief Toggle leds LD5,LD6 & LD7.
 * @details Toggle LEDs at finite intervals.
 * @warning 
 * @param[in] UC cmd: Command to be written to LCD 
 * @param[Out] No output parameter 
*/
void lcd_send_command(UC cmd)
{
	UI i =0;
	GPIO_write_pin(3,LOW); 	// RS - Select Register.
	GPIO_write_pin(4,LOW); 	// RW - Data read, Data write.

	GPIO_write_pin(5,HIGH); // E - Enable Signal. (A start signal for reading or writing data.)

	(cmd & 0x01)?GPIO_write_pin(6,HIGH):GPIO_write_pin(6,LOW);
	(cmd & 0x02)?GPIO_write_pin(7,HIGH):GPIO_write_pin(7,LOW);
	(cmd & 0x04)?GPIO_write_pin(8,HIGH):GPIO_write_pin(8,LOW);
	(cmd & 0x08)?GPIO_write_pin(9,HIGH):GPIO_write_pin(9,LOW);
	(cmd & 0x10)?GPIO_write_pin(10,HIGH):GPIO_write_pin(10,LOW);
	(cmd & 0x20)?GPIO_write_pin(11,HIGH):GPIO_write_pin(11,LOW);
	(cmd & 0x40)?GPIO_write_pin(12,HIGH):GPIO_write_pin(12,LOW);
	(cmd & 0x80)?GPIO_write_pin(13,HIGH):GPIO_write_pin(13,LOW);

	for(i=0;i<3;i++);     //delay
	GPIO_write_pin(5,LOW); // E - Enable Signal. (A start signal for reading or writing data.)
	GPIO_write_pin(4,HIGH); 	// RW - Data read, Data write.

	for(i=0;i<360;i++);     //delay
}


/** @fn lcd_send_ascii
 * @brief 
 * @details 
 * @warning 
 * @param[in] UC ascii_data: Data to be written in ascii format.
 * @param[Out] No output parameter 
*/
void lcd_send_ascii(UC ascii_data)
{
	UI i =0;
	GPIO_write_pin(3,HIGH); 	// RS - Select Register.
	GPIO_write_pin(4,LOW); 		// RW - Data read, Data write.

	GPIO_write_pin(5,HIGH); // E - Enable Signal. (A start signal for reading or writing data.)

	(ascii_data & 0x01)?GPIO_write_pin(6,HIGH):GPIO_write_pin(6,LOW);
	(ascii_data & 0x02)?GPIO_write_pin(7,HIGH):GPIO_write_pin(7,LOW);
	(ascii_data & 0x04)?GPIO_write_pin(8,HIGH):GPIO_write_pin(8,LOW);
	(ascii_data & 0x08)?GPIO_write_pin(9,HIGH):GPIO_write_pin(9,LOW);
	(ascii_data & 0x10)?GPIO_write_pin(10,HIGH):GPIO_write_pin(10,LOW);
	(ascii_data & 0x20)?GPIO_write_pin(11,HIGH):GPIO_write_pin(11,LOW);
	(ascii_data & 0x40)?GPIO_write_pin(12,HIGH):GPIO_write_pin(12,LOW);
	(ascii_data & 0x80)?GPIO_write_pin(13,HIGH):GPIO_write_pin(13,LOW);

	for(i=0;i<3;i++);     //delay
	GPIO_write_pin(5,LOW); // E - Enable Signal. (A start signal for reading or writing data.)
	GPIO_write_pin(4,HIGH); 	// RW - Data read, Data write.

	for(i=0;i<360;i++);     //delay
}

/** @fn lcd_disp_delay
 * @brief 
 * @details 
 * @warning 
 * @param[in] UC ascii_data: Data to be written in ascii format.
 * @param[Out] No output parameter 
*/
void lcd_disp_delay(void)
{
	int i=0;
	for(i = 0;i<20000;i++);
}


/** @fn main
 * @brief Toggle leds LD5,LD6 & LD7.
 * @details Toggle LEDs at finite intervals.
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main ()
{
	UC rx = 0;
	US sw_status = 0;
	UI i = 0;
	lcd_init();
	printf("\n\r Please check LCD");
	while(1)
	{
		//Turn ON LEDs 5, 6, 7 at GPIO pins 16,17,18 respectively.
		
		lcd_send_command(LCD_FUN_SET_8_CMD); // Function set for 8 bit transfer
		lcd_send_command(0x01); //Clear display
		lcd_send_command(LCD_DISP_ON|LCD_CURSOR_ON); // Display & cursor ON, Blink OFF
		lcd_send_command(0x06); // Entry Mode set to increment address.
		lcd_disp_delay();

		lcd_send_ascii('H');
		lcd_send_ascii('E');
		lcd_send_ascii('L');
		lcd_send_ascii('L');
		lcd_send_ascii('O');
		lcd_send_ascii('!');
		lcd_send_ascii(' ');
		lcd_send_ascii('V');
		lcd_send_ascii('E');
		lcd_send_ascii('G');
		lcd_send_ascii('A');
		lcd_send_ascii(' ');
		lcd_send_ascii('H');
		lcd_send_ascii('E');
		lcd_send_ascii('R');
		lcd_send_ascii('E');
		lcd_send_ascii(' ');
		lcd_send_ascii(';');
		lcd_send_ascii(')');

		while(1);
	
	}
	
	
	
}




