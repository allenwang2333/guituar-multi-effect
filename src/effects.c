/*
 * effects.c
 *
 *  Created on: Aug 4 2022
 *      Author: Allen Wang
 */

#include "effects.h"
#include "config.h"
#include "dsc_config.h"

uint16_t reverbEffect(uint16_t i, uint16_t* adcResArr, uint16_t param) {
// reverb is just a bunch of delays lol

	delayEffect(i, adcResArr, 2000);
	delayEffect(i, adcResArr, 1000);

	return 1;
}

uint16_t delayEffect(uint16_t i, uint16_t* adcResArr, uint16_t param) {
	uint16_t adcDelay, a, b;
	uint16_t k;
	if (i < param) {
		k = i + BUFFER_SIZE - param;
	}
	else {
		k = i - param;
	}
	a = adcResArr[i];
	b = adcResArr[k];
	adcDelay = a + b;
	adcDelay >>= 1;
	adcResArr[i] = adcDelay;
	return 1;
}

uint16_t distortionEffect(uint16_t i, uint16_t* adcResArr, float gain) {
	float adcResDisto = (float) adcResArr[i];
	adcResDisto -= 2048.0;
	adcResDisto *= gain;

	if (adcResDisto >= 2048.0) {
		adcResDisto = 2048.0;
	}
	if (adcResDisto <= -2048.0) {
		adcResDisto = -2048.0;
	}

	adcResDisto += 2048.0;

	adcResArr[i] = (uint16_t) adcResDisto;
	return 1;
}


