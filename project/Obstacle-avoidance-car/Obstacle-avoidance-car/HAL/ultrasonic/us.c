/*
 * us.c
 *
 * Created: 5/17/2023 3:42:42 PM
 *  Author: atef
 */ 

#include "us.h"


volatile u8 flag=0;
volatile u16 t1,t2,t3;

void USCallBackFun(void)
{
	if (flag==0)
	{
		t1=TCNT1;
		EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
		flag=1;
	}
	else if (flag==1)
	{
		t2=TCNT1;
		flag=2;
	}
}
u16 US_getdistance(void)
{
	u8 duty;
	u32 frq;
	u16 time, u16_d;
	
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	EXI_Enable(EX_INT2);
	TCNT1=0;
	EXI_SetCallBack(EX_INT2, USCallBackFun);
	EXI_TriggerEdge(EX_INT2,RISING_EDGE);
	
	
	
	while(1)
	{
		TCNT1=0;
		flag=0;
		EXI_TriggerEdge(EX_INT2,RISING_EDGE);
		DIO_writepin(PINB3,HIGH);
		_delay_us(10);
		DIO_writepin(PINB3,LOW);
		while(flag<2);
		time=(t2-t1);
		u16_d=(time/58);
		return u16_d;		
	}
}