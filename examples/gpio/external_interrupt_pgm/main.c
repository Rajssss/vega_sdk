/*****************************************************************************

 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 07-Jul-2020
 Filename		: main.c
 Purpose		: Proximity sensor program
 Description		: Proximity sensor program using gpio
 Author(s)		: Premjith A V
 Email			: premjith@cdac.in
    
 See LICENSE for license details.
******************************************************************************/

#include "stdlib.h"
#include "config.h"
#include "gpio.h"
#include "uart.h"
#include "interrupt.h"


/** @fn gpio_intr_handler
  @brief  gpio 0 intr handler.
  @details The function will execute the steps as described in routine
  @warning 
  @param[in] unsigned char, unsigned int
  @param[Out] No output parameter.
*/
void gpio_intr_handler(void) {

	printf("External GPIO interrupt handler\n");
	// User can add their code for GPIO 0 interrupt.
	return;   
}

/** @fn main
 * @brief Proximity sensor program
 * @details Proximity sensor program
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main ()
{	

		printf("\n\r ***************************************************************************");
		printf("\n\r INFO: Connect any sensor to GPIO 0 ");				
		printf("\n\r ***************************************************************************");		
		
		irq_register_handler(GPIO_0_IRQ, gpio_intr_handler);

		interrupt_enable(GPIO_0_IRQ);

		while(1);
	
}




