/***************************************************


 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 24-Aug-2020
 Filename		: i2c_adxl345.c
 Purpose		: I2C adxl345 interface
 Description		: Sample adxl345 with I2C interface
 Author(s)		: Karthika P
 Email			: karthikap@cdac.in

 See LICENSE for license details.
 ***************************************************/

/**
 @file i2c_adxl345.c
 @brief contains routines for I2C ADXL345 interface
 @detail Includes software functions declarations to initialize,
 configure, write and read ADXL345 over I2C interface
 */

#include "i2c.h"
#include "stdlib.h"
#include "adxl345.h"

/**
 @fn main
 @brief writes and reads adxl345 with I2C interface
 @details Initializes configures I2C to write and read in adxl345
 @param[in] No input parameters.
 @param[Out] No ouput parameter.
 @return Void function.

 */
void main(){
	printf("I2C ADXL345 Accelerometer\n\r");
		i2c_configure(I2C_0, 40000000, 100000); //System clock =40MHz and I2C clock =100 kHz

		i2c_ADXL345_write_register(I2C_0,ADXL345_I2C_ADDR_WR,ADXL345_REG_POWER_CTL,0x08);
	UC status=i2c_ADXL345_read_register(I2C_0,ADXL345_I2C_ADDR_WR,ADXL345_I2C_ADDR_RD,ADXL345_REG_POWER_CTL);
		i2c_ADXL345_set_range(I2C_0, ADXL345_I2C_ADDR_WR,ADXL345_RANGE_2_G,ADXL345_REG_DATA_FORMAT);
while(1){

		US acc_x=(i2c_ADXL345_get_acc(I2C_0, ADXL345_I2C_ADDR_WR,
				ADXL345_I2C_ADDR_RD, ADXL345_REG_DATAX0));
		printf("\n\r Acceleration in X axis %x",acc_x);
		US acc_y=(i2c_ADXL345_get_acc(I2C_0, ADXL345_I2C_ADDR_WR,
						ADXL345_I2C_ADDR_RD, ADXL345_REG_DATAY0));
		printf("\n\r Acceleration in Y axis %x",acc_y);
		US acc_z=(i2c_ADXL345_get_acc(I2C_0, ADXL345_I2C_ADDR_WR,
							ADXL345_I2C_ADDR_RD, ADXL345_REG_DATAZ0));
		printf("\n\r Acceleration in Z axis %x",acc_z);
}
}

/**
 @fn i2c_ADXL345_get_acc
 @brief reads acceleration from adxl345 with I2C interface
 @details read  acceleration from adxl345 after writing slave address and Adxl_Address
 @param[in] unsigned char(i2c_num--which i2c to be used)
 @param[in] unsigned short (Slave_Address_Wr--Slave address for write)
 @param[in] unsigned char (Slave_Address_Rd--Slave address for read)
 @param[in] unsigned short (Adxl_Address--word _Address)
 @param[Out] No ouput parameter.
 @return unsigned short.

 */


US i2c_ADXL345_get_acc(UC i2c_num, UC Slave_Address_Wr,
		UC Slave_Address_Rd, UC Adxl_Address){
	UC acc[2];
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

			i2c_data_read(i2c_num, acc, 2);

			return (US) (acc[1] << 8)|(acc[0]);




			break;

		}

	
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
/**
 @fn i2c_ADXL345_write_register
 @brief write adxl345 register
 @details write to adxl345 register is made after writing slave address and Adxl_Address
 @param[in] unsigned char(i2c_num--which i2c to be used)
 @param[in] unsigned char (Slave_Address_Wr--Slave address for write)
@param[in] unsigned short (Adxl_Address--word _Address)
 @param[Out] No ouput parameter.
 @return unsigned short.

 */
void i2c_ADXL345_write_register(UC i2c_num, UC Slave_Address_Wr,UC Adxl_Address,UC value){

	 while (1) {
	  			i2c_start(i2c_num, 0x00, 0);

	  			if (i2c_data_write(i2c_num, &Slave_Address_Wr, 01)) { //writes slave address

	  				continue; //received NACK
	  			}
	  			//printf("Slave address ACK\n\r");
	  			if (i2c_data_write(i2c_num, &Adxl_Address, 01)) { //writes MSB of address

	  				continue; //received NACK
	  			}
	  			if (i2c_data_write(i2c_num, &value, 01)) { //writes LSB of address

	  						continue; //received NACK
	  			}
	  			//printf("Word address  ACK\n\r");
	  			i2c_stop(i2c_num);

	break;
	 }
}


UC i2c_ADXL345_read_register(UC i2c_num, UC Slave_Address_Wr,UC Slave_Address_Rd,UC Adxl_Address){

	UC rxd_data;
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

			i2c_start(i2c_num, 0x01, 1); //start sequence for reading data
			if (i2c_data_write(i2c_num, &Slave_Address_Rd, 01)) { //write slave address and set EEPROM to read mode

				continue; //received NACK
			}
			//printf("Slave address read ACK\n\r");
			i2c_data_read(i2c_num, &rxd_data, 01);
			printf("data is %x", rxd_data);
			printf("\n\r");
			return rxd_data;

		}


}







