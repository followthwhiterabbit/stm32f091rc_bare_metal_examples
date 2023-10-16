/*
 * adc.h
 *
 *  Created on: Oct 9, 2023
 *      Author: kaan
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>


// function prototypes
void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);







#endif /* ADC_H_ */
