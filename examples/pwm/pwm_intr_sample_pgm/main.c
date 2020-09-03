

/***************************************************
* Module name: main.c
*
* Copyright 2020 Company CDAC(T)
* All Rights Reserved.
*
*  The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
*
*
* Module Description:
* SPI test pgm
*
***************************************************/

/*  Include section
*
*
***************************************************/
#include "pwmc.h"
#include "stdlib.h"
#include "config.h"
#include "debug_uart.h"



void pwmc_channel_one_short_mode_with_intr(UC opc,UC channel_no)
{
	UC rx = 0;
	PWMC_Set_Period(channel_no,10);
	PWMC_Set_OnOffTime(channel_no,4);
	PWMC_init(channel_no,PWM_ONE_SHORT_MODE,PWM_RIGHT_ALIGN,PWM_LOC_INTR_EN,opc,PWM_REPEAT_COUNT);

	PWMC_Enable_with_intr();

	while(1){
	}
}


/** @fn main
 * @brief PWMC sample program using interrupt.
 * @details 
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main (void)
{
	UC rx = 0;
	UL selection;

	printf("\n\rPWMC INTR SAMPLE PGM ");
	printf("\n\r*********************** ");
	pwmc_register_isr(PWM_CH_0, pwmc_ch0_intr_handler);
	pwmc_channel_one_short_mode_with_intr(PWM_OPC_HIGH,PWM_CH_0);
	while(1);

}




