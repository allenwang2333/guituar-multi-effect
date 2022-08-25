/*
 * tunner.h
 *
 *  Created on: Aug 8 2022
 *      Author: Allen Wang
 */

#ifndef TUNNER_H_
#define TUNNER_H_

#include "config.h"

uint16_t bitReverse(uint16_t index, uint16_t len);
void dft(uint16_t* inputBuff, uint32_t* outputBuff);
void fft(uint16_t* inputBuff, float* realBuff, float* imgBuff, float* outputBuff);
#endif /* TUNNER_H_ */
