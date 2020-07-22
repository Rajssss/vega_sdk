#ifndef __I2C_H
#define __I2C_H
/***************************************************


 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 08-Nov-2019
 Filename		: i2c.h
 Purpose		: I2C Firmware header file
 Description	: I2C functions
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
#define I2CReg (*((volatile I2C_REG_TYPE *)0x10000800))

/*  Function declaration section
 *
 ***************************************************/

void i2c_initialize(void);
void i2c_start(UC read_length);
void i2c_configure(UL System_Clock, UL I2C_Clock);
int i2c_data_write(UC Data);
void i2c_stop(void);
UC i2c_ReadData(void);


void i2c_WriteByte(UC WBdata, US Word_Address, US Slave_Address_Wr);
UC i2c_ReadByte(US Slave_Address_Wr,US Slave_Address_Rd, US Word_Address);

#endif /*__I2C_H*/

