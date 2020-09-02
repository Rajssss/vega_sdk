/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  pwmc.c
 * Brief Description of file             :  Driver for PWM controller.
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
#include <include/pwmc.h>
#include <include/config.h>

PWMcntrlRegType gPWMCtransfer;


/** @fn PWMC_Set_Period
 * @brief PWM cycle duration.
 * @details 
 * @warning
 * @param[in] unsigned char channel_no: The channel number to which device is connected (It can be from 0 to 7),
	      unsigned int period: Minimum value supported is 2. Maximum value supported 2^32 – 1.
 * @param[Out] No output parameter
*/


void PWMC_Set_Period(UC channel_no, UI period)
{
	PWMCreg(channel_no).Period = period;
	__asm__ __volatile__ ("fence");
	return;
}


/** @fn PWMC_Set_OnOffTime
 * @brief Defined as pulse duration in a PWM cycle
 * @details When Alignment register is set for left alignment this register
	    represents on time or high time of the PWM signal.

	    When Alignment register is set for right alignment this register
	    represents off time or low time of the PWM signal.
 * @warning
 * @param[in] unsigned char channel_no: The channel number to which device is connected (It can be from 0 to 7),
	      unsigned int time: Minimum value supported is 1. Maximum value supported 2^32 – 1.
 * @param[Out] No output parameter
*/


void PWMC_Set_OnOffTime(UC channel_no, UI time)
{
	PWMCreg(channel_no).On_Off = time;
	__asm__ __volatile__ ("fence");
	return;
}


/** @fn PWMC_Set_OnOffTime
 * @brief 
 * @details 
 * @warning
 * @param[in] unsigned char channel_no- The channel number to which device is connected (It can be from 0 to 7),
	      unsigned char mode- 00 : PWM Idle, 01: One short mode, 10: Continuous mode, 11: Reserved for future use.
	      unsigned char align- 00: Left alignment, 01: Right alignment. 10,11: Reserved for future use.
	      unsigned char intr_en_dis- 0 - Disable interrupt, 1 - Enable interrupt.
	      unsigned char opc- 0: Output level is Low in idle mode,1: Output level is High in idle mode
	      unsigned short  repeatCount- Repeat count for the PWM cycle.
 * @param[Out] No output parameter
*/

void PWMC_init(UC channel_no,UC mode,UC align,UC intr_en_dis,UC opc, US repeatCount)
{
	PWMCreg(channel_no).Control.word = 0;
	gPWMCtransfer.Bits.Mode 	= mode;
	gPWMCtransfer.Bits.AC 		= align;
	gPWMCtransfer.Bits.IE		= intr_en_dis;
	gPWMCtransfer.Bits.OPC		= opc;
	gPWMCtransfer.Bits.RepeatCount	= repeatCount;

	PWMCreg(channel_no).Control.word = gPWMCtransfer.Value;
	__asm__ __volatile__ ("fence");
	return;
}


/** @fn PWMC_Enable
 * @brief  Enale PWM.
 * @details 
 * @warning
 * @param[in] No input parameter
 * @param[Out] No output parameter
*/
void PWMC_Enable(void)
{
	UI *ptrPWM_Global_Ctrl = (UI*)PWMC_GCR_REG;
	*ptrPWM_Global_Ctrl = 0;
	*ptrPWM_Global_Ctrl = PWM_GPE;
	__asm__ __volatile__ ("fence");
	return;
}


/** @fn PWMC_Enable_with_intr
 * @brief 
 * @details 
 * @warning
 * @param[in] No input parameter
 * @param[Out] No output parameter
*/

void PWMC_Enable_with_intr(void)
{
	UI *ptrPWM_Global_Ctrl = (UI*)PWMC_GCR_REG;
	*ptrPWM_Global_Ctrl = 0;
	*ptrPWM_Global_Ctrl = (PWM_GPE|PWM_GIE);
	__asm__ __volatile__ ("fence");
	return;
}



/** @fn PWMC_Enable_with_intr
 * @brief  Disable interrupt
 * @details 
 * @warning
 * @param[in] No input parameter
 * @param[Out] No output parameter
*/

void PWMC_Disable(void)
{
	UI *ptrPWM_Global_Ctrl = (UI*)PWMC_GCR_REG;
	*ptrPWM_Global_Ctrl = (0<<0);
	__asm__ __volatile__ ("fence");
	return;
}

