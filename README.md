# stm_Rtos_uart_adc
Hello , I wish that you are doing well.

In this blog , we will deal with ADC and UART units in stm32f4 board. I did already post in the last blog how does the usart1 work, you can find the post here .

this project is about  automatic lighting system.
Hardware Supplies:
1.STM32F4

2.Lamp

3. LDR (Photoresistor)

4. 10 KOhms resistor 

 

The process functions of these peripherals will work simultaneous , via FreeRtos middle-ware. this application turns into two threads 
Note : 
     USART1 peripheral is connected to the USB port in the stm32f4 board.


     LDR resistor:
A photoresistor (or light-dependent resistor, LDR,or photo-conductive cell) is a light-controlled variable resistor. The resistance of a photoresistor decreases with increasing incident light intensity.a photoresistor is made of a high resistance semiconductor. In the dark, a photoresistor can have a resistance as high as several megohms (MΩ), while in the light,a photoresistor can have a resistance as low as a few hundred ohms.(Source : Wikipedia )

 
To deal with any periphral in stm32 devices there is four steps to follow:
 
1. configuration : 
    Set up the clock , configure the Control Registers (CRx) gennerally there is 2 or 3 control registers need to configured depend on the desired application.
 
2.Initialization :
    Initialize the peripheral (if needed)
 
3. Enable the Peripheral 
 
4. main function or the process. 


ADC1 :
 
The value of the Vldr will be captured by the ADC , the pin 5 of the port A  will be configured as analog input.
 
 
GPIO Configuration

The LDR pin will be wired to the pin5 of the Port A
then:
      *active the clock of the port A
      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

      *pick the analog mode
      GPIOA->MODER |= GPIO_MODER_MODER5;

      *no pull to
      GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;





ADC Configuration :

 active the clock of the ADC1 peripheral
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




 
