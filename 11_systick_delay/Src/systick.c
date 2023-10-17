/*
 * systick.c
 *
 *  Created on: Oct 16, 2023
 *      Author: kaan
 */

#include "stm32f0xx.h"
#include "systick.h"


// default clock of stm32f091rc is 8Mhz, 8 000 000 cycles per second,
// per milisecond 8000 cycles, this will


#define SYSTICK_LOAD_VAL		8000 // in one miliseconds
#define CTRL_ENABLE 			(1U<<0)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)




void systickDelayMs(int delay)
{
/* Configure the SysTick */
/* Reload with number of clocks per millisecond */

	SysTick->LOAD = SYSTICK_LOAD_VAL;

/* Clear Systick current value register */
	SysTick->VAL = 0;
/* Enable Systick and select internal Clock Source */
	SysTick->CTRL  = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i = 0; i < delay; i++)
	{
		/* Wait until the COUNTFLAG is set */
		while((SysTick->CTRL & CTRL_COUNTFLAG)!= CTRL_COUNTFLAG){}
// this for loop is to create a delay with a configured value, we're stuck in while loop until the 8000 cycles which means
		// 1 millisecond has been passed, with the for loop we delay this function

	}


	SysTick->CTRL = 0;



}
