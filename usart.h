/*
 * usart.h
 *
 *  Created on: Jan 4, 2020
 *      Author: dbouba
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f4xx.h"




void USART1_GPIO_Config(void);
void USART1_Init(void);
void USART1_Enable(void);








void strTransmit(const char * str);




#endif /* USART_H_ */
