//#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "systick.h"
#include "tim.h"


#define GPIOA_ENABLE  (1U << 17)

#define PIN_5		  (1U << 5)

#define LED_PIN 		PIN_5





int main(void)
{

tim2_pa5_output_compare();


while(1)
{


}

}

