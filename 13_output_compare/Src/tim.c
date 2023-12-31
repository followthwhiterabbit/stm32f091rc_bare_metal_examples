/*
 * tim.c
 *
 *  Created on: Oct 16, 2023
 *      Author: kaan
 *
 */
#include "stm32f0xx.h"

#define TIM2_EN		(1U<<0)
#define CR1_EN		(1U<<0)
#define OC_TOGGLE	(1U<<4) | (1U<<5)
#define CCER_CC1E	(1U<<0)

#define GPIOA_ENABLE (1U<<17)
#define AFR5_TIM	 (1U<<21)



/*
 * Our default clock frequency is 8Mhz
 *
 *
 *
 */


void tim2_1hz_init(void)
{
	/* enable the clock access to tim2 */
	RCC->APB1ENR |= TIM2_EN;

	/* set prescaler value */
	TIM2->PSC = 800 - 1;  // ---------------> 800 0000 / 800 = 10 000


	/* set auto-reload value */
	TIM2->ARR = 10000 - 1;  // 10 000 / 10 000 = 1Mhz
	/* clear counter */
	TIM2->CNT = 0;

	/* enable timer */
	TIM2->CR1 = CR1_EN;





}

void tim2_pa5_output_compare(void)
{
	/* Enable clock access to GPIOA */
	RCC->AHBENR |= GPIOA_ENABLE;


	/* Set PA5 to alternate function */
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |=	 (1U<<11);

	/* Set PA5 alternate function type to TIM2_CH1 (AF02) */
	GPIOA->AFR[0] = AFR5_TIM;

	/* enable the clock access to tim2 */
	RCC->APB1ENR |= TIM2_EN;

	/* set prescaler value */
	TIM2->PSC = 800 - 1;  // ---------------> 800 0000 / 800 = 10 000


	/* set auto-reload value */
	TIM2->ARR = 10000 - 1;  // 10 000 / 10 000 = 1Mhz

	/* Set output compare toggle mode */
	TIM2->CCMR1 = OC_TOGGLE;



	/* For PA5 pin for instance, Alternate function value is AF02 */
	TIM2->CCER = CCER_CC1E;


	/* clear counter */
	TIM2->CNT = 0;

	/* enable timer */
	TIM2->CR1 = CR1_EN;





}

