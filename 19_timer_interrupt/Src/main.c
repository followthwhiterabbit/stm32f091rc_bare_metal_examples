//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "systick.h"
#include "tim.h"


#define GPIOA_ENABLE  (1U << 17)

#define PIN_5		  (1U << 5)

#define LED_PIN 		PIN_5


static void tim2_callback(void);



int main(void)
{

	// enable clock access to GPIOA

	RCC->AHBENR |= GPIOA_ENABLE;


	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);


	uart2_tx_init();
	tim2_1hz_interrupt_init();


while(1)
{

}

}

static void tim2_callback(void)
{
	printf("a second passed !! \n\r");
	GPIOA->ODR ^= LED_PIN;
}



void TIM2_IRQHandler(void)
{
	/* Clear update interrupt flag */
	TIM2->SR &= ~SR_UIF;

	// do something ...
	tim2_callback();



}





