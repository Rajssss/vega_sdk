/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  interrupt.c
 * Brief Description of file             :  Driver to control the Exxternal Interrupt.
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

fp external_interrupt_table[64];


/* @fn __enable_irq
  @brief  Enable external interrupt.
  @details The selected timer is loaded with the no of clocks and it is enabled with intr unmasked. The timer module waits untill it interrupts.
  @warning
  @param[in] unsigned char intr_number: The number at which the periphral will interrupt
  @param[Out] No output parameter.
*/
void enable_irq(void) {
    set_csr(mie, MIP_MEIP);							// Set MEIE bit in MIE register for Machine External Intr.
    set_csr(mstatus, MSTATUS_MIE);		// Set global machine intr bit (3rd bit) in MSTATUS register.
}

/* @fn external_interrupt_enable
  @brief  Enable external interrupt.
  @details The selected timer is loaded with the no of clocks and it is enabled with intr unmasked. The timer module waits untill it interrupts.
  @warning 
  @param[in] unsigned char intr_number: The number at which the periphral will interrupt
  @param[Out] No output parameter.
*/

void external_interrupt_enable(UC intr_number)
{
	ext_intr_regs.INTR_EN |= (1 << intr_number);
	__asm__ __volatile__ ("fence");
	//ext_intr_enable_reg |= 1 << intr_number;
}

 
/* @fn initialize_external_interrupt_table
 @brief  load, enable and wait for interrupt (Polling mode).
 @details The selected timer is loaded with the no of clocks and it is enabled with intr unmasked. The timer module waits untill it interrupts.
 @warning 
 @param[in] unsigned char, unsigned int
 @param[Out] Returns 1 when interrupt is generated.
*/

void initialize_external_interrupt_table(void)
{
	enable_irq();

#if __riscv_xlen == 64
	write_csr(mtvec,(UL)external_interrupt_handler);
	external_interrupt_table[10] = timer0_intr_handler; 
	external_interrupt_table[11] = timer1_intr_handler; 
	external_interrupt_table[12] = timer2_intr_handler;
#else
	write_csr(mtvec,(UI)external_interrupt_handler);
	external_interrupt_table[7] = timer0_intr_handler; 
	external_interrupt_table[8] = timer1_intr_handler; 
	external_interrupt_table[9] = timer2_intr_handler;
#endif
}

 
/* @fn timer_put_delay
 @brief  load, enable and wait for interrupt (Polling mode).
 @details The selected timer is loaded with the no of clocks and it is enabled with intr unmasked. The timer module waits untill it interrupts.
 @warning 
 @param[in] unsigned char, unsigned int
 @param[Out] Returns 1 when interrupt is generated.
*/
void external_interrupt_handler(void){

	UI intr_status = ext_intr_regs.INTR_STATUS; 


	for(int i = 0; i < 32; i++) 
	{
		if ((intr_status >> i) & 1)
			external_interrupt_table[i]();
	}
}




