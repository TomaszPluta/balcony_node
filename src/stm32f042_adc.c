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

void EnableAdc (void){
	ADC1->ISR |= ADC_ISR_ADRDY;
	ADC1->CR |= ADC_CR_ADEN;
	uint16_t timout = 0xFFFF;
	while ((!(ADC1->ISR && ADC_ISR_ADRDY)) && (timout > 0));
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN

}
