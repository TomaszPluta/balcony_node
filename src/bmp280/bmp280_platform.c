
#include <bmp280_platform.h>
#include "bmp280.h"
#include "stm32f042_spi.h"

uint8_t  spi_read_write_string(uint8_t * read, uint8_t* write, uint8_t cnt){
	bmp280_CSN_L();
	Spi1ReadWriteString(read, write, cnt);
	bmp280_CSN_H();
}


s8  bmp280_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError=BMP280_INIT_VALUE;
	u8 array[SPI_BUFFER_LEN]={BUFFER_LENGTH};
	u8 stringpos;
	/*	For the SPI mode only 7 bits of register addresses are used.
	The MSB of register address denotes the type of SPI data transfer, whether
	read/write (read as 1/write as 0)*/
	array[BMP280_INIT_VALUE] = reg_addr|SPI_READ;
	spi_read_write_string(array, array, cnt+1);
	/*read routine is initiated by masking register address with 0x80*/
	/*
	* Please take the below function as your reference to
	* read the data using SPI communication
	* " IERROR = SPI_READ_WRITE_STRING(ARRAY, ARRAY, CNT+1)"
	* add your SPI read function here
	* iError is an return value of SPI read function
	* Please select your valid return value
	* In the driver SUCCESS defined as 0
	* and FAILURE defined as -1
	* Note :
	* This is a full duplex operation,
	* The first read data is discarded, for that extra write operation
	* have to be initiated. Thus cnt+1 operation done in the SPI read
	* and write string function
	* For more information please refer the SPI communication in data sheet
	*/
	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
		*(reg_data + stringpos) = array[stringpos+BMP280_DATA_INDEX];
	}
	return (s8)iError;
}

/*	\Brief: The function is used as SPI bus write
 *	\Return : Status of the SPI write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, where data is to be written
 *	\param reg_data : It is a value held in the array,
 *		which is written in the register
 *	\param cnt : The no of bytes of data to be written
 */
s8  bmp280_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = BMP280_INIT_VALUE;
	u8 array[SPI_BUFFER_LEN * BMP280_ADDRESS_INDEX];
	u8 stringpos = BMP280_INIT_VALUE;
	u8 index = BMP280_INIT_VALUE;

	for (stringpos = BMP280_INIT_VALUE; stringpos < cnt; stringpos++) {
		/* the operation of (reg_addr++)&0x7F done as per the
		SPI communication protocol specified in the data sheet*/
		index = stringpos * BMP280_ADDRESS_INDEX;
		array[index] = (reg_addr++) & SPI_WRITE;
		array[index + BMP280_DATA_INDEX] = *(reg_data + stringpos);
	}

	uint8_t read_buff[8];
	spi_read_write_string(read_buff, array, cnt*2 );


	/* Please take the below function as your reference
	 * to write the data using SPI communication
	 * add your SPI write function here.
	 * "IERROR = SPI_WRITE_STRING(ARRAY, CNT*2)"
	 * iError is an return value of SPI write function
	 * Please select your valid return value
	 * In the driver SUCCESS is defined as 0 and FAILURE is defined as -1
	 */
	return (s8)iError;
}

/*	Brief : The delay routine
 *	\param : delay in ms
*/
void  bmp280_delay_msek(u32 msek)
{
	/*Here you can write your own delay routine*/
}




s8 bmp280_assign_SPI(struct bmp280_t *bmp280) {
/*--------------------------------------------------------------------------*
 *  By using bmp280 the following structure parameter can be accessed
 *	Bus write function pointer: BMP280_WR_FUNC_PTR
 *	Bus read function pointer: BMP280_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *--------------------------------------------------------------------------*/

	bmp280->bus_write = bmp280_SPI_bus_write;
	bmp280->bus_read = bmp280_SPI_bus_read;
	bmp280->delay_msec = bmp280_delay_msek;

	return BMP280_INIT_VALUE;
}


void bmp280_init_Csn (void){
	GPIOF->MODER |= GPIO_MODER_MODER0_0;
}

