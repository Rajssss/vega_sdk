/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  spi.c
 * Brief Description of file             :  Driver to control the spi device.
 * Name of Author                        :  Sreeju G R
 * Email ID                              :  sreeju@cdac.in

 Copyright (C) 2020  CDAC(T). All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

 ***************************************************************************/

#include <include/stdlib.h>
#include <include/qspi.h>
#include <include/config.h>

CSR_CONFG_TYPE gCSRConfg;
DCR_CONFG_TYPE gDCRConfg;

/**
 @fn Qspi_initialise
 @brief Initialises QSPI
 @details sets prescalar ,choose mode , chip select high time and flash memory size
 Enable QSPI
 @param[in] unsigned char (qspi_number)
 @param[Out] No ouput parameter.
 @return Void function.

 */

void Qspi_initialise(UC qspi_number) {

	while (1) { //checks whether busy
		if (QSPI_wait_if_busy)
			continue;
		else
			break;
	}

	gCSRConfg.Field.CSR_Prescalar = PRESCALAR_MAX; //  Sclk/2=00
	gCSRConfg.Field.CSR_LSB = 0x01; //QSPI enabled
	QSPIReg(qspi_number).QSPI_CSR = gCSRConfg.value;

	__asm__ __volatile__ ("fence");

	while (1) { //checks whether busy
		if (QSPI_wait_if_busy)
			continue;
		else
			break;
	}

	gDCRConfg.Field.DCR_ModeCHST = (CHIP_HIGH_TIME << 01) | CK_MODE_0; //Mode 0,Chip select high time =5 cycles
	gDCRConfg.Field.DCR_FSize = FLASH_MEMORY_SIZE; //64MB flash memory can be connected
	QSPIReg(qspi_number).QSPI_DCR = gDCRConfg.value;

	__asm__ __volatile__ ("fence");

}

/**
 @fn Qspi_read_flash_register
 @brief reads flash register
 @details sets address,data length and data size ,choose required data,instruction line
 @param[in] unsigned char (qspi_number)
 @param[in] unsigned long (address)
 @param[in] unsigned int (dataLength)
 @param[in] unsigned char (command)
 @param[in] unsigned char (instr_line)
 @param[in] unsigned char (data_line)
 @param[Out] unsigned char
 @return Void function.

 */

void Qspi_read_flash_register(UC qspi_number, UL address, UI dataLength,
		UC command, UC instr_line, UC data_line, UC *read_data) {

	QSPIReg(qspi_number).QSPI_ADLR = ((address << 32) | dataLength);
	QSPIReg(qspi_number).QSPI_DSR = 0x00;	//8 bit data size
	QSPIReg(qspi_number).QSPI_CCR = ((data_line << 25) | (INDIRECT_RD << 23)
			| (instr_line << 8) | command);

	while (1) {	//checks for read transfer complete
		gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
		if ((gCSRConfg.Field.CSR_Flag & 0x04) == 0x04)
			break;
		else
			continue;
	}

	for (int i = 0; i < dataLength; i++) {
		*read_data = QSPIReg(qspi_number).QSPI_DR;
		read_data++;
	}
	QSPIReg(qspi_number).QSPI_FCR = 0x4F;	//cleared all flags except busy

	__asm__ __volatile__ ("fence");
}

/**
 @fn Qspi_instrTxt
 @brief writes flash command to QSPI register
 @details writes flash command to QSPI register with the required instruction line
 @param[in] unsigned char (qspi_number)
 @param[in] unsigned char (instr_line)
 @param[in] unsigned char (command)
 @param[Out] No ouput parameter.
 @return Void function.

 */
void Qspi_instrTxt(UC qspi_number, UC instr_line, UC command) {

	QSPIReg(qspi_number).QSPI_CCR = ((instr_line << 8) | command);

}

