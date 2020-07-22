

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
#include "spi.h"
#include "eeprom_spi.h"

SPIcntrlRegType gSPItransfer;

/**************************************************
 * Function name	    	: ReadStatusRegSPI
 * returns		   	: Nil
 * Created by			: Sreeju GR & Sreenadh S.
 * Date created			: 30/05/2012
 * Description			: Commad (0x05)for reading the status register of SPI device, NB: not the SPI controller.
 * Notes			: Returns the status of SPI device by reading the device's register.
 **************************************************/
/** @fn 
 * @brief 
 * @details 
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



/**************************************************
 * Function name		: memcmp
 * Created by			: Sreeju GR & Sreenadh S.
 * Date created			: 25/04/2012
 * Description			: Compare the original data with the received data from device.
 * Notes			: Returns '1' when mismatch occurred ELSE '0'.
 **************************************************/
/** @fn 
 * @brief 
 * @details 
 */

UC memcmp(UC *bWrData, UC *bRdData, UI wDataLength) {
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

/**************************************************
 * Function name	: ProgramBytePageSPI
 * returns		: Nil
 * Created by		: Sreeju GR & Sreenadh S.
 * Date created		: 30/05/2012
 * Description		: Write data bytes to SPI device.
 * Notes		: A write latch enable command (0x06) is followed by Write bytes command (0x02) and
 * 			 2 bytes of address to where data is to be written.
 **************************************************/
/** @fn 
 * @brief 
 * @details 
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


/**************************************************
 * Function name	: ReadDataBytesSPI
 * returns		: Nil
 * Created by		: Sreeju GR & Sreenadh S.
 * Date created		: 30/05/2012
 * Description		: Read data bytes from SPI device.
 * Notes		: Read bytes command is 0x03 followed by 2 bytes of address from where data is to be read.
 **************************************************/

/** @fn 
 * @brief 
 * @details 
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


/**************************************************
 * Function name		: TestSPI_Few_Locations
 * Created by			: Sreeju GR & Sreenadh S.
 * Date created			: 25/04/2012
 * Description			: Write , read and compare 20 locations.
 * Notes			:
 **************************************************/
/** @fn 
 * @brief 
 * @details 
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
	bStatus = memcmp(pbWrData, pbRdData, wDataLength);


	if (bStatus) //Wrong Data
		printf("\n\r COMPARISON -  FAILED\n\r");
	else //Right Data
		printf("\n\r COMPARISON -  SUCCESS\n\r");
}


/**************************************************
* Function name	: write_reference_data
* returns	: Nil
* Created by	: Sreeju G R
* Date created	: 31/10/2019
* Description	: Write data to array.
* Notes		: 
**************************************************/
void write_reference_data(void)
{
    	//Write Reference Data
	UC i,bData,abWrData[30];
	bData = 0xFF;
	for (i = 0; i < 20; i++) {
		abWrData[i] = bData;
	}
}

/**************************************************
* Function name	: main
* returns	: Nil
* Created by	: Sreeju G R
* Date created	: 31/10/2019
* Description	: GPIO Test cases.
* Notes		: Test cases includes configuring both GPIOs as
* 		  both input and output and lit LEDs based on switch position.
**************************************************/

/** @fn main
 * @brief GPIO Write read program
 */
 
void main ()
{
	TestSPI_Few_Locations(MDP_SPI_0);
	while(1);
}




