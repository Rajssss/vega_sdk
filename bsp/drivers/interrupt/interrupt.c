/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  interrupt.c
 * Brief Description of file             :  Driver to control the Interrupt.
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
#include <include/interrupt.h>
#include <include/timer.h>
#include <include/config.h>
#include <include/encoding.h>

#if __riscv_xlen == 64
#define MAXIMUM_INTR_COUNT 64
#else
#define MAXIMUM_INTR_COUNT 32
#endif

#define read_const_csr(reg) ({ unsigned long __tmp; \
  asm ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })


extern volatile UL INTERRUPT_Handler_0;
fp irq_table[64]; //Array of Function pointer.


/** @fn    enable_irq
  @brief   Enable processor interrupt and Global interrupt in machine mode.
  @details The function "set_csr" will set the interrupt bit in MIE register and Machine mode External interrupt in MSTATUS register.
  @warning
  @param[in]  No input parameter.
  @param[Out] No output parameter.
*/
void enable_irq(void) {
    set_csr(mie, MIP_MEIP);			// Set MEIE bit in MIE register for Machine External Intr.
    set_csr(mstatus, MSTATUS_MIE);		// Set global machine intr bit (3rd bit) in MSTATUS register.
#if __riscv_xlen == 64
	//For 64 Bit processors		
    write_csr(mtvec,(UL)&INTERRUPT_Handler_0);		// Set MTVEC register with vector address.
#else
	//For32 Bit processors
    write_csr(mtvec,(UI)&INTERRUPT_Handler_0);		// Set MTVEC register with vector address.
#endif
}

/** @fn interrupt_enable
  @brief  Enable interrupt in controller.
  @details The interrupt enable register is set with the enable value of peripheral selected.
  @warning 
  @param[in] unsigned char intr_number: The number at which the periphral will interrupt
  @param[Out] No output parameter.
*/

void interrupt_enable(UC intr_number)
{
	enable_irq();	// Enable global interrupt and external interrupt of the processor.
	intr_regs.INTR_EN |= ((UL)1 << intr_number);	// Enable interrupt for peripheral in interrupt controller.
	__asm__ __volatile__ ("fence");
}

 
/** @fn irq_register_handler
 @brief  Initialise peripheral interrupt handler to a table.
 @details Enable processor interrupt and Global interrupt in machine mode  and init irq_table.
 @warning 
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void irq_register_handler(UC irq_no, void (*irq_handler)()){///*irq_handler is function pointer to user defined intr handler
    	irq_table[irq_no] = irq_handler;
}


/** @fn interrupt_handler
 @brief  Invoke the peripheral interrupt handler.
 @details The interrupt controller's status register is read to identify the interrupted peripheral and then the corresponding
	  handler for the peripheral is invoked.
 @warning 
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/

void interrupt_handler(uintptr_t cause, uintptr_t epc, uintptr_t regs[32]){

	UL intr_status = intr_regs.INTR_STATUS; 		// Read interrupt status register.

	printf("%x\n",intr_status);
	
	/*

	printf("\n\rTRAP\n\r");
	printf("EPC : %lx\n\r",epc);
	printf("Cause : %lx\n\r",cause);
	printf("badaddress: %lx\n\r",read_const_csr(mbadaddr));
	for(int i=0;i<32;i++)
		printf("reg %d : %lx\n\r",i,regs[i]);*/

	

	for(UL i = 0; i < MAXIMUM_INTR_COUNT ; i++) 
	{
		if ((intr_status >> i) & (UL)1){
			//printf("\nINTR if %d",i);
			irq_table[i]();		// Invoke the peripheral handler as function pointer.
			//printf("\nINTR if done");
		}

	}
	//printf("\nINTR handler return");
}

