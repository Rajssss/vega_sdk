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
 * QSPI sample pgm
 *
 ***************************************************/

/*  Include section
 *
 *
 ***************************************************/
/**
 @fn main
 @brief writes and reads flash with QSPI interface
 @details Initializes configures QSPI to erase write, read and compare data in FLASH
 @param[in] No input parameters.
 @param[Out] No ouput parameter.
 @return Void function.

 */
#include "stdlib.h"
#include "qspi.h"
CSR_CONFG_TYPE gCSRConfig;


void main() {

	Board_setup(QSPI_0);
	FlashReadId(QSPI_0);
}

/**
 @fn FlashReadId
 @brief reads Flash identification register
 @details  Read access to manufacturer identification, device identification, and Common
 Flash Interface (CFI) information and QRY
 @param[in] unsigned char (qspi_number)
 @param[Out] No ouput parameter.
 @return Void function.

 */

void FlashReadId(UC qspi_number) {

	UC flash_id[3];

	Qspi_read_flash_register(qspi_number, 0x00, 0x03, RD_FLASH_ID_CMD,
	INSTR_LINE_1, DATA_LINE_1, flash_id);

	for (int i = 0; i < 3; i++) {
		printf("\n\r flash_id :%x", flash_id[i]);
		printf("\n\r");
	}

}

/**
 @fn Board_setup
 @brief Initialises QSPI AND Resets the board
 @details
 @param[in] unsigned char (qspi_number)
 @param[Out] No ouput parameter.
 @return Void function.

 */

void Board_setup(UC qspi_number) {

	qspi_delay(10000);

	Qspi_initialise(qspi_number);

	QSPIReg(qspi_number).QSPI_ADLR = 0X00;

	Qspi_instrTxt(qspi_number, INSTR_LINE_3, RESET_ENABLE_CMD);

	while (1) {	//checks for write transfer complete
		gCSRConfig.value = QSPIReg(qspi_number).QSPI_CSR;

		if ((gCSRConfig.Field.CSR_Flag & 0x08) == 0x08) {
			QSPIReg(qspi_number).QSPI_FCR = 0x4F;//cleared all flags except busy
			__asm__ __volatile__ ("fence");
			break;
		} else
			continue;

	}

	Qspi_instrTxt(qspi_number, INSTR_LINE_3, RESET_FLASH_CMD);

	while (1) {	//checks for write transfer complete
		gCSRConfig.value = QSPIReg(qspi_number).QSPI_CSR;

		if ((gCSRConfig.Field.CSR_Flag & 0x08) == 0x08) {
			QSPIReg(qspi_number).QSPI_FCR = 0x4F;//cleared all flags except busy
			__asm__ __volatile__ ("fence");
			break;

		} else
			continue;

	}

	qspi_delay(10000);

}

/**
 @fn qspi_delay
 @brief Provides required amount of delay
 @details
 @param[in] unsigned long (count)
 @param[Out] No ouput parameter.
 @return Void function.

 */

void qspi_delay(UL count) {

	for (UL d = 1; d <= count; d++) //delay 25MHz
			{
	}

}


/**************************************************
 *Function name	: Flash_busy_check_111P
 * Created by	: Karthika P
 * Date created	: 30/10/2019
 * Date modified:
 * Description	:checks the WIP in status indirect mode for 111P
 * Notes			:
 * Set no address and Datalength= 1 byte
 * Command for Read RDSR (Configure CCR and check end transfer)
 * Check WIP of Flash Status (stored in DR)
 * Set Address and Datalength o zero After completion of busy flag of flash
 **************************************************/
/*
void Flash_busy_check_111P(void) {

	UC flash_status;

	Qspi_Set_ADLR(0x00, 0x01); //set for flash status read (1 byte,no address)
	QSPIReg.QSPI_DSR = 0x00;	//8 bit data size
	__asm__ __volatile__ ("fence");

	while (1) {

		Qspi_Set_CCR(0x00, 0x0280, 0x01, 0x05);	//read status register IMode=1 ADMode=0 AdSize=0 AbMode=0 AbSize=0 DCYC=0 DMode=1 FMode=1 AB=00

		while (1) {	//checks for read transfer complete
			gCSRConfg.value = QSPIReg.QSPI_CSR;
			if ((gCSRConfg.Field.CSR_Flag & 0x04) == 0x04)
				break;
			else
				continue;
		}

		//TxStringUartDbg("status:");
		flash_status = QSPIReg.QSPI_DR;

		//TxHexUartByteDbg(flash_status);
		//TxStringUartDbg("\n\r");
		if ((flash_status & 0x01) == 0x00) {	//checks if flash is idle

			break;
		}
		QSPIReg.QSPI_FCR = 0x4F;	//cleared all flags except busy

	}

	QSPIReg.QSPI_FCR = 0x4F;	//cleared all flags except busy

	Qspi_Set_ADLR(0x00, 0x00);  //set for send command
	__asm__ __volatile__ ("fence");

}
*/
