/*
 * tunner.c
 *
 *  Created on: Aug 8 2022
 *      Author: Allen Wang
 */

#include "dsc_config.h"
#include "config.h"
#include "math.h"
#include "tunner.h"

void dft(uint16_t* inputBuff, uint32_t* outputBuff) {
	for (uint16_t i = 0; i < TUNER_BUFFER_SIZE; i++) {
		complex result;
		result.real = 0.00;
		result.img = 0.00;
		for (uint16_t j = 0; j < TUNER_BUFFER_SIZE; j++) {
			float temp = (float)2*PI* (float)i* (float)j;
			float in = inputBuff[j];
			temp /= TUNER_BUFFER_SIZE;
			float resReal = cosf(temp) * in;
			float resImg = sinf(temp) * in;
			result.real += resReal;
			result.img -= resImg;
		}
		outputBuff[i] = sqrtf(powf(result.real,2)+powf(result.img,2));
	}
}

unsigned short bitReverse(unsigned short index, unsigned short len) {
    unsigned short newIndex = 0;
    for (int i = 1; i <= len; i++) {
        if (index & (1 << (len - i))) {
            newIndex |= 1 << (i-1);
        }
    }
    return newIndex;
}

void fft(unsigned short* inputBuff, float* realBuff, float* imgBuff, float* outputBuff) {
/*
    first reverse the input index bits and place them in the output buffer
*/

	for (int i = 0; i < TUNER_BUFFER_SIZE; i++) {
        imgBuff[i] = 0;
		unsigned short temp = bitReverse(i, LEVEL);
        realBuff[i] = inputBuff[temp];
    }

    for (unsigned int level = 1; level <= LEVEL; level++) {
        unsigned int distance = 1 << (level - 1);
        for (unsigned int j = 0; j <= distance - 1; j++) {
            unsigned int k = 1 << (LEVEL - level);
            unsigned int p = j*k;
            for (unsigned int i = 0; i <= k - 1; i++) {
                unsigned int r = 2*distance*i;
                r += j;
                float ft = 2.0*PI*p;
                ft /= TUNER_BUFFER_SIZE;
                float real = realBuff[r+distance];
				real *= cosf(ft);
                real += imgBuff[r+distance] * sinf(ft);
                float img =  imgBuff[r+distance];
				img	*= cosf(ft);
                img	-= realBuff[r+distance] * sinf(ft);

                realBuff[r+distance] = realBuff[r] - real;
                imgBuff[r+distance] = imgBuff[r] - img;
                realBuff[r] = realBuff[r] + real;
                imgBuff[r] = imgBuff[r] + img;
            }
        }
    }

    for (uint16_t i = 0; i < TUNER_BUFFER_SIZE; i++) {
    	float t1 = realBuff[i];
    	float t2 = imgBuff[i];
    	outputBuff[i] = sqrtf(t1*t1 + t2*t2);
    }
}
