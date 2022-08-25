/*
 * adc.c
 *
 * 	Created on: Aug 2 2022
 * 		Author: Allen Wang
 *
 */


#include "adc.h"

void ADC_Init(void)
{
	EALLOW;
	AdcRegs.ADCCTL1.bit.ADCENABLE = 1;  // enable ADC	
	AdcRegs.ADCCTL2.bit.CLKDIV2EN = 1; // set ADC clock to 30 MHz

	while(AdcRegs.ADCCTL1.bit.ADCRDY != 1)
	{
	} // reset ADC

	AdcRegs.INTSEL1N2.bit.INT1SEL = 0; // select EOC 0 as ADC trigger
	AdcRegs.INTSEL1N2.bit.INT1E = 1;  // enable ADCINT1 as interrupt
	AdcRegs.INTSEL1N2.bit.INT1CONT = 0; 
	AdcRegs.SOCPRICTL.bit.ONESHOT = 0; 
	AdcRegs.SOCPRICTL.bit.SOCPRIORITY = 0;
	AdcRegs.SOCPRICTL.bit.RRPOINTER = 0; // SOC1 has highest priority in round-robin
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 0; // sample time 2n+6 clocks
	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0x5; // input is ADCIN 5A
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0x5; // set PWM1 to trigger SOC0

	EDIS;
}



