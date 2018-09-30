/*
******************************************************************************
File:     main.cpp
Info:     Generated by Atollic TrueSTUDIO(R) 9.0.1   2018-09-28

The MIT License (MIT)
Copyright (c) 2018 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f0xx.h"
#include "stm32f042_spi.h"
#include "bmp280_hal.h"
#include "bmp280.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/






struct bmp280_t bmp280;

int main(void)
{
	SystemCoreClockUpdate();
	GpioInitForSpi1();

	Spi1Init8bit();
	bmp280_init_Csn();

	bmp280_assign_SPI(&bmp280);

	uint8_t v_data_u8;
//	  bmp280.BMP280_BUS_READ_FUNC(bmp280.dev_addr,	BMP280_CHIP_ID_REG, &v_data_u8, BMP280_GEN_READ_WRITE_DATA_LENGTH);
//	  bmp280.BMP280_BUS_READ_FUNC(bmp280.dev_addr,	BMP280_STAT_REG, &v_data_u8, BMP280_GEN_READ_WRITE_DATA_LENGTH);
//	  bmp280.BMP280_BUS_READ_FUNC(bmp280.dev_addr,	BMP280_TEMPERATURE_LSB_REG, &v_data_u8, BMP280_GEN_READ_WRITE_DATA_LENGTH);
//	  bmp280.BMP280_BUS_READ_FUNC(bmp280.dev_addr,	BMP280_CONFIG_REG, &v_data_u8, BMP280_GEN_READ_WRITE_DATA_LENGTH);

	bmp280_init(&bmp280);

	 signed long temperature;
	 signed long pressure;

	 signed long temp_out;
	 signed long press_out;

 uint8_t powerMode;
	 bmp280_set_power_mode(3);
	 bmp280_get_power_mode(&powerMode);
	 bmp280_set_oversamp_temperature(3);
	 bmp280_set_oversamp_pressure(3);

	bmp280_read_uncomp_temperature(&temperature);
	temp_out = bmp280_compensate_temperature_int32(temperature);


	bmp280_read_uncomp_pressure(&pressure);
	press_out = bmp280_compensate_pressure_int32(pressure);



  while (1)
  {

  }
}