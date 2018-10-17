/*
 * stm32f042_rtc.h
 *
 *  Created on: 17.10.2018
 *      Author: tomek
 */

#ifndef STM32F042_RTC_H_
#define STM32F042_RTC_H_



#ifdef __cplusplus
extern "C" {
#endif



void RtcUnlock(void);


void RtcInit(void);


#ifdef __cplusplus
}
#endif


#endif /* STM32F042_RTC_H_ */
