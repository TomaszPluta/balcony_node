/*
 * stm32f042_gpio.c
 *
 *  Created on: 30.09.2018
 *      Author: tomek
 */
#include "stm32f0xx.h"


void SetPin_PullUp (GPIO_TypeDef * gpioPort, uint8_t pinNB){
	const uint8_t pupdrPullUp = 0x1U;
	gpioPort->PUPDR |= (pupdrPullUp << (pinNB*2));
	gpioPort->ODR |= (1 << pinNB);
}


void SetPin_AsOutput (GPIO_TypeDef * gpioPort, uint8_t pinNB){
	const uint8_t moderOut = 0x1U;
	const uint8_t moderOutSize = 0x2U;
	gpioPort->MODER |= (moderOut << (pinNB * moderOutSize));
}


void SetPin_AsInput (GPIO_TypeDef * gpioPort, uint8_t pinNB){
	const uint8_t moderInMask = 0x2U;
	const uint8_t moderInMaskSize = 0x2U;
	gpioPort->MODER &= ~(moderInMask << (pinNB * moderInMaskSize));
}


void SetPort_Enable (GPIO_TypeDef * gpioPort){
	if (gpioPort == GPIOA){
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	}
	if (gpioPort == GPIOB){
		RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	}
	if (gpioPort == GPIOC){
		RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	}
	if (gpioPort == GPIOF){
		RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
	}
}


void SetGpioA0AsExtiFall (void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;//////////////////////////////
	SYSCFG->EXTICR[1] &= (uint16_t)~SYSCFG_EXTICR1_EXTI0_PA;
	EXTI->IMR |= 0x0001;
	EXTI->FTSR |= 0x0001;
}



// void SetGpioAsExti(GPIO_TypeDef * gpioPort, uint8_t pinNb, bool riseEdge, bool fallEdge){
//	 if (gpioPort == GPIOA){
//		 RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//	 }
//	 if (gpioPort == GPIOB){
//		 RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
//	 }
//	 if (gpioPort == GPIOC){
//		 RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
//	 }
//	 if (gpioPort == GPIOF){
//		 RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
//	 }
//
//
//	 ////SYSCFG->EXTICR[1] &= (uint16_t)~SYSCFG_EXTICR1_EXTI0_PA; /* (2) */
//
//	 EXTI->IMR |= (1<<pinNb);
//	 riseEdge ? EXTI->RTSR |= (1<<pinNb) : EXTI->RTSR &= ~(1<<pinNb) ;
//	 fallEdge ? EXTI->FTSR |= (1<<pinNb) : EXTI->FTSR &= ~(1<<pinNb) ;
//
//	 if ((pinNb >=0) && (pinNb<=1)){
//		 NVIC_EnableIRQ(EXTI0_1_IRQn);
//		 NVIC_SetPriority(EXTI0_1_IRQn,0);
//	 }
//
//	 if ((pinNb >=2) && (pinNb<=3)){
//		 NVIC_EnableIRQ(EXTI2_3_IRQn);
//		 NVIC_SetPriority(EXTI2_3_IRQn,0);
//	 }
//
//	 if ((pinNb >=4) && (pinNb<=15)){
//		 NVIC_EnableIRQ(EXTI4_15_IRQn);
//		 NVIC_SetPriority(EXTI4_15_IRQn,0);
//	 }
//
// }

