/*
 * __rfm12b.c
 *
 *  Created on: 02.09.2018
 *      Author: Tomasz Pluta
 */

#include "__rfm12b_platform.h"
#include "stm32f042_spi.h"


void Rfm12bSpiInit(void) {

	SPI1Reset();
	Spi1Init16bit();
//	SetPInPullUp(RFM12B_IRQ_PORT, RFM12B_IRQ_PIN_NB);
	GPIOF->MODER |= GPIO_MODER_MODER1_0;


}



uint16_t Rfm12bWriteCmd( uint16_t cmd )
{
  	NSEL_RFM12_LOW;
	uint16_t recData = Spi1Transmit16bit(cmd);
	NSEL_RFM12_HIGH;
	return recData;

}
