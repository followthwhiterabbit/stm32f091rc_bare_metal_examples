//#include "stm32f091xc.h"
#include "stm32f0xx.h"


#define GPIOA_ENABLE   (1U << 17)

#define UART2EN 	   (1U << 17)




/*
 *                          00    00    00     00     00    00    00   00   00  00
 *
 *
 */

int main(void)
{

while(1)
{


}


}




void uart2_tx_init(void)
{
	/* configure uart gpio pin */
	// Enable clock access to gpioa
	RCC->AHBENR |= GPIOA_ENABLE;


	/* Set PA2 mode to alternate function mode */
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &= ~(1U<<6);

	/* Set PA2 alternate function type to UART_TX (AF01) */
	GPIOA->AFR[0] |= (1<<8);
	GPIOA->AFR[0] &= (1<<9);
	GPIOA->AFR[0] |= (1<<10);
	GPIOA->AFR[0] |= (1<<11);


	/* configure uart module */
	/* enable clock access to uart2 */
	/* configure baud rate */
	/* configure the transfer direction */
	/* enable uart module */








}
