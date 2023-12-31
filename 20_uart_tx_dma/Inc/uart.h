/*
 * uart.h
 *
 *  Created on: Oct 5, 2023
 *      Author: kaan
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f0xx.h"
#include <stdint.h>

#define ISR_RXNE	   (1U << 5)

void uart2_tx_init();
void usart2_rxtx_init();
void uart2_rx_interrupt_init(void);

/* Funtion Prototypes */
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);


void uart_write(unsigned int ch);
char uart_read(void);





#endif /* UART_H_ */
