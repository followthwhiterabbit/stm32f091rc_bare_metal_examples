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


void uart2_tx_init();

/* Funtion Prototypes */
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);


void uart_write(unsigned int ch);




#endif /* UART_H_ */
