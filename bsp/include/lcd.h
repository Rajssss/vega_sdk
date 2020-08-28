
#ifndef LCD_H_
#define LCD_H_



/*  Include section
*
***************************************************/


/*  Defines section
*


***************************************************/
#define LOW		0
#define HIGH		1

#define LCD_CLEAR_DISP_CMD			(0x1<<0)
#define LCD_RET_HOME_CMD			(0x1<<1)
#define LCD_ENTRY_MODE_SET_RIGHT_CMD		(0x5<<0)	 // SHIFT DISPLAY TO RIGHT
#define LCD_ENTRY_MODE_SET_LEFT_CMD		(0x7<<0)	 // SHIFT DISPLAY TO LEFT
#define LCD_FUN_SET_8_CMD			(0x30<<0)	 // Data transferred with 8-bit length (DB7 - DB0).
#define LCD_FUN_SET_4_CMD			(0x20<<0)	 // Data transferred with 4-bit length (DB7 - DB4).
	
#define LCD_DISP_ON				(0xC<<0)
#define LCD_DISP_OFF				(0x8<<0)

#define LCD_CURSOR_ON				(0xA<<0)	
#define LCD_CURSOR_OFF				(0x8<<0)

#define LCD_CURSOR_BLINK_ON			(0x9<<0)
#define LCD_CURSOR_BLINK_OFF			(0x8<<0)				

/*  Function declarations
*
***************************************************/

#endif /* LCD_H_ */
