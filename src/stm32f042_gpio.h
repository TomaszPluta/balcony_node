/*
 * stm32f042_gpio.h
 *
 *  Created on: 30.09.2018
 *      Author: tomek
 */

#ifndef STM32F042_GPIO_H_
#define STM32F042_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"

void SetPort_Enable (GPIO_TypeDef * gpioPort);
void SetPin_PullUp (GPIO_TypeDef * gpioPort, uint8_t GPIOPinNB);
void SetPin_AsOutput (GPIO_TypeDef * gpioPort, uint8_t pinNB);
void SetPin_AsInput (GPIO_TypeDef * gpioPort, uint8_t pinNB);

void SetGpioA0AsExtiFall (void);

#ifdef __cplusplus
}
#endif



#endif /* STM32F042_GPIO_H_ */
