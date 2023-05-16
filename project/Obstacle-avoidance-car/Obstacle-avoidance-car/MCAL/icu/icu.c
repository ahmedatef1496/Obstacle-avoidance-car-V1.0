/*
 * icu.c
 *
 * Created: 5/16/2023 12:00:50 AM
 *  Author: atef
 */ 

#include "icu.h"
static volatile u16 t1,t2,t3,flag=0,ICU_flag=0;

void PWM_Measure(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;

	TCNT1=0;
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	flag=0;
	while(flag<3);//busy w8
	Ton=t2-t1;
	Toff=t3-t2;
// 	LCD_SetCursor(1,0);
// 	LCD_WriteNumber(Ton);
// 	LCD_SetCursor(1,7);
// 	LCD_WriteNumber(Toff);
	*Pduty=((u32)Ton*100)/((u32)Ton+Toff);
	*Pfreq=(u32)1000000/(((u32)Toff+Ton)/2);  //2 IN CASE OF 16 

}

static void Func_ICU(void)
{ 
	 
	if (flag==0)
	{
		t1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if (flag==1)
	{
		t2=ICR1;
		Timer1_InputCaptureEdge(RISING);
		flag=2;
	}
	else if (flag==2)
	{
		t3=ICR1;
		Timer1_ICU_InterruptDisable();
		flag=3;
		
	}

}

void PWM_Measure_exi(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;

	TCNT1=0;
	EXI_SetCallBack(EX_INT2,Func_ICU_exi);
	EXI_TriggerEdge(EX_INT2,RISING_EDGE);
	EXI_Enable(EX_INT2);
	flag=0;
	while(flag<3);
	Ton=t2-t1;
	Toff=t3-t2;
	*Pduty=((u32)Ton*100)/((u32)Ton+Toff);
	*Pfreq=(u32)1000000/(((u32)Toff+Ton));  //2 IN CASE OF 16

}

static void Func_ICU_exi(void)
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
		EXI_TriggerEdge(EX_INT2,RISING_EDGE);
		flag=2;
	}
	else if (flag==2)
	{
		t3=TCNT1;
		EXI_Disable(EX_INT2);
		flag=3;
		
	}

}
/************************************************************************/
/*                                                                      */
/************************************************************************/

void ICU_init ()
{
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	DIO_initpin(ICU_CH,INFREE);
}

static void ICU_GetPeriod(void)
{
	
	if (ICU_flag==0)
	{
	/* Get the counter value */
		t1=TCNT1;
	/* Reverse the external interrupt polarity */
		EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
	/* change ICU_flag to next period */
		ICU_flag=1;
	}
	else if (ICU_flag==1)
	{
		t2=TCNT1;
		EXI_TriggerEdge(EX_INT2,RISING_EDGE);
		ICU_flag=2;
	}
	else if (ICU_flag==2)
	{
		t3=TCNT1;
		EXI_Disable(EX_INT2);
		ICU_flag=3;
		
	}

}

void ICU_SW(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;
	TCNT1=0;
	EXI_SetCallBack(EX_INT2,ICU_GetPeriod);
	EXI_TriggerEdge(EX_INT2,RISING_EDGE);
	EXI_Enable(EX_INT2);
	ICU_flag=0;
	while(ICU_flag<3);
	Ton=t2-t1;
	Toff=t3-t2;
	*Pduty=((u32)Ton*100)/((u32)Ton+Toff);
	*Pfreq=(u32)1000000/(((u32)Toff+Ton))*2;  //*2 IN CASE OF 16

} 
