/*
 * filter.c
 *
 *  Created on: Aug 15 2022
 *      Author: Allen Wang
 */

#include "filter.h"
#include "config.h"

float lowPassInit(float fc) {
	double alpha,k;
	k= 2 * PI * fc * SAMPLE_TIME;
	alpha = k/(k+1);
	return alpha;
}

float lowPass(uint16_t i, uint16_t* input, float alpha, filter* data) {
/* TODO:
 * Yn = A * Xn + (1 - A) * Yn-1
 */
	float temp;
	temp = 1.0f - alpha;
	if (!i){
		temp *= input[BUFFER_SIZE-1];
	}
	else{
		temp *= input[i-1];
	}
	float output = alpha * (data->newData);
	output += temp;
	input[i] = (uint16_t) output;
	return output;
}

float highPassInit(float fc) {
	float alpha,k;
	k = 1/(2*PI*fc);
	alpha = k/(k+SAMPLE_TIME);
	return alpha;
}

float highPass(uint16_t i, uint16_t* input, float alpha, filter* data) {
	/*
	 * Yn = a*Yn-1 + a* (Xn - Xn-1)
	 */

	float output;
	float temp;
	if (i == 0) temp = alpha * input[BUFFER_SIZE-1];
	else temp = alpha * input[i-1];
	output = alpha * (data->newData - data->oldData);
	output += temp;
	input[i] = (uint16_t) output;
	return output;
}

float midPass(uint16_t i, uint16_t* input, float alpha, float beta, filter* data) {
	/*
	 * combine low pass and high pass
	 */
	lowPass(i, input, alpha, data);
	highPass(i, input, beta, data);
	return 1.0;
}