/**
 @fn Qspi_write_flash_register
 @brief writes flash register
 @details writes flash register  with the required instruction line/data line
 @param[in] unsigned char (qspi_number)
 @param[in] unsigned long (address)
 @param[in] unsigned int (dataLength)
 @param[in] unsigned char (command)
 @param[in] unsigned char (instr_line)
 @param[in] unsigned char (data_line)
 @param[in] unsigned char (wr_data)
 @param[Out] No ouput parameter.
 @return Void function.

 */

void Qspi_write_flash_register(UC qspi_number, UL address, UI dataLength,
		UC command, UC instr_line, UC data_line, UC wr_data) {

	QSPIReg(qspi_number).QSPI_ADLR = ((address << 32) | dataLength);
	QSPIReg(qspi_number).QSPI_DSR = 0x00;	//8 bit data size
	QSPIReg(qspi_number).QSPI_DR = wr_data;
	QSPIReg(qspi_number).QSPI_CCR = ((data_line << 25) | (INDIRECT_WR << 23)
			| (instr_line << 8) | command);

	while (1) {	//checks for write transfer complete
		gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
		if ((gCSRConfg.Field.CSR_Flag & 0x08) == 0x08) {
			QSPIReg(qspi_number).QSPI_FCR = 0x4F;//cleared all flags except busy
			__asm__ __volatile__ ("fence");
			break;
		}

		else
			continue;
	}

	__asm__ __volatile__ ("fence");
}

/**
 @fn Qspi_mem_write
 @brief writes flash memory
 @details writes flash memory with the required instruction line/data line
 @param[in] unsigned char (qspi_number)
 @param[in] unsigned long (address)
 @param[in] unsigned int (dataLength)
 @param[in] unsigned char (command)
 @param[in] unsigned char (instr_line)
 @param[in] unsigned char (data_line)
 @param[in] unsigned char (data_size)
 @param[in] unsigned char (address_line)
 @param[in] unsigned char (address_size)
 @param[in] unsigned char (fifo_threshold)
 @param[in] unsigned char (write_data)
 @param[Out] No ouput parameter.
 @return Void function.

 */

void Qspi_mem_write(UC qspi_number, UL Address, UI DataLength, UC command,
		UC instr_line, UC data_line, UC data_size, UC address_line,
		UC address_size, UC fifo_threshold, UC *write_data) {

	UC loop_count_DataReg;

	switch (data_size) {

	case 0x00:
		loop_count_DataReg = fifo_threshold / 1;
		break;

	case 0x01:
		loop_count_DataReg = fifo_threshold / 2;
		break;

	case 0x02:
		loop_count_DataReg = fifo_threshold / 4;
		break;

	case 0x03:
		loop_count_DataReg = fifo_threshold / 8;
		break;

	}

	QSPIReg(qspi_number).QSPI_ADLR = ((Address << 32) | DataLength);
	QSPIReg(qspi_number).QSPI_CCR = ((INDIRECT_WR << 25)
			| (data_line << 23)|(address_size << 12) | (address_line << 10)
			| (instr_line << 8) | command);

	gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
	if ((gCSRConfg.Field.CSR_Flag & 0x02) == 0x02) {
		printf(" Write address out of range \n\r");
		QSPIReg(qspi_number).QSPI_FCR = 0x02;//cleared Write transfer error flag
		__asm__ __volatile__ ("fence");
		while(1);
		//qspi_failure();

	}

	for (int j = 0; j < (DataLength / fifo_threshold); j++) {

		while (1) { //wait for free space in fifo

			gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
			if ((gCSRConfg.Field.CSR_Flag & 0x20) == 0x20) {

				break; //break if Txfifo is empty or Fifo have the space for n+1 bytes(63+1) to write
			}
		}

		QSPIReg(qspi_number).QSPI_DSR = data_size;

		__asm__ __volatile__ ("fence");

		for (int i = 0; i < loop_count_DataReg; i++) {

			QSPIReg(qspi_number).QSPI_DR = *write_data;
			write_data++;
		}

	}

	__asm__ __volatile__ ("fence");

	while (1) {	//checks for write transfer complete
		gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
		if ((gCSRConfg.Field.CSR_Flag & 0x08) == 0x08) {
			QSPIReg(qspi_number).QSPI_FCR = 0x4F;//cleared all flags except busy
			__asm__ __volatile__ ("fence");
			break;
		}

		else
			continue;
	}
}

