/*
 * config.h
 *
 *  Created on: Aug 15 2022
 *      Author: Allen Wang
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define BUFFER_SIZE 12288
#define TUNER_BUFFER_SIZE 512
#define LEVEL 9
#define PI 3.1415926
#define SAMPLE_RATE 12000
#define SAMPLE_TIME 0.0000833333f

typedef struct {
	float real;
	float img;
} complex;

typedef struct {
	unsigned short oldData;
	unsigned short newData;
} filter;

#endif /* CONFIG_H_ */
