/*
 * adc.h
 *
 *  Created on: Oct 9, 2023
 *      Author: kaan
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

#define ADC_EOC		(1U<<2)



// function prototypes
void pa1_adc_init(void);
void pa1_adc_interrupt_init(void);
void start_conversion(void);
uint32_t adc_read(void);







#endif /* ADC_H_ */
