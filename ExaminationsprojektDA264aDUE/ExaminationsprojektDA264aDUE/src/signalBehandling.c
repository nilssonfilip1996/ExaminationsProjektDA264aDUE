/*
* sampel_int.c
*
* Low-pass FIR-filter implementation(0-1000Hz).
* 
*  Author: Tommy och Filip och Jesper
*/

#include <asf.h>
#include "signalBehandling.h"
#include <math.h>
#include "adcdac.h"


#define M 43
#define nbrOfSamples 100



static float xbuff[M+1]={0};
static float b[M+1] ={  -0.008501776042313,-0.002743409346133, 0.007488801099629,  0.01765326667963,
	0.01657598715714,  0.00263784038596, -0.01119863755238, -0.00938804134475,
	0.007734114648412,  0.02066577307441,  0.01087858147431, -0.01530120118036,
	-0.02834002249943,-0.007200440660156,  0.03094029359488,  0.04082545906818,
	-0.002276799635088, -0.06331186690031, -0.06589701061634,  0.03779925384047,
	0.209660057233,    0.342050287139,    0.342050287139,    0.209660057233,
	0.03779925384047, -0.06589701061634, -0.06331186690031,-0.002276799635088,
	0.04082545906818,  0.03094029359488,-0.007200440660156, -0.02834002249943,
	-0.01530120118036,  0.01087858147431,  0.02066577307441, 0.007734114648412,
	-0.00938804134475, -0.01119863755238,  0.00263784038596,  0.01657598715714,
	0.01765326667963, 0.007488801099629,-0.002743409346133,-0.008501776042313};			 //Initierar b koefficienterna till 1/(M+1).
	
	static uint8_t offsetCounter = 0;
	static uint32_t offsetBuff[nbrOfSamples] = {0};	//Array with samples(including offset!).
		
	static uint32_t offsetSum = 0;
	static uint16_t dcOffset = 0;
	
	static uint8_t sampleCounter = 0;
	static int16_t mvBuffer[nbrOfSamples] = {0};	//Array with mV(Without offset!).


/**
*  Interrupt handler for TC0 interrupt.
*/
void TC0_Handler(void)
{
	//ioport_set_pin_level(CHECK_PIN, HIGH);		//put test pin HIGH
	volatile uint32_t ul_dummy;
	uint32_t invalue, outvalue;
	float sum = 0;
	
	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);			//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	invalue = adc_get_value();
	
	/* FIR filter */
	for(int i = M; i>0;i--){
		xbuff[i]=xbuff[i-1];
	}
	
	xbuff[0] = (float)invalue;
	
	/* Apply FIR-filter */
	for(uint8_t k=0; k<=M; k++){
		sum += b[k]*xbuff[M-k];
	}
	
	outvalue = (uint32_t)sum;
	/* FIR filter ends */
	
	/************************************************************************/
	/* Offset calculation                                                   */
	/************************************************************************/
	/* Still waiting for 100 ADC-samples */
	if(offsetCounter<=nbrOfSamples){
		offsetBuff[offsetCounter] = outvalue;
		offsetCounter++;
	}
	/* We have reached 100 samples, time to compute a new offset */
	else{
		for(int i=0; i<nbrOfSamples; i++){
			offsetSum = offsetSum + offsetBuff[i];
		}
		dcOffset = offsetSum/nbrOfSamples;
		offsetCounter=0;
		offsetSum=0;
	}
	/************************************************************************/
	/* Converting the ADC value to the corresponding mV.                    */
	/************************************************************************/
	if(sampleCounter<nbrOfSamples){
		int32_t ov = outvalue;  //uint32 ---> int32. Brutally important.
		mvBuffer[sampleCounter] = ((ov-dcOffset)*1000)/1240; //1.24 is ratio between ADC-values and actual voltage.
		sampleCounter++;
	}
	
	dacc_write_conversion_data(DACC,outvalue);	//send output value to DAC
	//ioport_set_pin_level(CHECK_PIN,LOW);		//put test pin LOW
}

uint16_t getDcOffset(void) {
	return dcOffset;
}

uint8_t getCounter(void){
	return sampleCounter;
}

int16_t* getMvBuffer(void){
	return mvBuffer;
}

void reset_counter(void){
	sampleCounter = 0;
} 
