//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "systick.h"
#include "tim.h"



int timestamp = 0;

/* set up: connect jumper wire from pa5 to pa6 */


int main(void)
{

tim2_pa5_output_compare();
tim3_pa6_input_capture();



while(1)
{
	// wait until edge is captured //
	while(! (TIM3->SR & SR_CC1IF) ){} // 0000 0000 0000 0000 0000 0000 0000 00x0 // if it's set, we get out of the loop
									// 0000 0000 0000 0000 0000 0000 0000 0010
								  //  &--------------------------------------
                                    //0000 0000 0000 0000 0000 0000 0000 00 0

	/* read value */
	timestamp = TIM3->CCR1;





}

}

