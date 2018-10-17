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
	RtcUnlock();
	RTC->ISR  |= RTC_ISR_INIT;
	while ((RTC->ISR & RTC_ISR_INITF) != RTC_ISR_INITF) /* (3) */
	{
	/* add time out here for a robust application */
	}
	RTC->ISR  &= ~RTC_ISR_INIT;
//	RTC->PRER =
}
