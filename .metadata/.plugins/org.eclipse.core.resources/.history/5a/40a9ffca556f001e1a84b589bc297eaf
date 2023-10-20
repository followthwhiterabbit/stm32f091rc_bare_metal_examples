/*
 * tim.c
 *
 *  Created on: Oct 16, 2023
 *      Author: kaan
 *
 */

#include "stm32f0xx.h"

#define TIM2_EN		(1U<<0)





void tim2_1hz_init(void)
{
	/* enable the clock access to tim2 */
	RCC->APB1ENR |= TIM2_EN;

	/* set prescaler value */
	TIM2->PSC = 1600 - 1;




	/* set auto-reload value */
	/* clear counter */
	/* enable timer */





}

