/***************************************************
 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 08-Nov-2019
 Filename		: uart_tx_rx.c
 Purpose		: UART interface
 Description		: transmission & reception with uart interface
 Author(s)		: Karthika P
 Email			: karthikap@cdac.in

 See LICENSE for license details.
 ***************************************************/
/**
 @file uart_tx_rx.c.c
 @brief Contains routines for UART interface
 @detail Includes software functions to initialize,
 configure, transmit and receive over UART
 */
/*  Include section
 ***************************************************/

#include "uart.h"
#include "stdlib.h"
#include "config.h"
#include "gpio.h"
#include <string.h>

int send_string(char * str)
{
char error;
  while(*str!='\0'){
	 uart_putchar(UART_1,*str, &error);
	if(*str=='\n')
	 uart_putchar(UART_1,'\r', &error);
	str++;
  }
  return 0;
}

void receive_string(char * str)
{
  char error;  
  char data;

  while(1){
	 data = uart_getchar(UART_1, &error);	
	 *str=data;
	  str++;
	 if(data=='\n'){	
	 *str='\r';	
	 break;
	}	
  }
}



/**
 @fn main
 @brief transmit and reception through uart
 @details 1 character is transmitted and received through uart
 @param[in] No input parameter.
 @param[Out] No ouput parameter.
 @return Void function.

 */
void main() {
	char error;       
	char str[100]={0,};

	printf("Setting up Bluetooth Device \n\r");
	uart_set_baud_rate(UART_1,9600,40000000);

while(1){
		memset(str,0,sizeof(str));
		receive_string(str);	
		printf("%s", str);
		if(strncmp(str,"ON",2)==0)
		{	
			GPIO_write_pin(22,ON_LED);
			send_string("LED ON\n");
		}
		else
		{
			send_string("LED OFF\n");
			GPIO_write_pin(22,OFF_LED);
		}		
		
	}
	
	
}

