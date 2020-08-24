#include "adcPhoto.h"

void GPIO_Connfig()
{
	  // active the clock of the port A
	  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	  //pick the analog mode
	  GPIOA->MODER |= GPIO_MODER_MODER5;
	  // no pull
	  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;

}
void ADC_Config()
{
	//active the clock of the ADC1 peripheral
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	/*
	 * control register one  (CR1) configuration
	 */
	// select 12 bits resolutionn
	ADC1->CR1 &= ~ADC_CR1_RES;

	/*
	 *control register two  (CR2) configuration
	 */

	// Select Right alignment
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	//Enable ADC
	ADC1->CR2 |= ADC_CR2_ADON;
	//start converion
	ADC1->CR2 |= ADC_CR2_SWSTART;



	  // Select channel 5 regular
	  ADC1->SQR1 &= ~ADC_SQR1_L;
	  ADC1->SQR3 &= ~ADC_SQR3_SQ1;
	  ADC1->SQR3 |= 0x05;

}