/**
 @fn Qspi_mem_read
 @brief reads flash memory
 @details reads flash memory with the required instruction line/data line
 @param[in] unsigned char (qspi_number)
 @param[in] unsigned long (address)
 @param[in] unsigned int (dataLength)
 @param[in] unsigned char (command)
 @param[in] unsigned char (instr_line)
 @param[in] unsigned char (data_line)
 @param[in] unsigned char (data_size)
 @param[in] unsigned char (address_line)
 @param[in] unsigned char (address_size)
 @param[in] unsigned char (fifo_threshold)
 @param[in] unsigned char (write_data)
 @param[Out] unsigned char
 @return Void function.

 */

void Qspi_mem_read(UC qspi_number, UL Address, UI DataLength, UC command,
		UC instr_line, UC data_line, UC data_size, UC address_line,
		UC address_size, UC fifo_threshold, UC *read_data) {

	UC loop_count_DataReg;
	switch (data_size) {

	case 0x00:
		loop_count_DataReg = fifo_threshold / 1;
		break;

	case 0x01:
		loop_count_DataReg = fifo_threshold / 2;
		break;

	case 0x02:
		loop_count_DataReg = fifo_threshold / 4;
		break;

	case 0x03:
		loop_count_DataReg = fifo_threshold / 8;
		break;

	}

	QSPIReg(qspi_number).QSPI_ADLR = ((Address << 32) | DataLength);
	QSPIReg(qspi_number).QSPI_CCR = ((INDIRECT_RD << 25)
			| (data_line << 23)|(address_size << 12) | (address_line << 10)
			| (instr_line << 8) | command);
	//Qspi_Set_CCR(0x00, 0x0180, 0x3F, 0x12); //Flash Page programming 4QPP, IMode=3 ADMode=3 AdSize=3 AbMode=0 AbSize=0 DCYC=0 DMode=3 FMode=0 AB=00
	gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;

	if ((gCSRConfg.Field.CSR_Flag & 0x01) == 0x01) {
		printf(" Read address out of range \n\r");
		QSPIReg(qspi_number).QSPI_FCR = 0x01;//cleared Write transfer error flag
		__asm__ __volatile__ ("fence");
		while(1);

	}
	for (int j = 0; j < (DataLength / fifo_threshold); j++) {

		while (1) {	//wait till data available in fifo
			gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
			if ((gCSRConfg.Field.CSR_Flag & 0x10) == 0x10) {// break if RxFifo have Fth +1 data to be read

				break;
			} else {

				continue;
			}
		}
		QSPIReg(qspi_number).QSPI_DSR = data_size;
		__asm__ __volatile__ ("fence");

		for (int i = 0; i < loop_count_DataReg; i++) {//check read threshold..8 for 64 bit

			*read_data = QSPIReg(qspi_number).QSPI_DR;
			read_data++;
		}

	}

	while (1) {	//checks for transfer complete
		gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
		if ((gCSRConfg.Field.CSR_Flag & 0x04) == 0x04)
			break;
		else
			continue;
	}

}

/**
 @fn QSPI_wait_if_busy
 @brief waits if QSPI is busy
 @details
 @param[Out] No ouput parameter.
 @return returns 1 if busy and 0 if idle.

 **/

UC QSPI_wait_if_busy(UC qspi_number) {
	//checks whether busy
	gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
	if ((gCSRConfg.Field.CSR_Flag & 0x80) == 0x80)
		return 1;
	else
		return 0;

}
