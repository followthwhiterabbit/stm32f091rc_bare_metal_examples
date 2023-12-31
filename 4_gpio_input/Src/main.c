//#include "stm32f091xc.h"
#include "stm32f0xx.h"


#define GPIOA_PIN_5_MODE_OUTPUT (1U<<10)


#define PIN_5  		(1U<<5)
#define PIN_13      (1U<<13)

#define PIN_5_TURN_OFF (1U<<21)

#define PUSH_BUTTON_ENABLE  (1U<<26)

#define LED_PIN		PIN_5

#define GPIOA_ENABLE   (1U << 17)
#define GPIOC_ENABLE   (1U << 19)

#define BTN_PIN 		PIN_13


/*
 *                          00    00    00     00     00    00    00   00   00  00
 *
 *
 */

int main(void)
{
// enabling clock access to GPIOA and GPIOC

	RCC->AHBENR |= GPIOA_ENABLE;
	RCC->AHBENR |= GPIOC_ENABLE;

	GPIOA->MODER |= GPIOA_PIN_5_MODE_OUTPUT;
	GPIOA->MODER &= ~(1U<<11);

	GPIOC->MODER &= ~(1<<26);
	GPIOC->MODER &= ~(1<<27);



	/*   Set GPIOC PIn 13 as input */



while(1)
{

	// we need to check if btn is pressed
	if(GPIOC->IDR & BTN_PIN)
	{

	GPIOA->BSRR  = LED_PIN;

	}
	else
	{

	GPIOA->BSRR =  PIN_5_TURN_OFF;
	}



}


}
