/*
 * stm32f042_rtc.c
 *
 *  Created on: 17.10.2018
 *      Author: tomek
 */
#include "stm32f0xx.h"

#define RTC_UNLOCK1 		(0xCA)
#define RTC_UNLOCK2 		(0x53)

#define RTC_LOCK1 			(0xFE)
#define RTC_LOCK2 			(0x64)
#define RTC_PRESCALER		(0x007F0137)



void RtcUnlock(void){
	RTC->WPR = RTC_UNLOCK1;
	RTC->WPR = RTC_UNLOCK2;
}


void RtcLock(void){
	RTC->WPR = RTC_LOCK1;
	RTC->WPR = RTC_LOCK2;
}



void RtcInit(void){
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	RCC->CSR |= RCC_CSR_LSION;
	PWR->CR |= PWR_CR_DBP; /*Disable backup protection*/
	RCC->BDCR |= RCC_BDCR_RTCEN;
	RCC->BDCR |= RCC_BDCR_RTCSEL_LSI;

	RtcUnlock();
	RTC->ISR |= RTC_ISR_INIT;
	uint8_t timeout = 0xFF;
	while (((RTC->ISR & RTC_ISR_INITF) != RTC_ISR_INITF) && (timeout > 0))
	{
		timeout--;
	}
	RTC->PRER = RTC_PRESCALER;
	RTC->TR =0;
	RTC->ISR &=~ RTC_ISR_INIT;
	RtcUnlock();
}




void RtcSetAlarmEveryMinute(){

	RtcUnlock();
	RTC->CR &= ~(RTC_CR_ALRAE);
	RTC->ISR &= ~(RTC_ISR_ALRAWF);
	RTC->ALRMAR =0;

	uint8_t timeout = 0xFF;
	while (((RTC->ISR & RTC_ISR_ALRAWF) != RTC_ISR_ALRAWF) && (timeout > 0))
	{
		timeout--;
	}

	RTC->ALRMAR |= RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2;
	RTC->CR |= RTC_CR_ALRAE;
	RTC->CR |= RTC_CR_ALRAIE;
	RtcLock();
	NVIC_EnableIRQ(RTC_IRQn);
}


void RtcSetAlarmEveryGivenSeconds(uint8_t seconds){
	RtcUnlock();
	RTC->CR &= ~(RTC_CR_ALRAE);
	RTC->ISR &= ~(RTC_ISR_ALRAWF);
	RTC->ALRMAR =0;

	uint8_t secondsUnits = seconds % 10;
	RTC->ALRMAR |=  secondsUnits << RTC_ALRMAR_SU_Pos;
	uint8_t secondsTens = seconds / 10;
	RTC->ALRMAR |=  secondsTens << RTC_ALRMAR_ST_Pos;

	uint8_t timeout = 0xFF;
	while (!(RTC->ISR & RTC_ISR_ALRAWF)  && (timeout > 0))
	{
		timeout--;
	}
	RTC->ALRMAR |= RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2;

	RTC->ISR |= RTC_ISR_INIT;
	timeout = 0xFF;
	while (!(RTC->ISR & RTC_ISR_INITF) && (timeout > 0))
	{
		timeout--;
	}
	RTC->TR =0;
	RTC->ISR &=~ RTC_ISR_INIT;
	RtcUnlock();


	RTC->CR |= RTC_CR_ALRAE;
	RTC->CR |= RTC_CR_ALRAIE;
	RtcLock();
	NVIC_EnableIRQ(RTC_IRQn);
}




void RtcSetAlarmEveryGivenMinutes(uint8_t minutes){
	RtcUnlock();
	RTC->CR &= ~(RTC_CR_ALRAE);
	RTC->ISR &= ~(RTC_ISR_ALRAWF);
	RTC->ALRMAR =0;

	uint8_t minutesUnits = minutes % 10;
	RTC->ALRMAR |=  minutesUnits << RTC_ALRMAR_MNU_Pos;
	uint8_t minutesTens = minutes / 10;
	RTC->ALRMAR |=  minutesTens << RTC_ALRMAR_MNT_Pos;

	uint8_t timeout = 0xFF;
	while (!(RTC->ISR & RTC_ISR_ALRAWF) && (timeout > 0))
	{
		timeout--;
	}
	RTC->ALRMAR |= RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3;

	RTC->ISR |= RTC_ISR_INIT;
	timeout = 0xFF;
	while (!(RTC->ISR & RTC_ISR_INITF) && (timeout > 0))
	{
		timeout--;
	}
	RTC->TR =0;
	RTC->ISR &=~ RTC_ISR_INIT;
	RtcUnlock();


	RTC->CR |= RTC_CR_ALRAE;
	RTC->CR |= RTC_CR_ALRAIE;
	RtcLock();
	NVIC_EnableIRQ(RTC_IRQn);
}




void BSP_RTC_EXTI_Init()
{
	EXTI->IMR |= EXTI_IMR_IM17;
	EXTI->RTSR |=  EXTI_RTSR_RT17;
	EXTI->FTSR &= ~EXTI_FTSR_FT17;
}

