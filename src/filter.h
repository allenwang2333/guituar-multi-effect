/*
 * filter.h
 *
 *  Created on: Aug 15 2022
 *      Author: Allen Wang
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "config.h"
#include "dsc_config.h"

float lowPassInit(float fc);
float highPassInit(float fc);
float lowPass(uint16_t i, uint16_t* input, float alpha, filter* data);
float highPass(uint16_t i, uint16_t* input, float alpha, filter* data);
float midPass(uint16_t i, uint16_t* input, float alpha, float beta, filter* data);

#endif /* FILTER_H_ */
