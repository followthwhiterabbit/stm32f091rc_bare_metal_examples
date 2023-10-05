//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>







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





