#include "uart.h"

#define GPIOA_ENABLE   (1U << 17)
#define UART2EN 	   (1U << 17)
#define CR1_TE 		   (1U << 3)
#define CR1_RE		   (1U << 2)
#define CR1_UE_ENABLE  (1U << 0)
#define ISR_TXE 	   (1U << 7)
#define ISR_RXNE	   (1U << 5)
#define CR1_RXNEIR	   (1U << 5)

#define DMA1EN		   (1U << 0)

#define DMA_CH4_EN	   ~( (1U<<12) | (1U<<13) | (1U<<14) | (1U<<15) )

#define SYS_FREQ 	   8000000
#define APB1_CLK	   SYS_FREQ

#define UART_BAUDRATE 	38400



/* Funtion Prototypes */

int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void dma1_requestline0_init(uint32_t src, uint32_t dst, uint32_t len)
{

	// this needs to be configured for stm32f091rc

	/* (3) Configure the peripheral data register address */
	/* (4) Configure the memory address */
	/* (5) Configure the number of DMA tranfer to be performs on channel 1 */
	/* (6) Configure increment, size and interrupts */
	/* (7) Enable DMA Channel 1 */


/* (1) Enable the peripheral clock on DMA */
	RCC->AHBENR |= RCC_AHBENR_DMA1EN; /* (1) */


	/* (2) Enable DMA transfer on ADC */
	ADC1->CFGR1 |= ADC_CFGR1_DMAEN; /* (2) */

	DMA1_Channel1->CPAR = (uint32_t) (&(ADC1->DR)); /* (3) */
	DMA1_Channel1->CMAR = (uint32_t)(ADC_array); /* (4) */
	DMA1_Channel1->CNDTR = 3; /* (5) */
	DMA1_Channel1->CCR |= DMA_CCR_MINC | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0
	| DMA_CCR_TEIE | DMA_CCR_TCIE ; /* (6) */
	DMA1_Channel1->CCR |= DMA_CCR_EN; /* (7) */
	/* Configure NVIC for DMA */
	/* (1) Enable Interrupt on DMA Channel 1 */
	/* (2) Set priority for DMA Channel 1 */
	NVIC_EnableIRQ(DMA1_Channel1_IRQn); /* (1) */
	NVIC_SetPriority(DMA1_Channel1_IRQn,0); /* (2) */




}









void uart2_rxtx_init(void)
{
	/* configure uart gpio pin */
	// Enable clock access to gpioa
	RCC->AHBENR |= GPIOA_ENABLE;


	/* Set PA2 mode to alternate function mode */
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &= ~(1U<<4);

	/* Set PA2 alternate function type to UART_TX (AF01) */
	GPIOA->AFR[0] |= (1<<8);
	GPIOA->AFR[0] &= ~(1<<9);
	GPIOA->AFR[0] &= ~(1<<10);
	GPIOA->AFR[0] &= ~(1<<11);


	/* Set PA3 as alternate function mode*/
	GPIOA->MODER |= (1U<<7);
	GPIOA->MODER &= ~(1U<<6);

	/* Set PA3 alternate fucntion type to UART_RX */
	GPIOA->AFR[0] |= (1<<12);
	GPIOA->AFR[0] &= ~(1<<13);
	GPIOA->AFR[0] &= ~(1<<14);
	GPIOA->AFR[0] &= ~(1<<15);




	/* configure uart module */
	/* enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/* configure baud rate */
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/* configure the transfer direction
	 *
	 * rx and tx in this case
	 */
	USART2->CR1 = CR1_TE | CR1_RE;

	/* enable uart module */
	USART2->CR1 |= CR1_UE_ENABLE;


}

void uart2_rx_interrupt_init(void)
{
	/* configure uart gpio pin */
	// Enable clock access to gpioa
	RCC->AHBENR |= GPIOA_ENABLE;


	/* Set PA3 as alternate function mode*/
	GPIOA->MODER |= (1U<<7);
	GPIOA->MODER &= ~(1U<<6);

	/* Set PA3 alternate fucntion type to UART_RX */
	GPIOA->AFR[0] |= (1<<12);
	GPIOA->AFR[0] &= ~(1<<13);
	GPIOA->AFR[0] &= ~(1<<14);
	GPIOA->AFR[0] &= ~(1<<15);



	/* configure uart module */
	/* enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/* configure baud rate */
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/* configure the transfer direction
	 *
	 * rx and tx in this case
	 */
	USART2->CR1 = CR1_TE | CR1_RE;

	/* Enable RXNE interrupt */
	USART2->CR1 |= CR1_RXNEIR;

	/* Enable UART2 interrupt in NVIC */
	NVIC_EnableIRQ(USART2_IRQn);


	/* enable uart module */
	USART2->CR1 |= CR1_UE_ENABLE;


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



char uart_read(void)
{
	/*
	 * We need to make sure that the receive data register is empty
	 *
	 *
	 */

	while(!(USART2->ISR & ISR_RXNE)){}


	/* reading the data */
	return USART2->RDR;

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



