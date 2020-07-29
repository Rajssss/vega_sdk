/***************************************************


 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 08-Nov-2019
 Filename		: i2c_EEEPROM.c
 Purpose		: I2C EEPROM interface
 Description		: Sample EEPROM with I2C interface
 Author(s)		: Karthika P
 Email			: karthikap@cdac.in

 See LICENSE for license details.
 ***************************************************/

 /**
 @file i2c_EEPROM.c
 @brief contains routines for I2C EEPROM interface
 @detail Includes software functions declarations to initialize,
 configure, write and read EEPROM over I2C interface
 */

#include "i2c.h"
#include "stdlib.h"


/**
 @fn main
 @brief writes and reads EEPROM with I2C interface
 @details Initializes configures I2C to write, read and compare data in EEPROM
 @param[in] No input parameters.
 @param[Out] No ouput parameter.
 @return Void function.

 */
void main() {

	printf("I2C EEPROM-24aa64\n\r");
	i2c_configure(25000000, 100000); //System clock =25MHz and I2C clock =100 kHz
	i2c_initialize(0);

	printf("I2C EEPROM Write started 1 byte \n\r");

	i2c_WriteByte(0,0x01, 0x1000, 0xA0);//control code 0A,chip select 0

	UC Byte_data = i2c_ReadByte(0,0xA0, 0xA1, 0x1000);//control code 0A,chip select 0

	if (Byte_data == 0x01) {
		printf("Rxd character is 0x01 \n\r");
		printf("Byte write and read successfull \n\r");

	} else {
		printf("Byte write and read failure \n\r");

	}

	while (1)
		;
}

/**
 @fn i2c_WriteByte
 @brief writes a byte of data to EEPROM with I2C interface
 @details write 1 byte data after writing slave address and word address
 @param[in] unsigned char(i2c_number--which i2c to be used)
 @param[in] unsigned char (WBdata--data to be written)
 @param[in] unsigned short (Word_Address--word address)
 @param[in] unsigned short (Slave_Address_Wr--Slave address for write)
 @param[Out] No ouput parameter.
 @return Void function.

 */
void i2c_WriteByte(UC i2c_number,UC WBdata, US Word_Address, US Slave_Address_Wr) {

	
	while (1) {
		i2c_start(0,0x00,0);

		if (i2c_data_write(0,Slave_Address_Wr)) { //writes slave address
			while ((I2CReg(i2c_number).I2C_SR0 & 0x02) != 0x02)
				; //wait for stop bit to be set

			continue;
		}

		if (i2c_data_write(0,(UC) ((Word_Address >> 8)))) { //writes MSB of address
			while ((I2CReg(i2c_number).I2C_SR0 & 0x02) != 0x02)
				; //wait for stop bit to be set

			continue;
		}

		if (i2c_data_write(0,(UC) (Word_Address & 0xFF))) { //writes LSB of address
			while ((I2CReg(i2c_number).I2C_SR0 & 0x02) != 0x02)
				; //wait for stop bit to be set

			continue;
		}

		if (i2c_data_write(0,WBdata)) {//writes data
			while ((I2CReg(i2c_number).I2C_SR0 & 0x02) != 0x02)
				; //wait for stop bit be set

			continue;
		}

		i2c_stop(0);
		break;

	}
}

/**
 @fn i2c_ReadByte
 @brief writes a byte of data to EEPROM with I2C interface
 @details write 1 byte data after writing slave address and word address
 @param[in] unsigned char(i2c_number--which i2c to be used)
 @param[in] unsigned short (Slave_Address_Wr--Slave address for write)
 @param[in] unsigned short (Slave_Address_Rd--Slave address for read)
 @param[in] unsigned short (Word_Address--word address)
 @param[Out] No ouput parameter.
 @return unsigned char data from EEPROM

 */
UC i2c_ReadByte(UC i2c_number,US Slave_Address_Wr,US Slave_Address_Rd, US Word_Address) {

	UC rxd_data;
	
	while (1) {
		i2c_start(0,0x00,0);

		if (i2c_data_write(0,Slave_Address_Wr)) { //writes slave address
			while ((I2CReg(i2c_number).I2C_SR0 & 0x02) != 0x02)
				; //wait for stop bit to be set

			continue;
		}

		if (i2c_data_write(0,(UC) ((Word_Address >> 8)))) {//writes MSB of address
			while ((I2CReg(i2c_number).I2C_SR0 & 0x02) != 0x02)
				; //wait for stop bit to be set

			continue;
		}

		if (i2c_data_write(0,(UC) (Word_Address & 0xFF))) { //writes LSB of address
			while ((I2CReg(i2c_number).I2C_SR0 & 0x02) != 0x02)
				; //wait for stop bit to be set

			continue;
		}

		i2c_stop(0);
		
		i2c_start(0,0x01,1); //start sequence for reading data
		if (i2c_data_write(0,Slave_Address_Rd)) { //write slave address
			while ((I2CReg(i2c_number).I2C_SR0 & 0x02) != 0x02)
				; //wait for stop bit to be set

			continue;
		}


	rxd_data = i2c_ReadData(0);

	break;
}
while ((I2CReg(i2c_number).I2C_SR0 & 0x02) != 0x02)
; //wait for stop bit to be set

}

