/*
 * stm042_spi.c
 *
 *  Created on: 29.09.2018
 *      Author: tomek
 */

#include "stm32f042x6.h"
#include "stm32f042_spi.h"

void Spi1Init8bit (void){
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_BR_2 | SPI_CR1_SSM;
	SPI1->CR2 |= SPI_CR2_SSOE | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0 | SPI_CR2_FRXTH;
	SPI1->CR1 |= SPI_CR1_SPE;
}

void Spi1Init16bit (void){
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_BR_2 | SPI_CR1_SSM;
	SPI1->CR2 |= SPI_CR2_SSOE | SPI_CR2_DS_2 | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0 ;
	SPI1->CR1 |= SPI_CR1_SPE;
}


void GpioInitForSpi1(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOFEN;

	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	GPIOA->MODER |= GPIO_MODER_MODER6_1;
	GPIOA->MODER |= GPIO_MODER_MODER7_1;
	GPIOA->AFR[0] = GPIO_AFRL_AFRL0;

}


void SPI1Reset (void){
	RCC->APB2RSTR |=  RCC_APB2RSTR_SPI1RST;
	RCC->APB2RSTR &=  ~RCC_APB2RSTR_SPI1RST;
}

uint8_t  Spi1Transmit8bit(uint8_t byte){
	while (!(SPI1->SR & SPI_SR_TXE));
	*(__IO uint8_t *) &(SPI1->DR) = byte;
	while (!(SPI1->SR & SPI_SR_RXNE));
	return *(uint8_t *)&(SPI1->DR);
}


uint16_t Spi1Transmit16bit(uint16_t word){
	while (!(SPI1->SR & SPI_SR_TXE));
	(SPI1->DR) = word;
	while (!(SPI1->SR & SPI_SR_RXNE));
	return (SPI1->DR);
}



void Spi1ReadWriteString(uint8_t * read, uint8_t* write, uint8_t cnt){
	uint8_t i =0;
	while (i != cnt){
		read[i] = Spi1Transmit8bit(write[i]);
		i++;
	}
}

