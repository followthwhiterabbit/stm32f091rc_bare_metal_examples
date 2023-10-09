//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>


#define GPIOA_ENABLE   (1U << 17)
#define UART2EN 	   (1U << 17)
#define CR1_TE 		   (1U << 3)
#define CR1_UE_ENABLE  (1U << 0)
#define ISR_TXE 	   (1U << 7)


#define SYS_FREQ 	   8000000
#define APB1_CLK	   SYS_FREQ

#define UART_BAUDRATE 	38400


/* Funtion Prototypes */
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_tx_init();
void uart_write(unsigned int ch);

/*
 *                          00    00    00     00     00    00    00   00   00  00
 *
 *
 */

int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}


int main(void)
{
	uart2_tx_init();


uart_write('k');
uart_write('a');
uart_write('a');
uart_write('n');


while(1)
{
	printf("hello from stm32f091rc.....\n\r");
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
	GPIOA->AFR[0] &= ~(1<<9);
	GPIOA->AFR[0] &= ~(1<<10);
	GPIOA->AFR[0] &= ~(1<<11);


	/* configure uart module */
	/* enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/* configure baud rate */
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/* configure the transfer direction */
	USART2->CR1 = CR1_TE;

	/* enable uart module */
	USART2->CR1 |= CR1_UE_ENABLE;


}


void uart_write(unsigned int ch)
{
	/* make sure transmit data register is empty */
	while(!(USART2->ISR & ISR_TXE))
	{

	} // we wait here until transmission is completed

	/* Write to transmit data register */

	USART2->TDR = (ch & 0xFF);




}





static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{

USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);

}




static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
			return ((PeriphClk + (BaudRate/2U)) /BaudRate);


}

