//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"


static void adc_callback(void);

uint32_t sensor_value;






int main(void)
{
	uart2_tx_init();
	//pa1_adc_init();
	//start_conversion();

	pa1_adc_interrupt_init();
	start_conversion();


while(1)
{


}

}

static void adc_callback(void)
{
	sensor_value = ADC1->DR;
	printf("the sensor value is %d \n\r", (int)sensor_value);
}





void ADC_COM_IRQHandler(void)
{
	/* Check for eoc in SR */
	if(ADC1->ISR & ADC_EOC)
	{
		/* Clear EOC */
		ADC1->ISR &= ~ADC_EOC;

		// doing sth here
		adc_callback();


	}
}

