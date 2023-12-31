//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"


static void adc_callback(void);

uint32_t sensor_value;
uint16_t val;
uint16_t adcResult = 0;

int main(void)
{
	uart2_tx_init();
	//pa1_adc_init();
	//start_conversion();

	pa1_adc_interrupt_init();
	//external_interrupt_selection_code();


	start_conversion();
while(1)
{
	//printf("adc value is %d: \r\n", (uint16_t)adcResult);
}

}



static void adc_callback(void)
{
	adcResult = ADC1->DR;
}





void ADC_COM_IRQHandler(void)
{
	/* Check for eoc in SR */


 	if(ADC1->ISR & ADC_ISR_EOC)
	{
//		 Clear EOC
 		 //adcResult = ADC1->DR;
		// doing sth here
		adc_callback();


	}


		ADC1->ISR &= ~ADC_ISR_EOC;
/*

	if(EXTI->PR & (1U<<21))
		{

		adc_callback();

			val = 1;
			EXTI->PR |= (1U<<21);


		}

}
*/

}
