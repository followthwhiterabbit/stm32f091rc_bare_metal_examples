/*
 * adc.c
 *
 *  Created on: Oct 9, 2023
 *      Author: kaan
 */
#include "stm32f0xx.h"
#include "adc.h"


#define ADCENABLE		(1U<<9)
#define GPIOAENABLE 	(1U<<17)
#define ADC_CH1 		(1U<<1)
#define CR_ADEN			(1U<<0)
#define CFGR_CONT 		(1U<<13)
#define CR_EOCIE		(1U<<2)


/*
 *	 adc configured with 3 channels
 *	 ch2, ch3, ch5
 *	 first = ch5
 *   second = ch6
 *	 third = ch3
 *
 */

void external_interrupt_selection_code()
{
	 	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	 	GPIOA->MODER |= (1<<2);
	 	GPIOA->MODER |= (1<<3);


	    // Enable the ADC1 clock
	    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	    // Select the ADC channel and configure the trigger for the ADC
	    ADC1->CHSELR = ADC_CH1; // Configure ADC settings, channel, and trigger

	    // Enable the ADC end of conversion interrupt
	    ADC1->IER |= ADC_IER_EOCIE;

	    // Configure NVIC for ADC1 interrupt
	    NVIC_EnableIRQ(ADC1_IRQn); // Use the correct interrupt name for ADC1
	    NVIC_SetPriority(ADC1_IRQn, 0);

	    // Enable ADC and start conversions
	    ADC1->CR |= ADC_CR_ADEN;

}





void pa1_adc_interrupt_init(void)
{


	/* Configure the ADC GPIO Pin */

	/* Enable Clock access to gpioa */
	RCC->AHBENR |= GPIOAENABLE;
	/* Set the mode of PA1 to analog mode */
	GPIOA->MODER |= (1<<2);
	GPIOA->MODER |= (1<<3);



	/* Configure the ADC module */
	/* Enable clock access to ADC */
	RCC->APB2ENR |= ADCENABLE;


	/* Enable ADC end-of-conversion interrupt */
	ADC1->IER |= CR_EOCIE;


	/* Enable ADC interrupt in NVIC */
	NVIC_EnableIRQ(ADC1_COMP_IRQn);


	/* Setting Priority */
	NVIC_SetPriority(ADC1_COMP_IRQn, 2);




	/* Configure adc parameters */
	/* Conversion sequence start */


	ADC1->CHSELR = ADC_CH1;

	/* Conversion sequence length */
	/* Enable ADC module */
	ADC1->CR |= CR_ADEN;

}





void pa1_adc_init(void)
{


	/* Configure the ADC GPIO Pin */

	/* Enable Clock access to gpioa */
	RCC->AHBENR |= GPIOAENABLE;
	/* Set the mode of PA1 to analog mode */
	GPIOA->MODER |= (1<<2);
	GPIOA->MODER |= (1<<3);



	/* Configure the ADC module */
	/* Enable clock access to ADC */
	RCC->APB2ENR |= ADCENABLE;

	/* Configure adc parameters */
	/* Conversion sequence start */
	ADC1->CHSELR = ADC_CH1;


	/* Conversion sequence length */
	/* Enable ADC module */
	ADC1->CR |= CR_ADEN;

}



void start_conversion(void)
{
	/* Enable continuous convertion */
	ADC1->CFGR1 |= CFGR_CONT;

	/* Start ADC conversion */
	ADC1->CR |= (1U<<2); // starting the adc conversion


}

uint32_t adc_read(void)
{
	/* Wait for conversion to be complete */

	/*
	 *  EOC - End of Conversion Flag
	 *  This bit is set by hardware at the end of the conversion of a sequence of channels selected by
	 *  the CHSEL bits. It's cleared by software writing 1 to it.
	 *
	 *  0: Conversion sequence not complete
	 *  1: Conversion sequence complete
	 *
	 *
	 */
		while(!(ADC1->ISR & (1U<<2)))
		{
		 // When we're stuck here, conversion is not completed


		}

	/* Read converted result */
		return ADC1->DR;

}


















