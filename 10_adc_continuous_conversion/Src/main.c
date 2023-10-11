//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"

uint32_t sensor_value;






int main(void	)
{
	uart2_tx_init();
	pa1_adc_init();
	//start_conversion();

	start_conversion();


while(1)
{
//	start_conversion(); // We were doing single conversion in a while loop in polling mode, we can set continuous coversion in main instead of while
	sensor_value = adc_read();
	printf("sensor value is  %d \n\r", sensor_value);



}

}

