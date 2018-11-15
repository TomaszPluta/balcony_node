/*
******************************************************************************
File:     main.cpp
Info:     Generated by Atollic TrueSTUDIO(R) 9.0.1   2018-09-28

The MIT License (MIT)
Copyright (c) 2018 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "string.h"
#include "bmp280_platform.h"
#include "stm32f0xx.h"
#include "stm32f042_spi.h"
#include "stm32f042_gpio.h"
#include "stm32f042_rtc.h"
#include "stm32f042_adc.h"
#include "bmp280.h"
#include "__rfm12b_platform.h"
#include "__rfm12b.h"
#include "ring_buff.h"
#include "mqtt_client.h"
#include "mqtt_packet.h"
#include "mqtt_socket.h"
#include "systemDefines.h"


#include <vector>
#include <string>
#include "json_parser.h"

using namespace::std;

#define NODE_ADDR					(2)
#define MAX_PUBLISH_BUFF_SIZE		(32)

#define ADC_LIGHT_POS				(0)
#define ADC_HUMID_POS					(1)

#define SW_RESET (uint16_t)0b1111111000000000

#define TOGGLE_LED()	(GPIOA->ODR ^= (1 << 3))


volatile rfm12bObj_t rfm12bObj;
struct bmp280_t bmp280;
volatile uint16_t  adcBuffDMA[2];


#ifdef __cplusplus
extern "C" {
#endif



volatile uint8_t rxBuff[512];
volatile uint16_t pos;
volatile bool rx_flag;
volatile uint32_t systickMsIRQ;
volatile ringBuff_t ringBuff;


#define BROKER_ADDR		(1)
#define NODE_ADDR		(2)

uint8_t radio_receive (volatile rfm12bObj_t* rfm12b, volatile ringBuff_t * ringBuff);

void StartSystick(void){
	SysTick_Config(SystemCoreClock/1000);
}


void SysTick_Handler(void){
	systickMsIRQ++;
}



uint32_t GetTickCount(void){
	 return systickMsIRQ;
}


void EXTI0_1_IRQHandler (void){
	GPIOA->ODR ^= (1 << 3);
	NVIC_ClearPendingIRQ(EXTI0_1_IRQn);
	Rfm12bIrqCallback(&rfm12bObj);
	EXTI->PR |= EXTI_PR_PR0;
	radio_receive (&rfm12bObj, &ringBuff);
}






void RTC_IRQHandler (void){
	EXTI->PR |= EXTI_PR_PR17;
}


void DMA1_Channel1_IRQHandler (void){
	NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);
	DMA1->IFCR |= DMA_IFCR_CTCIF1;
	asm volatile ("nop");
}



#ifdef __cplusplus
}
#endif



 void _delay_ms(int n) {

 	int i, j;
 	j= n*1000;
 	while(j--) {
 		i=2;
 		while(i--);
 	}
 }





 uint8_t client_rec(void * context, uint8_t * buf, uint8_t buf_len);

 int mqtt_message_cb(struct _MqttClient *client, MqttMessage *message, byte msg_new, byte msg_done){
 	return 1;
 }

 int mqt_net_connect_cb (void *context, const char* host, word16 port, int timeout_ms){
 	return 1;
 }

 int mqtt_net_read_cb(void *context, byte* buf, int buf_len, int timeout_ms){
 	uint32_t enterTimestamp = GetTickCount();
 	while (GetTickCount() - enterTimestamp < (uint32_t) timeout_ms){
 		uint8_t rxNb = RingBufferRead(&ringBuff, (uint8_t *)buf, buf_len);
 		if (rxNb >0){
 			return rxNb;
 		}
 	}
 	return -1;
 }

 int mqtt_net_write_cb(void *context, const byte* buff, int buffLen, int timeout_ms){

 	rfm12bObj_t * obj = (rfm12bObj_t*) context;
 	Rfm12bStartSending(obj, (uint8_t *)buff, buffLen, BROKER_ADDR);
 	return buffLen;
 }


 int mqtt_net_disconnect_cb(void *context){
 	return 0;
 }




 uint8_t radio_receive (volatile rfm12bObj_t* rfm12b, volatile ringBuff_t * ringBuff){
 	//here check if address we receive is our address and check who send this message
 	uint8_t byteNb = 0;
 		byteNb = rfm12b->completedRxBuff.dataNb;
 		if (byteNb > 0){
 			byteNb = (byteNb < R_BUFF_SIZE) ? byteNb : R_BUFF_SIZE;
 			RingBufferWrite(ringBuff, rfm12b->completedRxBuff.data, byteNb);
 			rfm12b->completedRxBuff.dataNb = 0;
 		}
 	return byteNb;
 }









int main(void)
{

	json jsonDataToSend;
	tokenT tokentest("testId", "testVal");
	jsonDataToSend.add(tokentest);

	tokenT tokenCounter("counter");
	jsonDataToSend.add(tokenCounter);
	tokenT tokenTemp("temp");
	jsonDataToSend.add(tokenTemp);
	tokenT tokenPress("press");
	jsonDataToSend.add(tokenPress);
	tokenT tokenHumid("humid");
	jsonDataToSend.add(tokenHumid);
	tokenT tokenLight("light");
	jsonDataToSend.add(tokenLight);
	std::string jsonNodeStr = jsonDataToSend.parse();

	AdcEnable ();
	AdcConfigDmaTransfer (adcBuffDMA);
	AdcStartSingleConversion();
	StartSystick();

	BSP_RTC_EXTI_Init();
	RtcInit();
	SystemCoreClockUpdate();
//	RtcSetAlarmEveryGivenMinutes(1);
	RtcSetAlarmEveryGivenSeconds(5);
	GpioInitForSpi1();

	Spi1Init8bit();
	bmp280_init_Csn();

	bmp280_assign_SPI(&bmp280);

	uint8_t v_data_u8;

	bmp280_init(&bmp280);

	signed long temperature;
	signed long pressure;

	signed long tempOut;
	signed long pressOut;



	bmp280_set_oversamp_temperature(3);
	bmp280_set_oversamp_pressure(3);

	uint8_t powerMode;


	bmp280_set_power_mode(0);
	bmp280_get_power_mode(&powerMode);

	bmp280_read_uncomp_temperature(&temperature);
	tempOut = bmp280_compensate_temperature_int32(temperature);

	bmp280_read_uncomp_pressure(&pressure);
	pressOut = bmp280_compensate_pressure_int32(pressure);


	bmp280_set_power_mode(3);
	bmp280_get_power_mode(&powerMode);

	bmp280_read_uncomp_temperature(&temperature);
	tempOut = bmp280_compensate_temperature_int32(temperature);

	bmp280_read_uncomp_pressure(&pressure);
	pressOut = bmp280_compensate_pressure_int32(pressure);


	/*led init*/
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	SetPin_AsOutput(GPIOA, 3);
	SetPin_PullUp(GPIOA, 3);
	GPIOA->ODR |= (1 << 3);




 	Rfm12bInit();
 	Rfm12bWriteCmd(0x0000);
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	SetGpioA0AsExtiFall();
	SetPin_PullUp(RFM12B_IRQ_PORT, RFM12B_IRQ_PIN_NB);


 	rfm12bFifoReset();
 	rfm12bSwitchRx();
	NVIC_SetPriority(EXTI0_1_IRQn, 0);
 	NVIC_EnableIRQ(EXTI0_1_IRQn);
 	Rrm12bObjInit (&rfm12bObj, NODE_ADDR);



 	SetPort_Enable(GPIOF);
 	SetPin_AsInput(GPIOF, 0);
 	SetPin_PullUp(GPIOF, 0);


		MqttNet net;
		MqttClient client;
		net.context = (void*)&rfm12bObj;
		net.connect = mqt_net_connect_cb;
		net.read = mqtt_net_read_cb;
		net.write = mqtt_net_write_cb;
		net.disconnect = mqtt_net_disconnect_cb;

		uint8_t tx_buf[BUF_SIZE_TX];
		uint8_t rx_buf[BUF_SIZE_RX];
		MqttClient_Init(&client, &net, mqtt_message_cb, tx_buf, BUF_SIZE_TX, rx_buf, BUF_SIZE_RX, CMD_TIMEOUT_MS);


		MqttConnect mqtt_con;
		mqtt_con.clean_session =0;
		mqtt_con.client_id = "rt1";
		mqtt_con.enable_lwt = 0;
		mqtt_con.keep_alive_sec = 30;
		mqtt_con.stat = MQTT_MSG_BEGIN;
		mqtt_con.username ="bedroomTMP1";
		mqtt_con.password = "passw0rd";
		MqttClient_Connect(&client, &mqtt_con);

		const char* balconyConf = "flat/config/balcony";
		const char* globalConf = "flat/config/global";

		MqttTopic topics[2];
		topics[0].qos = MQTT_QOS_1;
		topics[0].topic_filter = balconyConf;
	    topics[1].qos = MQTT_QOS_1;
		topics[1].topic_filter = globalConf;

		MqttSubscribe subscribe;
		subscribe.packet_id = 1;
		uint8_t topic_count = 2;
		subscribe.topic_count = topic_count;
		subscribe.topics = topics;
		subscribe.stat = MQTT_MSG_BEGIN;
		MqttClient_Subscribe(&client, &subscribe);


		SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
		uint32_t pckt_count = 0;
		while (1){
			if (RTC->ISR & RTC_ISR_ALRAF){
				RTC->ISR &= ~RTC_ISR_ALRAF;
//				RtcSetAlarmEveryGivenMinutes(2);
				RtcSetAlarmEveryGivenSeconds(8);
				TOGGLE_LED();

				AdcStartSingleConversion();

				bmp280_SPI_init();

				bmp280_read_uncomp_temperature(&temperature);
				tempOut = bmp280_compensate_temperature_int32(temperature);
				tokenTemp.UpdateVal(tempOut);
				jsonDataToSend.update(tokenTemp);

				bmp280_read_uncomp_pressure(&pressure);
				pressOut = bmp280_compensate_pressure_int32(pressure);
				tokenPress.UpdateVal(pressOut);
				jsonDataToSend.update(tokenPress);

				tokenLight.UpdateVal((uint32_t)adcBuffDMA[ADC_LIGHT_POS]);
				jsonDataToSend.update(tokenLight);
				tokenHumid.UpdateVal((uint32_t)adcBuffDMA[ADC_HUMID_POS]);
				jsonDataToSend.update(tokenHumid);


				Rfm12bSpiInit();

				tokenCounter.UpdateVal(pckt_count++);
				jsonDataToSend.update(tokenCounter);
				MqttPublish publish;
				publish.buffer = (uint8_t*) jsonDataToSend.GetContent().data();
				publish.total_len = strlen((char*)publish.buffer);
				publish.duplicate = 0;
				publish.packet_id = 0;
				publish.qos = MQTT_QOS_0;
				publish.retain =0;
				publish.stat = MQTT_MSG_BEGIN;
				const char* topicBalcony = "flat/balcony/";
				publish.topic_name = topicBalcony;
				publish.topic_name_len = strlen(topicBalcony);
				MqttClient_Publish(&client, &publish);


			}

			__WFI();

		}
		//	}
}
//http://pomad.fr/node/37



