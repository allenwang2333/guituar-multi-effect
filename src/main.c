#include "dsc_config.h"
#include <syscalls.h>
#include "stdlib.h"
#include "config.h"
#include"epwm.h"
#include "adc.h"
#include "effects.h"
#include "tunner.h"
#include "filter.h"

float imgBuff[TUNER_BUFFER_SIZE];
float realBuff[TUNER_BUFFER_SIZE];
float output[TUNER_BUFFER_SIZE];
uint16_t adcResArr[BUFFER_SIZE];

volatile uint16_t i; // index
volatile uint16_t ii;
volatile uint16_t j;
volatile uint16_t adcRes;
volatile uint8_t flag;
float freq;

filter filterStruct;

void adc_isr();

int main(void)
{
	flag = 0; // not in interrupt
	i = 0;
	j = 0;

	InitSysCtrl();

	Init_ePWM_for_ADC(); // configure pwm0,1 as trigger
	Init_ePWM_O_Gpio(); // configure pwm2,3 as output


	DINT;
	IER = 0x0000; 
	IFR = 0x0000; 

	InitPieVectTable();

	EALLOW;
	PieCtrlRegs.PIEACK.all = 0xffff; 
	PieVectTable.rsvd10_1 = &adc_isr;
	PieCtrlRegs.PIEIER10.all = 0xff;
	EDIS;

	IER |= M_INT10;
	ADC_Init();

	pwm1_config();

	EINT;

	pwm2_config(4096); // init pwm output

	float alpha = lowPassInit(4000);
	float beta = highPassInit(100);

	while (1)
	{
		if (flag) {

			//lowPass(i, adcResArr, alpha, &filterStruct);
			//highPass(i, adcResArr, beta, &filterStruct);

			//distortionEffect(i, adcResArr, 10.5);
			reverbEffect(i, adcResArr, 2000);
			//delayEffect(i, adcResArr, 6000);
			int temp = *(adcResArr+i);
			pwm2_set(temp);
			flag = 0;
//
//			j++;
//			if(j > TUNER_BUFFER_SIZE-1) {
//				break;
//			}
    		}

	}

	uint16_t index = 1;
	uint32_t max = 0;
//
//	dft(adcResArr, output);
//	fft(adcResArr,realBuff, imgBuff, output);
//	for(uint16_t k = 1; k < (TUNER_BUFFER_SIZE/2);k++){
//		if (output[k] > max) {
//			max = output[k];
//			index = k;
//		}
//	}
//
//	freq = ((float) SAMPLE_RATE) * index/TUNER_BUFFER_SIZE;
//

	return 0;
}

INTERRUPT void adc_isr()
{

	EALLOW;
	flag = 1;
	adcRes = AdcResult.ADCRESULT0;


	//if (!i) filterStruct.oldData = adcResArr[BUFFER_SIZE-1];
	//else filterStruct.oldData = adcResArr[i-1];

	//filterStruct.newData = adcRes;

	if (i < BUFFER_SIZE-1) {
		i++;
	}
	else {
		i = 0;
	}
	adcResArr[i] = adcRes;



	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 0x1;
	AdcRegs.ADCINTOVFCLR.bit.ADCINT1 = 0x1;
	PieCtrlRegs.PIEACK.all = 0xffff;

	//flag = 1;
	EDIS;
}
// ----------------------------------------------------------------------------
