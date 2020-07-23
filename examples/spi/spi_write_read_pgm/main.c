

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
* SPI sample pgm
*
***************************************************/

/*  Include section
*
*
***************************************************/

#include "stdlib.h"
#include "spi.h"
#include "m25p80_eeprom.h"


/** @fn ReadStatusRegSPI
 * @brief read the status reg value  of m25p80 eeprom.
 * @details The eeprom's command to read ststus reg value is written to the SPI controller and the received data is read.
 * @warning 
 * @param[in] unsigned char 
 * @param[Out] status register value. 
*/
UC ReadStatusRegSPI(UC spi_number)
{
	UC read_data, bDummy = 0;

	SPI_check_busy(spi_number);	// Check if SPI controller is busy.

	SPI_set_CSAAT_high(spi_number);	// Setting CSAAT bit high.

	SPI_write(spi_number,RD_STATUS_REG_SPI_CMD); // Command : 0x05

	SPI_write(spi_number,bDummy);

	SPI_set_CSAAT_low(spi_number);	// Setting CSAAT bit low.

	read_data = SPI_read(spi_number);	// Read status reg value from rx data register.

	return read_data;
}



/** @fn comparedata
 * @brief Compare written value with read vaue from eeprom.
 * @details Compare the original data with the received data from device.
 * @warning 
 * @param[in] unsigned char *, unsigned char *, unsigned integer
 * @param[Out] status = 1 when comparison fails, status = 0 when comparison passes. 
*/
UC comparedata(UC *bWrData, UC *bRdData, UI wDataLength) {
	UC status = 0;
	UI i;
	for (i = 0; i < wDataLength; i++) {
		if (*bWrData == *bRdData)
			status = 0;
		else {
			status = 1;
			return status;
		}
		bWrData++;
		bRdData++;
	}
	return status;
}

/** @fn ProgramBytePageSPI
 * @brief Program the location of eeprom with a few bytes.
 * @details Provide the address and data to be written to the eeprom.
 * @warning 
 * @param[in] unsigned char, unsigned long, unsigned char *, unsigned char *, unsigned long
 * @param[Out] No output parameter. 
*/
void ProgramBytePageSPI(UC spi_number,UL wAddress, UC *pbData,UL wDatalength)
{
		int i;
		UC bStatus;
		UL reg_data = 0;
		// Write enable command.
		SPI_write(spi_number,WR_EN_LATCH_SPI_CMD);

		do {
			bStatus = ReadStatusRegSPI(spi_number);
		} while (!(bStatus & 0x02)); // Waiting till Write Enable Latch bit becomes 1

		SPI_check_busy(spi_number);

		SPI_set_CSAAT_high(spi_number);	// Setting CSAAT bit high.

		SPI_write(spi_number,BYTE_PAGE_PGM_SPI_CMD); // Page program command

		SPI_write(spi_number,(wAddress >> 8)); //MSB of start address

		SPI_write(spi_number,wAddress); //LSB of start address

		for (i = 0; i < wDatalength; i++) {
				
			SPI_write(spi_number,pbData[i]);
		}

		SPI_set_CSAAT_low(spi_number);	// Setting CSAAT bit low.


		do {
			bStatus = ReadStatusRegSPI(spi_number);
		} while (bStatus & 0x01); // Waiting till Write In Progress bit becomes 0

		return;
}


/** @fn ReadDataBytesSPI
 * @brief Read the location of eeprom.
 * @details Provide the address and number of data to be read from eeprom.
 * @warning 
 * @param[in] unsigned char, unsigned long, unsigned char *, unsigned long
 * @param[Out] No output parameter. 
*/
void ReadDataBytesSPI(UC spi_number,UL wAddress, UC *pbData, UL wDatalength)
{
	UL i;

	UC bDummy = 0;

	SPI_check_busy(spi_number);

	SPI_set_CSAAT_high(spi_number);	// Setting CSAAT bit high.

	SPI_write(spi_number,RD_DATA_BYTES_SPI_CMD);

	SPI_write(spi_number,(wAddress >> 8)); //MSB of start address

	SPI_write(spi_number,wAddress); //LSB of start address

	for (i = 0; i < wDatalength; i++)
	{
		SPI_write(spi_number,bDummy); // A dummy byte is written to read a data byte.
		pbData[i] = SPI_read(spi_number); // Read data stored in array.
	}

	SPI_set_CSAAT_low(spi_number);	// Setting CSAAT bit low.

	return;
}


/** @fn TestSPI_Few_Locations
 * @brief Write, read and compare eeprom locations.
 * @details Write, read and compare eeprom locations.
 * @warning 
 * @param[in] unsigned char
 * @param[Out] No output parameter. 
*/
void TestSPI_Few_Locations(UC spi_number)
{
	UC rx = 0, abWrData[200], bData, *pbWrData;
	UC abRdData[200], bStatus, *pbRdData;
	UI i, wDataLength, wAddress;

	pbWrData = abWrData;
	pbRdData = abRdData;
	wAddress = 0x0000;

	wDataLength = 10;

	// Initiliase SPI memory.
	SPI_init(MDP_SPI_0);

	// Write to SPI memory
	ProgramBytePageSPI(spi_number,wAddress, pbWrData, wDataLength);

	// Read from SPI memory
	ReadDataBytesSPI(spi_number,wAddress, pbRdData, wDataLength);

	// Compare data from SPI memory
	bStatus = comparedata(pbWrData, pbRdData, wDataLength);


	if (bStatus) //Wrong Data
		printf("\n\r COMPARISON -  FAILED\n\r");
	else //Right Data
		printf("\n\r COMPARISON -  SUCCESS\n\r");
}


/** @fn main
 * @brief Program eeprom.
 * @details Write, read and compare eeprom locations.
 * @warning 
 * @param[in] No input parameter. 
 * @param[Out] No output parameter. 
*/
void main ()
{
	TestSPI_Few_Locations(MDP_SPI_0);
	while(1);
}




