/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  timer.c
 * Brief Description of file             :  Driver to control the GPIO.
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

#include "stdlib.h"
#include "timer.h"
#include "config.h"




/** @fn timer_put_delay
 * @brief  load, enable and wait for interrupt (Polling mode).
 * @details The selected timer is loaded with the no of clocks and it is enabled with intr unmasked. The timer module waits untill it interrupts.
 * @warning 
 * @param[in] unsigned char, unsigned int
 * @param[Out] Returns 1 when interrupt is generated.
*/
UC timer_put_delay(UC timer_no, UI no_of_clocks) {

	UI wEOI;
	Timer(timer_no).Control = 0x0;			// Disable timer.
	Timer(timer_no).LoadCount = no_of_clocks;	// Load timer with no of clocks.
	Timer(timer_no).Control = 0x03;			// Enable timer with unmasked intr.

	while(Timer(timer_no).IntrStatus != 1); 	// Wait for interrupt status bit to set.
	wEOI = Timer(timer_no).EOI;			// Reads the EOI register to clear the intr.
	return 1;
}



/** @fn timer_get_current_value
 * @brief  Get the current timer value.
 * @details The current value of timer is returned.
 * @warning 
 * @param[in] unsigned char
 * @param[Out] The current value of timer.
*/
UI timer_get_current_value(UC timer_no) {

	UI current_val = 0;	
	current_val = Timer(timer_no).CurrentValue;
	return current_val;   
}



/** @fn timer_unmask_intr
 * @brief  Enable timer to interrupt.
 * @details The selected timer interrupt is enabled.
 * @warning 
 * @param[in] unsigned char
 * @param[Out] No output parameter.
*/
void timer_unmask_intr(UC timer_no) {

	Timer(timer_no).Control = (0 << 2);
	return;   
}

/** @fn timer_load
 * @brief  Load timer with the value.
 * @details The selected timer loaded with the count value.
 * @warning 
 * @param[in] unsigned char, unsigned int
 * @param[Out] No output parameter.
*/
void timer_load(UC timer_no,UI count) {
	
	Timer(timer_no).LoadCount = count;	// Load timer with no of clocks.
	return;   
}


/** @fn timer0_intr_handler
 * @brief  timer 0 intr handler.
 * @details The function will execute the steps as described in routine
 * @warning 
 * @param[in] unsigned char, unsigned int
 * @param[Out] No output parameter.
*/
void timer0_intr_handler(void) {

	return;   
}


/** @fn timer1_intr_handler
 * @brief  timer 1 intr handler.
 * @details The function will execute the steps as described in routine
 * @warning 
 * @param[in] unsigned char, unsigned int
 * @param[Out] No output parameter.
*/
void timer1_intr_handler(void) {

	return;   
}


/** @fn timer2_intr_handler
 * @brief  timer 2 intr handler.
 * @details The function will execute the steps as described in routine
 * @warning 
 * @param[in] unsigned char, unsigned int
 * @param[Out] No output parameter.
*/
void timer2_intr_handler(void) {

	return;   
}




