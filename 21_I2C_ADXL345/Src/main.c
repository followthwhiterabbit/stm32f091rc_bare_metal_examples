//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>


#define GPIOA_ENABLE (1U << 17)


#define GPIOA_5 (1U<<5);


char key;


int main(void)
{

	RCC->AHBENR |= GPIOA_ENABLE;

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);


	uart2_rx_interrupt_init();
	//uart2_tx_init();
	//uart2_rxtx_init();


while(1)
{

}



}



static void uart_callback(void)
{
	key = USART2->RDR;

	if(key == '1')
	{
		GPIOA->ODR |= GPIOA_5;
		printf("1 is pressed\n");
	}
	else
	{
		GPIOA->ODR &= ~GPIOA_5;
		printf("another key is pressed\n");
	}

}


void USART2_IRQHandler(void)
{
	/* Check if RXNE is set */
if(USART2->ISR & ISR_RXNE)
{
	uart_callback();
}

}

