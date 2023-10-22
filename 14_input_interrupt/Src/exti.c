/*
 * exti.c
 *
 *  Created on: Oct 22, 2023
 *      Author: kaan
 */

#include "exti.h"

#define GPIOC_ENABLE	(1U<<19)
#define SYSCFG_ENABLE 	(1U<<0)

void pc13_exti_init(void)
{
	/* disable global interrupt */
	__disable_irq();

	/* enable clock access for GPIOC */
	RCC->AHBENR |= GPIOC_ENABLE;

	/* Set PC13 as input */
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);



	/* Enable clock access to SYSCFG */
	RCC->APB2ENR |= SYSCFG_ENABLE;

	/* Select PORTC for EXTI13 */
	// We want to connect PC13 to the EXTI13 line
	SYSCFG->EXTICR[3] |= (1U<<5);



	/* Unmask EXTI13 */
	EXTI->IMR |= (1U<<13);


	/* Select falling edge trigger */
	EXTI->FTSR |= (1U<<13);

	/* Enable EXTI line in NVIC */
	NVIC_EnableIRQ(EXTI4_15_IRQn);




	/* Enable global interrupts */
	__enable_irq();





}
