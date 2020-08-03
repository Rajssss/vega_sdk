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

	printf("I2C EEPROM-24aa64-V7\n\r");
	i2c_configure(0, 25000000, 100000); //System clock =25MHz and I2C clock =100 kHz
	//i2c_initialize(0);

	printf("I2C EEPROM Write started 1 byte \n\r");

	i2c_WriteByte_EEPROM(0, 0x05, 0x1000, 0xA2);//control code 0A,chip select 0
	printf("I2C EEPROM Read started 1 byte \n\r");
	UC Byte_data = i2c_ReadByte_EEPROM(0, 0xA0, 0xA3, 0x1000);//control code 0A,chip select 0


	if (Byte_data == 0x05) {
		printf("Rxd character is 0x05 \n\r");
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
void i2c_WriteByte_EEPROM(UC i2c_num, UC WBdata, US Word_Address,
		US Slave_Address_Wr) {

	while (1) {
		i2c_start(i2c_num, 0x00, 0);
		//printf("start sequence generated\n\r");
		if (i2c_data_write(i2c_num, Slave_Address_Wr)) { //writes slave address and set EEPROM to write mode
			//printf("Slave address NACK\n\r");
			continue;//received NACK
		}
		//printf("Slave address ACK\n\r");
		if (i2c_data_write(i2c_num, (UC) ((Word_Address >> 8)))) { //writes MSB of address

			continue;//received NACK
		}
		//printf("Word address MSB ACK\n\r");
		if (i2c_data_write(i2c_num, (UC) (Word_Address & 0xFF))) { //writes LSB of address

			continue;//received NACK
		}
		//printf("Word address LSB ACK\n\r");
		if (i2c_data_write(i2c_num, WBdata)) { //writes data

			continue;//received NACK
		}
		//printf("Data ACK\n\r");
		i2c_stop(i2c_num);
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
UC i2c_ReadByte_EEPROM(UC i2c_num, US Slave_Address_Wr, US Slave_Address_Rd,
		US Word_Address) {

	UC rxd_data;

	while (1) {
		i2c_start(i2c_num, 0x00, 0);

		if (i2c_data_write(i2c_num, Slave_Address_Wr)) { //writes slave address

			continue;//received NACK
		}
		//printf("Slave address ACK\n\r");
		if (i2c_data_write(i2c_num, (UC) ((Word_Address >> 8)))) { //writes MSB of address

			continue;//received NACK
		}

		if (i2c_data_write(i2c_num, (UC) (Word_Address & 0xFF))) { //writes LSB of address

			continue;//received NACK
		}
		//printf("Word address  ACK\n\r");
		i2c_stop(i2c_num);

		i2c_start(i2c_num, 0x01, 1); //start sequence for reading data
		if (i2c_data_write(i2c_num, Slave_Address_Rd)) { //write slave address and set EEPROM to read mode

			continue;//received NACK
		}
		//printf("Slave address read ACK\n\r");
		rxd_data = i2c_ReadData(i2c_num);
		printf("data is %x",rxd_data);
					printf("\n\r");
		return rxd_data;
		break;
	}

}
#ifdef USED
/**
 @fn i2c_WriteMultiByte_EEPROM
 @brief writes given number of byte of data to EEPROM with I2C interface
 @details write bytes data after writing slave address and word address
 @param[in] unsigned char(i2c_number--which i2c to be used)
 @param[in] unsigned char (WBdata--data to be written)
 @param[in] unsigned short (Word_Address--word address)
 @param[in] unsigned short (Slave_Address_Wr--Slave address for write)
 @param[Out] No ouput parameter.
 @return Void function.

 */
void i2c_WriteMultiByte_EEPROM(UC i2c_number,UL no_of_bytes) {
	UC WPdata = 0x01;

	for (UL j = 0; j < no_of_bytes; j++) {
		i2c_WriteByte_EEPROM(i2c_number, WPdata, j, 0xA0);//control code 0A,chip select 0

		WPdata ++;

	}

}

/**************************************************
 * Function name	: i2c_ReadFlash_Full_MultiChar
 * Created by	: Karthika P
 * Date created	: 19/08/2019
 * Description	: Read flash(multi characters)
 * Notes			:
 **************************************************/
void i2c_ReadMultiByte_EEPROM(UC i2c_number,UL no_of_bytes) {

	UC Ref_data = 0x01;

	for (US j = 0; j < no_of_bytes; j++) {
	UC Rxd_data=i2c_ReadByte_EEPROM(i2c_number,0xA2, 0xA3,j);
	if (Rxd_data != Ref_data) {
						printf("read unsuccessfull \n\r");
						printf("rxd data ");
						TxHexUartByteDbg(i2c_rxd_data);
						TxStringUartDbg("; ref data  ");
						TxHexUartByteDbg(wr_data);
						TxStringUartDbg("\n\r");
						i2c_failure();
					}
		Ref_data ++;

	}
	//TxStringUartDbg("Full Flash read successfull //
#endif




