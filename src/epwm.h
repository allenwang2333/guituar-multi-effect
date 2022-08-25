/*
 * epwm.h
 *
 * 	Created on: Aug 1 2022
 * 		Author: Allen Wang
 *
 */


#ifndef EPWM_H_
#define EPWM_H_

#include "dsc_config.h"

void Init_ePWM_O_Gpio(void);
void Init_ePWM_for_ADC(void);
void pwm1_config();
void pwm2_config(uint16_t val);

#endif /* EPWM_H_ */
