/*
 * stm32f042_gpio.c
 *
 *  Created on: 30.09.2018
 *      Author: tomek
 */
#include "stm32f0xx.h"


void SetPInPullUp (GPIO_TypeDef * gpioPort, uint8_t GPIOPinNB){
	const uint8_t pupdrPullUp = 0x2U;
	gpioPort->PUPDR |= (pupdrPullUp << GPIOPinNB);
}
