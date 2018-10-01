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

void SetPInPullUp (GPIO_TypeDef * gpioPort, uint8_t GPIOPinNB);
void SetGpioA0AsExtiFall (void);

#ifdef __cplusplus
}
#endif



#endif /* STM32F042_GPIO_H_ */
