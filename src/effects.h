/*
 * effects.h
 *
 *  Created on: Aug 4 2022
 *      Author: Allen Wang
 */

#ifndef EFFECTS_H_
#define EFFECTS_H_

#include "dsc_config.h"

uint16_t reverbEffect(uint16_t i, uint16_t* adcResArr, uint16_t param);
uint16_t delayEffect(uint16_t i, uint16_t* adcResArr, uint16_t param);
uint16_t distortionEffect(uint16_t i, uint16_t* adcResArr, float gain);


#endif /* EFFECTS_H_ */
