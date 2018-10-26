/*
 * stm32f042_adc.c
 *
 *  Created on: 23.10.2018
 *      Author: tomek
 */
#include "stm32f0xx.h"




void AdcCalibration (void){
	if ((ADC1->CR & ADC_CR_ADEN) != 0) /* (1) */
	{
	ADC1->CR |= ADC_CR_ADDIS; /* (2) */
	}
	while ((ADC1->CR & ADC_CR_ADEN) != 0)
	{
	/* For robust implementation, add here time-out management */
	}
	ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN; /* (3) */
	ADC1->CR |= ADC_CR_ADCAL; /* (4) */
	while ((ADC1->CR & ADC_CR_ADCAL) != 0) /* (5) */
	{
	/* For robust implementation, add here time-out management */
	}
}

void AdcEnable (void){
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1->ISR |= ADC_ISR_ADRDY;
	ADC1->CR |= ADC_CR_ADEN;
	uint16_t timout = 0xFFFF;
	while ((!(ADC1->ISR && ADC_ISR_ADRDY)) && (timout > 0));
	RCC->CR2 = RCC_CR2_HSI14ON;
	timout = 0xFFFF;
	while (!(RCC->CR2 & RCC_CR2_HSI14RDY) && (timout>0));
}



void AdcConfigDmaTransfer (void){
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	ADC1->CFGR1 |= ADC_CFGR1_DMAEN;
	DMA1_Channel1->CPAR = (uint32_t)(&ADC1->DR);
	static uint16_t adcResult;
	DMA1_Channel1->CMAR = &adcResult;
	DMA1_Channel1->CNDTR = 1;
	DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0; /*Memory: 16bits*/
	DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0; /*Periph: 16bits*/
	DMA1_Channel1->CCR |= DMA_CCR_TCIE;
	DMA1_Channel1->CCR |= DMA_CCR_EN;
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	NVIC_SetPriority(DMA1_Channel1_IRQn, 4);
	ADC1->CHSELR |= ADC_CHSELR_CHSEL1;
	ADC1->CFGR1 |= ADC_CFGR1_OVRMOD;
	ADC1->CFGR1 |= ADC_CFGR1_AUTOFF;
}



void AdcStartSingleConversion (void){
	ADC1->CR |= ADC_CR_ADSTART;
}









