/*
 * __rfm12b.c
 *
 *  Created on: 02.09.2018
 *      Author: Tomasz Pluta
 */

#include "__rfm12b_platform.h"
#include "stm32f042_spi.h"


void Rfm12bSpiInit(void) {


	Spi1Init16bit();
	SetPInPullUp(RFM12B_IRQ_PORT, RFM12B_IRQ_PIN_NB);
}



uint16_t Rfm12bWriteCmd( uint16_t cmd )
{
	NSEL_RFM12_LOW;
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI1, cmd);

	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	/* Return the byte read from the SPI bus */
	uint16_t recData = SPI_I2S_ReceiveData(SPI1);

	NSEL_RFM12_HIGH;

	return recData;

}
