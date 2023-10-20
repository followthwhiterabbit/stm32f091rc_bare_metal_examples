/*
 * tim.h
 *
 *  Created on: Oct 16, 2023
 *      Author: kaan
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);



#define SR_UIF	(1U<<0)
#define SR_CC1IF	(1U<<1)


#endif /* TIM_H_ */
