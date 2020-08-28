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



/**************************************************
 * Function name	: Qspi_Set_ADLR
 * Created by	: Karthika P
 * Date created	: 01/10/2019
 * Description	: Set ADLR   Address-Data length register
 * Notes		Sets the value of the Address and number of data to be retreived
 **************************************************/

void Qspi_read_flash_register(UC qspi_number, UL QSPI_Address, UI QSPI_DataLength, UC command, UC instr_line,UC read_indirect,UC data_line, UC *read_data){


	QSPIReg(qspi_number).QSPI_ADLR = ((QSPI_Address << 32) | QSPI_DataLength);
	QSPIReg(qspi_number).QSPI_DSR = 0x00;	//8 bit data size
	QSPIReg(qspi_number).QSPI_CCR = ((data_line << 25) | (read_indirect << 23)
			| (instr_line << 8) | command);
	while (1) {	//checks for read transfer complete
				gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
				if ((gCSRConfg.Field.CSR_Flag & 0x04) == 0x04)
					break;
				else
					continue;
			}
	for (int i = 0; i < QSPI_DataLength; i++){
	*read_data = QSPIReg(qspi_number).QSPI_DR;
	read_data++;
	}
	__asm__ __volatile__ ("fence");
}
/**************************************************
 * Function name	: Qspi_Set_ADLR
 * Created by	: Karthika P
 * Date created	: 01/10/2019
 * Description	: Set ADLR   Address-Data length register
 * Notes		Sets the value of the Address and number of data to be retreived
 **************************************************/
void Qspi_instr_flash(UC qspi_number,UC command, UC instr_line){
	QSPIReg(qspi_number).QSPI_CCR = ((instr_line << 8) | command);
}
/**************************************************
 * Function name	: Qspi_Set_ADLR
 * Created by	: Karthika P
 * Date created	: 01/10/2019
 * Description	: Set ADLR   Address-Data length register
 * Notes		Sets the value of the Address and number of data to be retreived
 **************************************************/

void Qspi_write_flash_register(UC qspi_number, UL QSPI_Address, UI QSPI_DataLength, UC command, UC instr_line,UC read_indirect,UC data_line, UC wr_data){


	QSPIReg(qspi_number).QSPI_ADLR = ((QSPI_Address << 32) | QSPI_DataLength);
	QSPIReg(qspi_number).QSPI_DSR = 0x00;	//8 bit data size
	QSPIReg(qspi_number).QSPI_DR = wr_data;
	QSPIReg(qspi_number).QSPI_CCR = ((data_line << 25) | (read_indirect << 23)
			| (instr_line << 8) | command);
	while (1) {	//checks for read transfer complete
				gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
				if ((gCSRConfg.Field.CSR_Flag & 0x04) == 0x04)
					break;
				else
					continue;
			}

	__asm__ __volatile__ ("fence");
//}


while (1) { //checks whether busy
		gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
		if ((gCSRConfg.Field.CSR_Flag & 0x80) == 0x80)
			continue;
		else
			break;
	}
	gCSRConfg.Field.CSR_Prescalar = Clk_Prescalar; //  Sclk/2=00
	gCSRConfg.Field.CSR_CsIE = (Poll_Match << 7) | (Auto_poll_stop << 6) | 0x00; //CS0
	gCSRConfg.Field.CSR_LSB = (fifo_thres << 2) | (0x01); //QSPI enabled

	QSPIReg(qspi_number).QSPI_CSR = gCSRConfg.value;

	__asm__ __volatile__ ("fence");
QSPIReg(qspi_number).QSPI_ADLR = ((QSPI_Address << 32) | QSPI_DataLength);
QSPIReg(qspi_number).QSPI_CCR = ((read_indirect << 25) | (data_line << 23)
			(address_size<<12)|(address_line<<10)| (instr_line << 8) | command);
	Qspi_Set_CCR(0x00, 0x0180, 0x3F, 0x12); //Flash Page programming 4QPP, IMode=3 ADMode=3 AdSize=3 AbMode=0 AbSize=0 DCYC=0 DMode=3 FMode=0 AB=00
	gCSRConfg.value = QSPIReg(qspi_number).QSPI_CSR;
	if ((gCSRConfg.Field.CSR_Flag & 0x02) == 0x02) {
		TxStringUartDbg(" Write address out of range \n\r");
		TxStringUartDbg("CSR:");
		TxHexUartDWordDbg(QSPIReg(qspi_number).QSPI_CSR);
		TxStringUartDbg("\n\r");
		QSPIReg(qspi_number).QSPI_FCR = 0x02;	//cleared Write transfer error flag
		__asm__ __volatile__ ("fence");
		qspi_failure();

	}
	for (int j = 0; j < (Wdata_len / fifo_thres); j++) {

		while (1) { //wait for free space in fifo

			gCSRConfg.value = QSPIReg.QSPI_CSR;
			if ((gCSRConfg.Field.CSR_Flag & 0x20) == 0x20) {

				break; //break if Txfifo is empty or Fifo have the space for n+1 bytes(63+1) to write
			}
		}
		QSPIReg.QSPI_DSR = Wdata_size;

		__asm__ __volatile__ ("fence");
		loop_count_DataReg = bit_value_DSR(Wdata_size, fifo_thres);

		for (int i = 0; i < loop_count_DataReg; i++) {

			if (gbulk_data_flag == 1) {

				Write_data = bulk_data_RW(Wdata_size);

			} else
				Write_data = data_RW(Wdata_size);
			QSPIReg.QSPI_DR = Write_data;

		}

	}

	__asm__ __volatile__ ("fence");
	Qspi_check_TXComplete();
