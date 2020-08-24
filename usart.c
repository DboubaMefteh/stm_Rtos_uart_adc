/*
 * usart.c
 *
 *  Created on: Jan 4, 2020
 *      Author: dbouba
 */
#include "usart.h"




#include <stddef.h>
#include <string.h>



/*alternate function :Pin mask*/
#define GPIO_AFRH_AFRH9                      ((uint32_t) 0x000000F0)
#define GPIO_AFRH_AFRH9_AF7                  ((uint32_t) 0x00000070)
#define GPIO_AFRH_AFRH10                     ((uint32_t) 0x00000F00)
#define GPIO_AFRH_AFRH10_AF7                 ((uint32_t) 0x00000700)






void USART1_GPIO_Config(void)
{
	/* Enable port A clock */
	  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	  /* Select alternate function mode */
	  GPIOA->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10);
	  GPIOA->MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);

	  /* Select output type push-pull for Tx(PA9) */
	  GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_9);

	  /* Select output speed medium for Tx(PA9) */
	  GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR9);
	  GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_0;

	  /* Select pull up */
	  GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR9 | GPIO_PUPDR_PUPDR10);
	  GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR10_0);

	  /* Select AF7 */
	  GPIOA->AFR[1] &= ~(GPIO_AFRH_AFRH9 | GPIO_AFRH_AFRH10);
	  GPIOA->AFR[1] |= (GPIO_AFRH_AFRH9_AF7 | GPIO_AFRH_AFRH10_AF7);

}


void USART1_Init(void)
{
	/* Enable USART1 clock */
	  RCC->APB2ENR = RCC_APB2ENR_USART1EN;

	  /* Select oversampling by 8 mode */
	  USART1->CR1 &= USART_CR1_OVER8;

	  /* Select one sample bit method */
	  USART1->CR3 |= USART_CR3_ONEBIT;

	  /* Select 1 Start bit, 9 Data bits, n Stop bit */
	  USART1->CR1 |= USART_CR1_M;

	  /* Select 1 stop bit */
	  USART1->CR2 &= ~USART_CR2_STOP;

	  /* Enable parity control */
	  USART1->CR1 |= USART_CR1_PCE;

	  /* Select odd parity */
	  USART1->CR1 |= USART_CR1_PS;

	  USART1->BRR = 0x30d;//Baude rate


}


void USART1_Enable(void)
{
	/* Enable USART1 */
	  USART1->CR1 |= USART_CR1_UE;

	  /* Enable transmitter */
	  USART1->CR1 |= USART_CR1_TE;
	  /* Enable parity error interrupt */
	  USART1->CR1 |= USART_CR1_PEIE;


}




void strTransmit(const char * str)
{
	 uint8_t sizeM=strlen(str);
	 for(int idx = 0; idx < sizeM; idx++)
	     {
	       /* Check USART status register */
	       while(!(USART1->SR & USART_SR_TXE));/* Wait for transmission buffer empty flag */


	       /* Write data into transmit data register */
	       USART1->DR = str[idx];
	     }
}


