/*****************************************************************************

 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 07-Nov-2019
 Filename		: config.h
 Purpose		: Configuration for different peripherals
 Description		: Base address/configuration for peripherals 
 Author(s)		: Premjith A V
 Email			: premjith@cdac.in
    
 See LICENSE for license details.
******************************************************************************/


#ifndef CONFIG_H_
#define CONFIG_H_

#define	UART_BASE				0x10000100
#define SPI_BASE_ADDR				0x10000600
#define GPIO_0_BASE_ADDRESS			0x10080000
#define GPIO_1_BASE_ADDRESS			0x10180000



#define CONCATENATE(X) #X
#define CONCAT(X) CONCATENATE(X)


#endif /* CONFIG_H_ */
