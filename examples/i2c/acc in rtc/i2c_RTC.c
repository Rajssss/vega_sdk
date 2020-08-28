/***************************************************


 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 08-Nov-2019
 Filename		: i2c_RTC.c
 Purpose		: I2C RTC interface
 Description		: Sample RTC with I2C interface
 Author(s)		: Karthika P
 Email			: karthikap@cdac.in

 See LICENSE for license details.
 ***************************************************/

/**
 @file i2c_EEPROM.c
 @brief contains routines for I2C EEPROM interface
 @detail Includes software functions declarations to initialize,
 configure, write and read EEPROM over I2C interface
 */

#include "i2c.h"
#include "stdlib.h"
#include "ds3231_rtc.h"
#include "adxl345.h"

//RTC_TIME gRTCtime;
/**
 @fn main
 @brief writes and reads EEPROM with I2C interface
 @details Initializes configures I2C to write, read and compare data in EEPROM
 @param[in] No input parameters.
 @param[Out] No ouput parameter.
 @return Void function.

 */
void main() {
	//UC rxd_data[7];
	printf("I2C acc \n\r");
	i2c_configure(0, 40000000, 100000); //System clock =40MHz and I2C clock =100 kHz
	//i2c_initialize(0);

	i2c_set_rtc_DS3231(0, ADXL345_REG_POWER_CTL, ADXL345_I2C_ADDR_WR);
	printf("write completed acc\n\r");
	i2c_get_rtc_DS3231(0, ADXL345_I2C_ADDR_WR,
			ADXL345_I2C_ADDR_RD, ADXL345_REG_POWER_CTL);
	i2c_ADXL345_set_range(0, ADXL345_I2C_ADDR_WR,ADXL345_RANGE_2_G,ADXL345_REG_DATA_FORMAT);
	//while(1);


	while (1) {
		i2c_get_rtc_DS3231(0, ADXL345_I2C_ADDR_WR,
					ADXL345_I2C_ADDR_RD, ADXL345_REG_DATAX0);


		}
	}

	//printf("success \n\r");
	//while (1)
	//;



/**
 @fn i2c_set_rtc_DS3231
 @brief set rtc with i2c interface
 @details write data after writing slave address and word address
 @param[in] unsigned char(i2c_number--which i2c to be used)
 @param[in] unsigned short (RTC_Address--word RTC_Address)
 @param[in] unsigned short (Slave_Address_Wr--Slave address for write)
 @param[Out] No ouput parameter.
 @return Void function.

 */
void i2c_set_rtc_DS3231(UC i2c_num, UC RTC_Address, UC Slave_Address_Wr) {


	static UC acc;
	acc=0x8;

	while (1) {
		i2c_start(i2c_num, 0x00, 0);

		if (i2c_data_write(i2c_num, &Slave_Address_Wr, 01)) { //writes slave address -68 and set i2c to write mode

			continue; //received NACK
		}

		if (i2c_data_write(i2c_num, &RTC_Address, 01)) { //writes Time calc address 00

			continue; //received NACK
		}

		if (i2c_data_write(i2c_num, &acc, 01)) { //writes data

			continue; //received NACK
		}

		i2c_stop(i2c_num);
		break;
	}
}

/**
 @fn i2c_get_rtc_DS3231
 @brief read rtc with I2C interface
 @details read  data after writing slave address and rtc address
 @param[in] unsigned char(i2c_num--which i2c to be used)
 @param[in] unsigned char (Slave_Address_Wr--Slave address for write)
 @param[in] unsigned char (Slave_Address_Rd--Slave address for read)
 @param[in] unsigned short (RTC_Address--starting word address)
 @param[in] unsigned long (read_data_length--no:of bytes to be read)
 @param[Out] nil
 @return Void function.

 */

