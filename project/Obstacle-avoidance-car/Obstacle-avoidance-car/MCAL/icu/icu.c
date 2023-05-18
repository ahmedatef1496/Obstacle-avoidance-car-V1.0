/*
 * icu.c
 *
 * Created: 5/16/2023 12:00:50 AM
 *  Author: atef
 */ 

#include "icu.h"

static volatile u16 t1,t2,ICU_flag=0;

static void ICU_Read_callbackfun(void)
{
	if (ICU_flag==0)
	{
		timer1_ReadCounts(&t1);
		EXI_TriggerEdge(ICU_EXI_INT,FALLING_EDGE);
		ICU_flag=1;
	}
	else if (ICU_flag==1)
	{
		timer1_ReadCounts(&t2);
		ICU_flag=2;
	}
}
void ICU_init ()
{
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	// DIO_initpin(ICU_CH,INFREE);                              // in init all pins
	EXI_Enable(ICU_EXI_INT);
	EXI_TriggerEdge(ICU_EXI_INT,RISING_EDGE);
	EXI_SetCallBack(ICU_EXI_INT, ICU_Read_callbackfun );

}

u8 ICU_Read(u16 *pu16_PeriodTime)
{

	u16 timeout ;
	EXI_TriggerEdge(ICU_EXI_INT,RISING_EDGE);
	timer1_setTimerValue(0);
	ICU_flag=0;
		while((ICU_flag<2)&&(timeout<23000))
		{
			timeout++;
			_delay_us(1);
		}
		
		if(ICU_flag==2)
		{
			*pu16_PeriodTime =(t2-t1);
			
			return 1 ;    //done
		}
	
	return  0; //timeout
}
