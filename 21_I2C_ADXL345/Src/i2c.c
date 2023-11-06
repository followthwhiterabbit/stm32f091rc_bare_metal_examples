/*
 * i2c.c
 *
 *  Created on: Nov 3, 2023
 *      Author: kaan
 */
#include "stm32f0xx.h"


#define GPIOB_EN		(1U<<18)
#define I2C1_EN			(1U<<21)
#define I2C1_CR2_START 	(1U<<13)
#define I2C1_ISR_ADDR   (1U<<3)
#define I2C1_ISR_TXE	(1U<<0)



#define SR2_BUSY 	(1U<<15)



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



	// entering the reset mode
	I2C1->CR1 &= ~(1U << 0); // bit is set to 0

	// PE must be kept low during at least three APB clock cycles in order to perform the software reset.
	// This is ensured by writing the following software sequence
	/*
	 *	Write PE = 0; //
	 *  Check PE = 0
	 *  Write PE = 1;
	 */

	while((I2C1->CR1) & (1U << 0)) // while is not set to 0, set it to zero, if it's zero, cause APB clock delay
	{
		I2C1->CR1 &= ~(1U << 0);
	}


	// here we can set the TIMINGR register value for F0 series microcontroller
	/*
	 *	I2C Speed Mode = Standard
	 *	I2C Speed frequency = 100Khz
	 *	Rise Time(ns) = 100
	 *	Fall Time(ns) = 40
	 *	Analog Filter = Enabled
	 *
	 */


	I2C1->TIMINGR = (uint32_t)0x00301D2B;



/*
 * Additionally, in master mode, the SCL clock high and low levels must be configured by
 * programming the PRESC[3:0], SCLH[7:0] and SCLL[7:0] bits in the I2C_TIMINGR register.
 *
 *
 */

	// coming out of the reset mode
	I2C1->CR1 |= 1U < 0; // we come out of the reset mode

}


void I2C1_byteRead(char saddr, char maddr, char* data)
{
	volatile int tmp;

	//waiting until bus not busy
	while(I2C1->ISR & (SR2_BUSY))
	{

	}

	/* Generate Start */
	I2C1->CR2 |= I2C1_CR2_START;

	// wait until start flag is set



	//  Transmit slave address + write
	I2C1->TXDR |= saddr << 1;

	// wait until addr flag is set
	while(!(I2C1->ISR & (I2C1_ISR_ADDR)))
	{

	}


	// to clear the ADDR FLAG, We need to set PE = 0

	I2C1->CR1 &= ~(1U << 0);

	while((I2C1->CR1) & (1U << 0)) // while is not set to 0, set it to zero, if it's zero, cause APB clock delay
		{
			I2C1->CR1 &= ~(1U << 0);
		}

	I2C1->CR1 |= 1U < 0; // we come out of the reset mode


	// We need to send the memory address
	I2C1->TXDR = maddr;

	while(!(I2C1->ISR & I2C1_ISR_TXE)){}


	/* Generate Start */
	I2C1->CR2 |= I2C1_CR2_START;

	/* Transmit slave address + Read */

	I2C1->TXDR = saddr << 1 | 1;

	// wait until addr flag is set
	while(!(I2C1->ISR & (I2C1_ISR_ADDR)))
	{

	}

	// clear addr flag
    // disable acknowledge

	// generate stop after data received
	I2C1->CR2 |= (1U<<14); // stop generation after current byte transfer

	// wait until rxne flag is set
	while(!(I2C1->ISR & (1U<<2))){}

	/* read data from dr */
	*data++ = I2C1->RXDR;

}

void I2C1_burstRead(char saddr, char maddr, int n, char* data)
{

}









