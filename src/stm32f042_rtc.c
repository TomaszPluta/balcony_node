/*
 * stm32f042_rtc.c
 *
 *  Created on: 17.10.2018
 *      Author: tomek
 */
#include "stm32f0xx.h"

#define RTC_UNLOCK1 		0xCA
#define RTC_UNLOCK2 		0x53





void RtcUnlock(void){
	RTC->WPR = RTC_UNLOCK1;
	RTC->WPR = RTC_UNLOCK2;
}



void RtcInit(void){
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	RCC->CSR |= RCC_CSR_LSION;
	PWR->CR |= PWR_CR_DBP;
	RCC->BDCR |= RCC_BDCR_RTCEN;
	RCC->BDCR |= RCC_BDCR_RTCSEL_LSI;
	RTC->WPR = 0xCA; /* (1) */
	RTC->WPR = 0x53; /* (1) */
	RTC->ISR |= RTC_ISR_INIT; /* (2) */
	while ((RTC->ISR & RTC_ISR_INITF) != RTC_ISR_INITF) /* (3) */
	{
	/* add time out here for a robust application */
	}
	RTC->PRER = 0x007F0137; /* (4) */
	RTC->TR = RTC_TR_PM | 10; /* (5) */
	RTC->ISR &=~ RTC_ISR_INIT; /* (6) */
	RTC->WPR = 0xFE; /* (7) */
	RTC->WPR = 0x64; /* (7) */




//	RtcUnlock();
//	RTC->ISR  |= RTC_ISR_INIT;
//	//uint32_t wait = RTC_INIT_TIMEOUT;
//	//while ((RTC->ISR & RTC_ISR_INITF) != RTC_ISR_INITF)  && --wait))/* (3) */
//	while ((RTC->ISR & RTC_ISR_INITF) != RTC_ISR_INITF) /* (3) */
//	{
//	/* add time out here for a robust application */
//	}
//	RTC->ISR  &= ~RTC_ISR_INIT;
////	RTC->PRER =
}
