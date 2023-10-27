//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "systick.h"


#define GPIOA_ENABLE  (1U << 17)

#define PIN_5		  (1U << 5)

#define LED_PIN 		PIN_5





int main(void)
{

	// enable clock access to GPIOA

	RCC->AHBENR |= GPIOA_ENABLE;


	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);


	uart2_tx_init();
	systick_1hz_interrupt();


while(1)
{



}

}

void systick_callback(void)
{
	printf("A second passed !!\n\r");
	GPIOA->ODR ^= LED_PIN;

}


void SysTick_Handler(void)
{
	systick_callback();

}


