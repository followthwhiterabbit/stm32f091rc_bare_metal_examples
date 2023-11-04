/*
 * i2c.c
 *
 *  Created on: Nov 3, 2023
 *      Author: kaan
 */
#include "stm32f0xx.h"


#define GPIOB_EN	(1U<<18)
#define I2C1_EN		(1U<<21)



/* Pinout
 *  PB8 ---- SCL
 *  PB9 ---- SDA
 *
 *
 */



void I2C1_init(void)
{
	/* Enable clock access to GPIOB */
	RCC->AHBENR |= GPIOB_EN;


	/* Set PB8 and PB9 mode to alternate function */
	GPIOB->MODER |= (0xA << 16);

/* Set PB8 and PB9 output type to open drain */
	GPIOB->OTYPER |= (0x3 << 8);                     // 0000 0011 0000 0000

/* Enable Pullup for PB8 and PB9 */
	GPIOB->PUPDR |= (0x5 << 16);

	/* Enable clock access to I2C1 */
	RCC->APB1ENR |= I2C1_EN;


ex


}


