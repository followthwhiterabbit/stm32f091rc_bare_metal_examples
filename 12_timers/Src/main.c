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





int main(void)
{

	// enable clock access to GPIOA

	RCC->AHBENR |= GPIOA_ENABLE;


	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);


	uart2_tx_init();
	tim2_1hz_init();


while(1)
{
	/* wait for UIF */
	while(!(TIM2->SR & SR_UIF)){}

	/* Clear UIF */
	TIM2->SR &= ~(SR_UIF); // Update Interrupt Flag is cleared after we get out of the while loop


	printf("A second passed !!\n\r");
	GPIOA->ODR ^= LED_PIN;



}

}

