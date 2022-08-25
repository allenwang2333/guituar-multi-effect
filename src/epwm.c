/*
 * epwm.c
 * 	Created on Aug 1 2022
 * 		Author: Allen Wang
 */

#include "epwm.h"
/*
init trigger pwm
*/
void Init_ePWM_for_ADC(void)
{
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
	EDIS;
}

/*
init output pwm
*/
void Init_ePWM_O_Gpio(void)
{
	/*
	 * initialize output pwm
	 */
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
	EDIS;
}

/*
config trigger pwm
*/
void pwm1_config()
{
	EPwm1Regs.TBPRD = 5119; 
		EPwm1Regs.CMPA.half.CMPA = 1024; 
		EPwm1Regs.CMPB = 1024; 
		EPwm1Regs.TBCTR = 0x0000; /* clear counter */
		EPwm1Regs.TBPHS.half.TBPHS = 0x0000; 

		EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR; 
		EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
		EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;
		EPwm1Regs.AQCTLB.bit.CBU = AQ_SET; 

		EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 
		EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
		EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW; 
		EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; 
		EPwm1Regs.TBCTL.bit.SWFSYNC = 0;
		EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
		EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
		EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;

		EPwm1Regs.ETSEL.bit.INTSEL = ET_DCAEVT1SOC;
		EPwm1Regs.ETSEL.bit.INTEN = 0; 
		EPwm1Regs.ETSEL.bit.SOCASEL = 2; 
		EPwm1Regs.ETSEL.bit.SOCAEN = 1;
		EPwm1Regs.ETSEL.bit.SOCBEN = 0;
		EPwm1Regs.ETSEL.bit.SOCBSEL = 0;

		EPwm1Regs.ETPS.bit.SOCAPRD = 1;
}

/*
set output pwm
*/
void pwm2_set(uint16_t val)
{
	EPwm2Regs.CMPA.half.CMPA = val; 
}


/*
config output pwm
*/
void pwm2_config(uint16_t val)
{
	EPwm2Regs.TBPRD = 4096;
	EPwm2Regs.CMPA.half.CMPA = val; 
	EPwm2Regs.CMPB =  256;

	EPwm2Regs.TBPHS.half.TBPHS = 0x0000; // Set Phase register to zero
	EPwm2Regs.TBCTR = 0x0000; // clear TB counter
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Phase loading disabled
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; // TBCLK = SYSCLKOUT
	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on TBCTR = Zero
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on TBCTR = Zero
	EPwm2Regs.AQCTLA.bit.PRD = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;
	EPwm2Regs.AQCTLB.bit.PRD = AQ_CLEAR;
	EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;
}

