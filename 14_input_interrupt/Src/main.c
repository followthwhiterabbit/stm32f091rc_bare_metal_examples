//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"


#define GPIOA_ENABLE 	(1U<<17)

#define PIN5			(1U<<5)

#define LED				PIN5


int main(void)
{

	RCC->AHBENR |= GPIOA_ENABLE;


	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

pc13_exti_init();
uart2_tx_init();


while(1)
{



}

}


static void exti_callback(void)
{
	printf("button pressed...\n\r");
}



void EXTI4_15_IRQHandler(void)
{
	if((EXTI->PR & LINE_13))
	{
		/* Clear PR flag */
		EXTI->PR |= LINE_13;
		// do something...
		exti_callback();



	}
}

