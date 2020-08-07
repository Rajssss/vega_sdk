
#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_



/*  Include section
*
***************************************************/


/*  Defines section
*


***************************************************/
#define PIN_0			0x1
#define PIN_1			0x2
#define PIN_2			0x4
#define PIN_3			0x8

#define PIN_4			0x10
#define PIN_5			0x20
#define PIN_6			0x40
#define PIN_7			0x80

#define PIN_8			0x100
#define PIN_9			0x200
#define PIN_10			0x400
#define PIN_11			0x800

#define PIN_12			0x1000
#define PIN_13			0x2000
#define PIN_14			0x4000
#define PIN_15			0x8000

#define GPIO_0			0
#define GPIO_1			1

/*  Function declarations
*
***************************************************/

US GPIO_read_pin(US pin_no);
void GPIO_write_pin(US pin_no,US data);

#endif /* GPIO_DRIVER_H_ */
