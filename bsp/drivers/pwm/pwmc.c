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
#include <include/interrupt.h>

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

/** @fn PWMC_Set_mode
 * @brief 
 * @details 
 * @warning
 * @param[in] unsigned char channel_no- The channel number to which device is connected (It can be from 0 to 7),
	      unsigned char mode- 00 : PWM Idle, 01: One short mode, 10: Continuous mode, 11: Reserved for future use.
 * @param[Out] No output parameter
*/
void PWMC_Set_mode(UC channel_no,UC mode)
{
	gPWMCtransfer.Value = PWMCreg(channel_no).Control.word;
	gPWMCtransfer.Bits.Mode = mode;
	PWMCreg(channel_no).Control.word = gPWMCtransfer.Value;
	__asm__ __volatile__ ("fence");
	return;
}

/** @fn PWMC_Set_alignment
 * @brief 
 * @details 
 * @warning
 * @param[in] unsigned char channel_no- The channel number to which device is connected (It can be from 0 to 7),
	      unsigned char align- 00: Left alignment, 01: Right alignment. 10,11: Reserved for future use.
 * @param[Out] No output parameter
*/
void PWMC_Set_alignment(UC channel_no,UC align)
{
	gPWMCtransfer.Value = PWMCreg(channel_no).Control.word;
	gPWMCtransfer.Bits.AC = align;
	PWMCreg(channel_no).Control.word = gPWMCtransfer.Value;
	__asm__ __volatile__ ("fence");
	return;
}

/** @fn PWMC_Set_alignment
 * @brief 
 * @details 
 * @warning
 * @param[in] unsigned char channel_no- The channel number to which device is connected (It can be from 0 to 7),
	      unsigned short  repeatCount- Repeat count for the PWM cycle.
 * @param[Out] No output parameter
*/
void PWMC_Set_RepeatCount(UC channel_no,US repeatCount)
{
	gPWMCtransfer.Value = PWMCreg(channel_no).Control.word;
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

/** @fn pwmc_register_isr
 * @brief  Register PWMC isr
 * @details 
 * @warning
 * @param[in] unsigned char pwmc_ch_number: The channel number to which device is connected (It can be from 0 to 7),
	      function pointer to the pwmc isr().
 * @param[Out] No output parameter
*/
void pwmc_register_isr(UC pwmc_ch_number,void (*pwmc_isr)())
{
    	UC irq_no;
#if __riscv_xlen == 64
	if(pwmc_ch_number == 0)
		irq_no = 54;
	else if(pwmc_ch_number == 1)
		irq_no = 55;
	else if(pwmc_ch_number == 2)
		irq_no = 56;
	else if(pwmc_ch_number == 3)
		irq_no = 57;
	else if(pwmc_ch_number == 4)
		irq_no = 58;
	else if(pwmc_ch_number == 5)
		irq_no = 59;
	else if(pwmc_ch_number == 6)
		irq_no = 60;
	else if(pwmc_ch_number == 7)
		irq_no = 61;
#else
	if(pwmc_ch_number == 0)
		irq_no = 24;
	else if(pwmc_ch_number == 1)
		irq_no = 25;
	else if(pwmc_ch_number == 2)
		irq_no = 26;
	else if(pwmc_ch_number == 3)
		irq_no = 27;
	else if(pwmc_ch_number == 4)
		irq_no = 28;
	else if(pwmc_ch_number == 5)
		irq_no = 29;
	else if(pwmc_ch_number == 6)
		irq_no = 30;
	else if(pwmc_ch_number == 7)
		irq_no = 31;
#endif
	interrupt_enable(irq_no);		//Enable interrupt in controller.
    	irq_register_handler(irq_no, pwmc_isr);
}

/** @fn pwmc_ch0_intr_handler
 @brief PWMC channel 0 isr
 @details 
 @warning
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void pwmc_ch0_intr_handler(void){

    UI intr_status=PWMCreg(0).Status;
    printf("\n\rIn PWMC Handler:0x ");
    if(intr_status & 0x02) {
		//USER CAN ADD THEIR CODE HERE.
		printf("\n\rPWMC CH0 INTR");
    }
}


/** @fn pwmc_ch1_intr_handler
 @brief PWMC channel 1 isr
 @details 
 @warning
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void pwmc_ch1_intr_handler(void){

    UI intr_status=PWMCreg(1).Status;
    printf("\n\rIn PWMC Handler:0x ");
    if(intr_status & 0x02) {
		//USER CAN ADD THEIR CODE HERE.
		printf("\n\rPWMC CH1 INTR");
    }
}


/** @fn pwmc_ch2_intr_handler
 @brief PWMC channel 2 isr
 @details 
 @warning
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void pwmc_ch2_intr_handler(void){

    UI intr_status=PWMCreg(2).Status;
    printf("\n\rIn PWMC Handler:0x ");
    if(intr_status & 0x02) {
		//USER CAN ADD THEIR CODE HERE.
		printf("\n\rPWMC CH2 INTR");
    }
}


/** @fn pwmc_ch3_intr_handler
 @brief PWMC channel 3 isr
 @details 
 @warning
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void pwmc_ch3_intr_handler(void){

    UI intr_status=PWMCreg(3).Status;
    printf("\n\rIn PWMC Handler:0x ");
    if(intr_status & 0x02) {
		//USER CAN ADD THEIR CODE HERE.
		printf("\n\rPWMC CH3 INTR");
    }
}


/** @fn pwmc_ch4_intr_handler
 @brief PWMC channel 4 isr
 @details 
 @warning
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void pwmc_ch4_intr_handler(void){

    UI intr_status=PWMCreg(4).Status;
    printf("\n\rIn PWMC Handler:0x ");
    if(intr_status & 0x02) {
		//USER CAN ADD THEIR CODE HERE.
		printf("\n\rPWMC CH4 INTR");
    }
}


/** @fn pwmc_ch5_intr_handler
 @brief PWMC channel 5 isr
 @details 
 @warning
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void pwmc_ch5_intr_handler(void){

    UI intr_status=PWMCreg(5).Status;
    printf("\n\rIn PWMC Handler:0x ");
    if(intr_status & 0x02) {
		//USER CAN ADD THEIR CODE HERE.
		printf("\n\rPWMC CH5 INTR");
    }
}


/** @fn pwmc_ch6_intr_handler
 @brief PWMC channel 6 isr
 @details 
 @warning
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void pwmc_ch6_intr_handler(void){

    UI intr_status=PWMCreg(6).Status;
    printf("\n\rIn PWMC Handler:0x ");
    if(intr_status & 0x02) {
		//USER CAN ADD THEIR CODE HERE.
		printf("\n\rPWMC CH6 INTR");
    }
}

/** @fn pwmc_ch7_intr_handler
 @brief PWMC channel 7 isr
 @details 
 @warning
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void pwmc_ch7_intr_handler(void){

    UI intr_status=PWMCreg(7).Status;
    printf("\n\rIn PWMC Handler:0x ");
    if(intr_status & 0x02) {
		//USER CAN ADD THEIR CODE HERE.
		printf("\n\rPWMC CH7 INTR");
    }
}

