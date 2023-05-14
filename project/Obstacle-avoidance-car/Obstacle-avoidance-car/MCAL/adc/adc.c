/*
 * adc.c
 *
 * Created: 4/15/2023 5:26:15 AM
 *  Author: atef
 */ 

#include "adc.h"


en_adcError_t ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
		switch(vref)
		{
			case VREF_AREF:
			CLR_BIT(ADMUX,REFS1);
			CLR_BIT(ADMUX,REFS0);
			break;
			case VREF_VCC:
			CLR_BIT(ADMUX,REFS1);
			SET_BIT(ADMUX,REFS0);
			break;
			case VREF_256:
			SET_BIT(ADMUX,REFS1);
			SET_BIT(ADMUX,REFS0);
			break;
		}
		
	    	/*clock*/
	    	ADCSRA=ADCSRA&0xf8;//0b11111000
			// 	if (scaler>7)        //saturation
			// 	{
			// 		scaler=7;
			// 	}
		//	scaler=scaler&0x07;     //trancation
			ADCSRA=ADCSRA|scaler;
			
			
			/*ADC enable*/
			SET_BIT(ADCSRA,ADEN);
			
			/*ADC_READ*/
		//	CLR_BIT(ADMUX,ADLAR); // I WILL READ FAST BUT JUST THE HIGH BYTE
}
en_adcError_t ADC_Read(ADC_Channel_type channel,u16 *ADC_Read)
{   u8 adcl,adch;
	/* select ch using mux*/
	ADMUX&=0xE0;
	ADMUX|=channel;
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait until end */
	while(READ_BIT(ADCSRA,ADSC));
	/* get reading from 2 registers*/
	//IF ADLAR==0
	adcl=ADCL;
	adch=ADCH;
	*ADC_Read=(u16)(adch<<8|adcl);
	/*or*/
	//ADC_Read=ADC; 
	
	//ELSEIF ADLAR==1
	//*ADC_Read=ADC;
}

