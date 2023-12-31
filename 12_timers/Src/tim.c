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

