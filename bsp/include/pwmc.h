#ifndef _PWMC_H
#define _PWMC_H


/*  Include section
* 
*
***************************************************/

#include "stdlib.h"


#define PWMC_BASE_ADDR 	0x10400000


#define PWM_CH_0			0
#define PWM_CH_1			1
#define PWM_CH_2			2
#define PWM_CH_3			3
#define PWM_CH_4			4
#define PWM_CH_5			5
#define PWM_CH_6			6
#define PWM_CH_7			7

#define REPEAT_COUNT		5

#define PWM_IDLE_MODE				(0)
#define PWM_ONE_SHORT_MODE			(1)
#define PWM_CONTINUOUS_MODE			(2)

#define PWM_LEFT_ALIGN				(0)
#define PWM_RIGHT_ALIGN				(1)

#define PWM_LOC_INTR_DIS			(0)
#define PWM_LOC_INTR_EN				(1)

#define PWM_OPC_LOW					(0)
#define PWM_OPC_HIGH				(1)

#define PWM_REPEAT_COUNT			(REPEAT_COUNT)

#define PWM_GPE						(1<<0)
#define PWM_GIE						(1<<1)



typedef struct
{

	union
	{
		struct
		{
			UI 	Mode 		: 2,
				AC 		: 2,
				IE 		: 1,
				OPC 		: 1,
				RepeatCount	: 16,
				Rsvd  		: 10;
		}__attribute__((packed)) Bits;
		UI word;
	}Control; 					//0x00
	UI Status; 					//0x04
	UI Period;					//0x08
	UI On_Off;					//0x0c
}PWMCregType;



typedef union
{
	struct
	{
		UI 	Mode 		: 2,
			AC 		: 2,
			IE 		: 1,
			OPC 		: 1,
			RepeatCount	: 16,
			Rsvd  		: 10;
	}Bits;
	UI Value;
}PWMcntrlRegType;


#define PWMC_GCR_REG		(PWMC_BASE_ADDR + 0x80)
#define PWMCreg(n) (*((volatile PWMCregType *)(PWMC_BASE_ADDR +  (n * 0x10))))


/*  Function declaration section
* 
*
*
***************************************************/
void PWMC_Set_Period(UC channel_no, UI period);
void PWMC_Set_OnOffTime(UC channel_no, UI time);
void PWMC_init(UC channel_no,UC mode,UC align,UC intr_en_dis,UC opc, US repeatCount);
void PWMC_Configure(UC channel_no, UI cword);
void PWMC_Enable(void);
void PWMC_Enable_with_intr(void);
void PWMC_Disable(void);
void pwmc_all_channel_idle_mode(UC opc);
void pwmc_all_channel_continuous_mode(UC opc);
void pwmc_all_channel_continuous_disable_mode(UC opc);
void pwmc_one_short_mode_left_aligned(UC opc);
void pwmc_one_short_mode_right_aligned(UC opc);
void pwmc_one_short_mode_left_align_custom_repeat(UC opc,US repeat_count);
void pwmc_one_short_mode_right_align_custom_repeat(UC opc,US repeat_count);
void pwmc_channel_one_short_mode_with_intr(UC opc,UC channel_no);
void pwmc_register_isr(UC pwmc_ch_number,void (*pwmc_isr)());
void pwmc_ch0_intr_handler(void);

#endif	/* _PWMC_H */	





