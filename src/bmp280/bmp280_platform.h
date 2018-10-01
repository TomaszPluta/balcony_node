/*
 * bmp280_hal.h
 *
 *  Created on: 28 sie 2017
 *      Author: tomek
 */

#ifndef BMP280_PLATFORM_H_
#define BMP280_PLATFORM_H_

#include "stm32f0xx.h"

#ifdef __cplusplus
extern "C" {
#endif

#define bmp280_CSN_L()              (GPIOF->ODR &= ~(1<<0))
#define bmp280_CSN_H()              (GPIOF->ODR |= (1<<0))
#define SPI_BUFFER_LEN 				64
#define BUFFER_LENGTH				0xFF
#define	SPI_READ					0x80
#define SPI_WRITE					0x7F
#define BMP280_DATA_INDEX			1
#define BMP280_ADDRESS_INDEX		2

#define s8							int8_t
#define u8							uint8_t
#define u32							uint32_t

struct bmp280_t;

uint8_t  spi_read_write_string(uint8_t * read, uint8_t* write, uint8_t cnt);
s8  BMP280_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
s8  BMP280_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
void  BMP280_delay_msek(u32 msek);
s8 SPI_routine(void);
s8 bmp280_assign_SPI(struct bmp280_t *bmp280);

void bmp280_init_Csn (void);

#ifdef __cplusplus
}
#endif


#endif /* BMP280_PLATFORM_H_ */
