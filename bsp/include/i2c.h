#ifndef __I2C_H
#define __I2C_H
/***************************************************


 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 08-Nov-2019
 Filename		: i2c.h
 Purpose		: I2C Firmware header file
 Description		: I2C functions
 Author(s)		: Karthika P
 Email			: karthikap@cdac.in

 See LICENSE for license details.
 ***************************************************/
/**
 @file i2c.h
 @brief header file for I2C interface
 @detail Includes software functions declarations to initialize,
 configure, write and read over I2C interface
 */
#include "config.h"

typedef unsigned char UC; //1 Byte
typedef unsigned short US; //2 Bytes
typedef unsigned int UI; //4 Bytes
typedef unsigned long UL; //8 Bytes

typedef struct {
	UC I2C_CR;
	UC I2C_SR0;
	UC I2C_SR1;
	UC I2C_IER;
	UC I2C_TxFF;
	UC I2C_RxFF;
	UC I2C_CHL;
	UC I2C_CHH;
	UC I2C_CHHL;
	UC I2C_CHHH;
	UC I2C_TXCLR;
} I2C_REG_TYPE;

//Register address mapping
#define I2CReg(i) (*((volatile I2C_REG_TYPE *)(I2C_BASE_ADDR+ (0x100 * i))))


/*  Function declaration section
 *
 ***************************************************/

void i2c_initialize(UC i2c_number);
void i2c_start(UC i2c_number, UC read_length, UC Read);
void i2c_configure(UC i2c_number,UL System_Clock, UL I2C_Clock);
UC i2c_data_write(UC i2c_number, UC Data);
void i2c_stop(UC i2c_number);
UC i2c_ReadData(UC i2c_number);

void i2c_WriteByte_EEPROM(UC i2c_number,UC WBdata, US Word_Address, US Slave_Address_Wr);
UC i2c_ReadByte_EEPROM(UC i2c_number,US Slave_Address_Wr,US Slave_Address_Rd, US Word_Address);


#endif /*__I2C_H*/

