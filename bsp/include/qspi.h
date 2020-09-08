#ifndef _QSPI_H
#define _QSPI_H

/***************************************************
 * Module name: qspi.h
 *
 * Copyright 2020 Company CDAC(T).
 * All Rights Reserved.
 *
 *  The information contained herein is confidential
 * property of Company. The user, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Company.
 *
 *
 * Module Description:
 * QSPI registers and function declarations
 *
 ***************************************************/

/*  Include section
 *
 ***************************************************/

/*  Define section
 *
 *
 ***************************************************/
#define QSPI_0			0
#define QSPI_1			1
#define QSPI_2			2
#define QSPI_3			3


#define PRESCALAR_MAX	00
#define PRESCALAR_MIN	0xFF

#define CK_MODE_0         		0
#define CK_MODE_1         		1

#define CHIP_HIGH_TIME 			0x05

#define INSTR_LINE_1	0x01
#define INSTR_LINE_2	0x02
#define INSTR_LINE_3	0x03


#define POLLING_INTERVAL_256	0x40
#define AUTO_POLL_STOP_ON		0x01
#define AUTO_POLL_STOP_OFF		0x00
#define POLL_MODE_AND			0X00
#define POLL_MODE_OR			0X01


#define DATA_LINE_1		0x01
#define DATA_LINE_2		0x02
#define DATA_LINE_3		0x03

#define DATA_SIZE_0		0x00
#define DATA_SIZE_1		0x01
#define DATA_SIZE_2		0x02
#define DATA_SIZE_3		0x03


#define INDIRECT_WR 	0x00
#define INDIRECT_RD 	0x01
#define AUTOPOLL_RD 	0X02




#define SPI_INTR_MODE			1
#define SPI_POLLING_MODE		2
#define DATA_BYTES 			65536

// SPI BASE ADDRESS

#define LOW				0
#define HIGH 				1

#define MSB				0
#define LSB 				1

#define SPI_FIXD_PERIPH         	0
#define SPI_VAR_PERIPH          	1 

#define CPOL_MODE_0         		0
#define CPHA_MODE_0         		0  
#define CPOL_MODE_3         		1
#define CPHA_MODE_3         		1 

#define BPT_8				0

#define TXINTR_DIS			0
#define RXINTR_DIS			0

#define TXINTR_EN			1
#define RXINTR_EN			1

#define SPI_MODE_0			0
#define SPI_MODE_3			3

#define SPI_CS_0			0
#define SPI_CS_1			1
#define SPI_CS_2			2
#define SPI_CS_3			3

#define RX_TX_INTR_DIS			0
#define TX_DIS_RX_EN_INTR		1
#define RX_DIS_TX_EN_INTR		2
#define RX_TX_INTR_EN			3

#define SPI_BAUD_CFD_4        		0
#define SPI_BAUD_CFD_8        		1 
#define SPI_BAUD_CFD_16        		2 
#define SPI_BAUD_CFD_32        		3
#define SPI_BAUD_CFD_64        		4
#define SPI_BAUD_CFD_128        	5 
#define SPI_BAUD_CFD_256       		6
#define SPI_BAUD_CFD_512        	7 
#define SPI_BAUD_CFD_1024        	8 
#define SPI_BAUD_CFD_2048        	9

#define SPI_BUSY_BIT            	(1<<4)
#define SPI_OVERR_BIT           	(1<<5)
#define SPI_RX_COMPLETE_BIT    		(1<<6)
#define SPI_TX_HOLD_EMPTY_BIT   	(1<<7) 

#define SPI_RX_INT_STATUS_BIT       	(1<<2)
#define SPI_TX_INT_STATUS_BIT       	(1<<3)

#define QSPI_BASE_ADDR				0x10200100UL

/*************Micron M25P80 Serial Flash************* 
 *************Embedded Memory Command Set************/
#define RD_STATUS1_REG_QSPI_CMD 	0x05
#define RD_FLASH_ID_CMD 			0x9F
#define RESET_ENABLE_CMD			0x66
#define RESET_FLASH_CMD				0x99

/*#define WR_DISABLE_LATCH_SPI_CMD			0x04
 #define WR_EN_LATCH_SPI_CMD     			0x06
 #define BYTE_PAGE_PGM_SPI_CMD  				0x02
 #define RD_DATA_BYTES_SPI_CMD  				0x03
 #define RD_STATUS_REG_SPI_CMD				0x05
 #define RDID_SPI_CMD					0x83
 /***************************************************/



#define FLASH_MEMORY_SIZE	0X19
typedef unsigned char UC; //1 Byte
typedef unsigned short US; //2 Bytes
typedef unsigned int UI; //4 Bytes
typedef unsigned long UL; //8 Bytes

typedef struct {
	UL QSPI_CSR;
	UL QSPI_DCR;
	UL QSPI_ADLR;
	UL QSPI_CCR;
	UL QSPI_DR;
	UL QSPI_SPR;
	UL QSPI_FCR;
	UL QSPI_DSR;

} QSPI_REG_TYPE;
#define QSPI_0 0
#define QSPI_1 1
typedef union {
	struct {
		UC CSR_LSB; //Enable,Abort request,FTh
		UC CSR_CsIE; //Chip select ,interrupt enable,AMPS and PMM
		US CSR_Prescalar;
		UC CSR_Flag; //Flags
		UC CSR_FLevel;
		US dummy;
	} Field;

	UL value;
} CSR_CONFG_TYPE;

typedef union {
	struct {
		US DCR_ModeCHST :4, //level that Sclk takes between commands and Chip Select High Time
				DCR_FSize :5, //Flash memory size
				dummy1 :7;
		US dummy2;
		UI dummy3;
	} Field;

	UL value;
} DCR_CONFG_TYPE;

//Register address mapping
#define QSPIReg(i) (*((volatile QSPI_REG_TYPE *)(QSPI_BASE_ADDR+ (0x100 * i))))



/*  Function declaration section
 *
 *
 ***************************************************/

void Qspi_initialise(UC qspi_number);
void Qspi_read_flash_register(UC qspi_number, UL address, UI dataLength,
		UC command, UC instr_line, UC data_line, UC *read_data);

void Qspi_instrTxt(UC qspi_number, UC instr_line, UC command);

void Qspi_write_flash_register(UC qspi_number, UL address, UI dataLength,
		UC command, UC instr_line, UC data_line, UC wr_data);

void Qspi_mem_write(UC qspi_number, UL Address, UI DataLength, UC command,
		UC instr_line, UC data_line, UC data_size, UC address_line,
		UC address_size, UC fifo_threshold, UC *write_data);

void Qspi_mem_read(UC qspi_number, UL Address, UI DataLength, UC command,
		UC instr_line, UC data_line, UC data_size, UC address_line,
		UC address_size, UC fifo_threshold, UC *read_data);

UC QSPI_wait_if_busy(UC qspi_number);



void FlashReadId(UC qspi_number);
void Board_setup(UC qspi_number);
void qspi_delay(UL count);


//void (*spi_handle_rx_intr)(void);  
//void (*spi_handle_tx_intr)(void);

#endif	/* _SPI_H */	

