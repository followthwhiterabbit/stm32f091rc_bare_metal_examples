//#include "stm32f091xc.h"
#include "stm32f0xx.h"


#define GPIOA_PIN_5_MODE_OUTPUT (1U<<10)


#define PIN_5  		(1U<<5)

#define PIN_5_TURN_OFF (1U<<21)

#define LED_PIN		PIN_5

#define GPIOA_ENABLE   (1U << 17)




/*
 *                          00    00    00     00     00    00    00   00   00  00
 *
 *
 */

int main(void)
{

	RCC->AHBENR |= GPIOA_ENABLE;

	GPIOA->MODER |= GPIOA_PIN_5_MODE_OUTPUT;
	GPIOA->MODER &= ~(1U<<11);


while(1)
{
	GPIOA->BSRR  = LED_PIN;
	for(int i = 0; i < 1000000; i++){}
	GPIOA->BSRR =  PIN_5_TURN_OFF;
	for(int i = 0; i < 1000000; i++){}




}


}
