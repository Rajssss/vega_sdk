/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  adc.c
 * Brief Description of file             :  Driver to control the ADC.
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
#include <include/adc.h>
#include <include/config.h>




/* @fn adc_analogRead
  @brief  Enable external interrupt.
  @details The selected timer is loaded with the no of clocks and it is enabled with intr unmasked. The timer module waits untill it interrupts.
  @warning 
  @param[in] unsigned char adc_channel_number: The channel number from where adc value to be read.
  @param[Out] unsigned int : read adc data..
*/

UI adc_analogRead(UC adc_channel_number)
{
	UI adc_data = 0;
	if((adc_channel_number >= 0) && (adc_channel_number <= 3))
	{
		switch (adc_channel_number)
		{
			case 0:
				ADCReg.address_reg = 0x14;
				while((ADCReg.status_reg & 0x1) != 0x1);
				adc_data = ADCReg.data_reg;
				break;
			case 1:
				ADCReg.address_reg = 0x15;
				while((ADCReg.status_reg & 0x1) != 0x1);
				adc_data = ADCReg.data_reg;
				break;
			case 2:
				ADCReg.address_reg = 0x16;
				while((ADCReg.status_reg & 0x1) != 0x1);
				adc_data = ADCReg.data_reg;
				break;
			case 3:
				ADCReg.address_reg = 0x17;
				while((ADCReg.status_reg & 0x1) != 0x1);
				adc_data = ADCReg.data_reg;
				break;
			default:
				break;
		}
		return adc_data;
	}
}

 
