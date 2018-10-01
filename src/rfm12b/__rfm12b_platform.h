/*
 * __rfm12b.h
 *
 *  Created on: 02.09.2018
 *      Author: Tomasz Pluta
 */


#ifdef __cplusplus
extern "C" {
#endif


#include "stdint.h"
#include "stm32f0xx.h"

#ifndef RFM12B_PLATFORM_H_
#define RFM12B_PLATFORM_H_


#define RFM12B_IRQ_PORT 			(GPIOA)
#define RFM12B_IRQ_PIN_NB			(0)


#define RFM12B_CS_PORT 			(GPIOF)
#define RFM12B_CS_PIN_NB			(1)


#define NSEL_RFM12_LOW              (RFM12B_CS_PORT->ODR &= ~(1<<RFM12B_CS_PIN_NB))
#define NSEL_RFM12_HIGH             (RFM12B_CS_PORT->ODR |= (1<<RFM12B_CS_PIN_NB))


void Rfm12bSpiInit(void);
uint16_t Rfm12bWriteCmd( uint16_t cmd );



#ifdef __cplusplus
}
#endif

#endif /* RFM12B_PLATFORM_H_ */
