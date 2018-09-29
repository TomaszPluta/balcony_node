/*
 * stm32f042_spi.h
 *
 *  Created on: 29.09.2018
 *      Author: tomek
 */

#ifndef STM32F042_SPI_H_
#define STM32F042_SPI_H_


#ifdef __cplusplus
extern "C" {
#endif


void Spi1Init8bit (void);

void Spi1Init16bit (void);

void GpioInitForSpi1(void);


void SPI1Reset (void);

uint8_t  Spi1Transmit8bit(uint8_t byte);

uint16_t Spi1Transmit16bit(uint16_t word);


void Spi1ReadWriteString(uint8_t * read, uint8_t* write, uint8_t cnt);

#ifdef __cplusplus
}
#endif



#endif /* STM32F042_SPI_H_ */
