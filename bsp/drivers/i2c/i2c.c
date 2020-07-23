/***************************************************


 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 08-Nov-2019
 Filename		: i2c.c
 Purpose		: I2C Firmware
 Description		: I2C routines
 Author(s)		: Karthika P
 Email			: karthikap@cdac.in

 See LICENSE for license details.
 ***************************************************/

/**
 @file i2c.c
 @brief Contains routines for I2C interface
 @detail Includes software functions to initialize,
 configure, write and read over I2C interface
 */

#include "i2c.h"

US SYS_CLK;
US I2C_CLK;

UC gRead_var;

/**
 * @fn i2c_Initialize
 * @brief I2C Initialization
 * @details Initializes I2C Clock period registers
 * @param[in] No input parameters.
 * @param[Out] No ouput parameter.
 * @return Void function.

 */
void i2c_initialize(void) {
	I2CReg.I2C_TXCLR = 0xFF;
	__asm__ __volatile__ ("fence");
	US CH = SYS_CLK / (2 * I2C_CLK);
	I2CReg.I2C_CHL = ((UC) (CH & 0xFF));

	I2CReg.I2C_CHH = (UC) ((CH >> 8) & 0xFF);

	US CHH = SYS_CLK / (4 * I2C_CLK);

	I2CReg.I2C_CHHL = ((UC) (CHH & 0xFF));

	I2CReg.I2C_CHHH = (UC) ((CHH >> 8) & 0xFF);

	__asm__ __volatile__ ("fence");
}

/** @fn i2c_Start
 * @brief Generates Start Sequence for I2C
 * @details Start sequence is setting start bit and read length in I2C control
 *			register for I2C operations.
 * @param[in] unsigned char (read_length).
 * @param[Out] No output parameters.
 * @return Nil
 */

void i2c_start(UC read_length) {

	I2CReg.I2C_TXCLR = 0xFF;	//clear TxFifo
	while (((I2CReg.I2C_SR0 & 0x08) != 0x08)
			|| ((I2CReg.I2C_SR0 & 0x10) != 0x10))
		; //checks for transmission complete and TxFifo empty

	if (gRead_var == 1)
		I2CReg.I2C_CR = 0x05; //Set Start bit for read;read_length=1 byte
	else
		I2CReg.I2C_CR = ((read_length >> 1) | 0x01); //Set Start bit for write;
	while ((I2CReg.I2C_SR0 & 0x01) != 0x01)
		; //check start sequence initiated
	__asm__ __volatile__ ("fence");
}

/** @fn i2c_configure
 * @brief Configures I2C
 * @details Sets System frequency and I2C frequncy for I2C operation
 * @param[in] unsigned short(System_Clock,I2C_Clock)
 * @param[Out] void
 * @return nil
 */

void i2c_configure(UL System_Clock, UL I2C_Clock) {
	I2C_CLK = I2C_Clock;
	SYS_CLK = System_Clock;
}

/** @fn i2c_data_write
 * @brief Write data to transmit Fifo and checks for NACK
 * @details Data/address to be transmitted is written into transmit fifo and checks NACK
 * @param[in] unsigned char(Data-->Data/Address to be transmitted)
 * @param[Out] int
 * @return 0 if ACK and 1 if NACK
 */

int i2c_data_write(UC Data) {
	while ((I2CReg.I2C_SR0 & 0x04) == 0x04)
		; //waits if TxFF full

	I2CReg.I2C_TxFF = Data;
	__asm__ __volatile__ ("fence");

	while ((I2CReg.I2C_SR0 & 0x10) != 0x10)

		; //wait for Transfer complete
	if ((I2CReg.I2C_SR1 & 0x01) == 0x01) //checks NACK

			return 1 ;
	else
		return 0;
}


/** @fn i2c_Stop
 * @brief Generates Stop Sequence for I2C
 * @details Stop sequence is setting stop bit I2C control register for I2C operations.
 * @param[in] No input parameters.
 * @param[Out] No output parameters.
 * @return Nil
 */

void i2c_stop(void) {

	I2CReg.I2C_CR = 0x02; //Set Stop bit;
	__asm__ __volatile__ ("fence");
	while ((I2CReg.I2C_SR0 & 0x02) != 0x02)
		; //check stop sequence initiated

}

/** @fn i2c_ReadData
 * @brief Read  data from  I2C device
 * @details After Rx Complete,read data from fifo till fifo is empty
 * @param[in] void
 * @param[Out]  unsigned char
 * @return Data-->Data from I2C device
 */

UC i2c_ReadData(void) {

	UC Data;

	while ((I2CReg.I2C_SR0 & 0x80) != 0x80)
		; //checks for RX complete

	if ((I2CReg.I2C_SR0 & 0x40) != 0x40) { //checking RXfifo empty
		Data = I2CReg.I2C_RxFF; //reading RXFF
		//TxUartDbg(Data);
	}

	return Data;

}