void i2c_get_rtc_DS3231(UC i2c_num, UC Slave_Address_Wr,
		UC Slave_Address_Rd, UC RTC_Address) {

	static UC acc[1];        //second,minute,hour,dow,day,month,year

	while (1) {
		i2c_start(i2c_num, 0x00, 0);

		if (i2c_data_write(i2c_num, &Slave_Address_Wr, 01)) { //writes slave address

			continue; //received NACK
		}
		//printf("Slave address ACK\n\r");
		if (i2c_data_write(i2c_num, &RTC_Address, 01)) { //writes MSB of address

			continue; //received NACK
		}
		//printf("Word address  ACK\n\r");
		i2c_stop(i2c_num);

		i2c_start(i2c_num, 01, 01); //start sequence for reading data
		if (i2c_data_write(i2c_num, &Slave_Address_Rd, 01)) { //write slave address and set rtc to read mode

			continue; //received NACK
		}
		//printf("Slave address read ACK\n\r");

		i2c_data_read(i2c_num, acc, 1);

		printf("Time Data %x", acc[0]);


		break;

	}

}

/**
 @fn DecToBcd
 @brief decimal to bcd
 @details converts decimal to bcd
 @param[in] int(val--data to be converted)
 @param[Out] nil
 @return unsigned char(converted bcd number)

 */
UC DecToBcd(UC val) {
	return (UC) (((val / 10) * 16) + (val % 10));
}
/**
 @fn BcdToDec
 @brief bcd to decimal
 @details converts bcd to decimal
 @param[in] Unsigned char(val--data to be converted)
 @param[Out] nil
 @return unsigned char(converted bcd number)

 */

UC BcdToDec(UC val) {
	return (UC) (((val / 16 )* 10) + (val % 16));
}
/**
 @fn i2c_ADXL345_set_range
 @brief set range of adxl345 with I2C interface
 @details read  acceleration from adxl345 after writing slave address and Adxl_Address
 @param[in] unsigned char(i2c_num--which i2c to be used)
 @param[in] unsigned char (Slave_Address_Wr--Slave address for write)
 @param[in] enum range_t
 @param[Out] No ouput parameter.
 @return unsigned short.

 */
void i2c_ADXL345_set_range(UC i2c_num, UC Slave_Address_Wr,range_t range,UC Adxl_Address) {
  /* Read the data format register to preserve bits */
  UC format;
  while (1) {
  			i2c_start(i2c_num, 0x00, 0);

  			if (i2c_data_write(i2c_num, &Slave_Address_Wr, 01)) { //writes slave address

  				continue; //received NACK
  			}
  			//printf("Slave address ACK\n\r");
  			if (i2c_data_write(i2c_num, &Adxl_Address, 01)) { //writes MSB of address

  				continue; //received NACK
  			}
  			//printf("Word address  ACK\n\r");
  			i2c_stop(i2c_num);

  			i2c_start(i2c_num, 02, 01); //start sequence for reading data
  			if (i2c_data_write(i2c_num, &Adxl_Address, 01)) { //write slave address and set rtc to read mode

  				continue; //received NACK
  			}
  			//printf("Slave address read ACK\n\r");

  			i2c_data_read(i2c_num, &format, 1);

  			break;

  		}
  printf("\n\rformat %x",format);
  /* Update the data rate */
  format &= ~0x0F;
  format |= range;

  /* Make sure that the FULL-RES bit is enabled for range scaling */
  format |= 0x08;

  /* Write the register back to the IC */


  while (1) {
  		i2c_start(i2c_num, 0x00, 0);

  		if (i2c_data_write(i2c_num, &Slave_Address_Wr, 01)) { //writes slave address -68 and set i2c to write mode

  			continue; //received NACK
  		}

  		if (i2c_data_write(i2c_num, &Adxl_Address, 01)) { //writes Time calc address 00

  			continue; //received NACK
  		}

  		if (i2c_data_write(i2c_num, &format, 01)) { //writes data

  			continue; //received NACK
  		}

  		i2c_stop(i2c_num);
  		break;
  	}
}
