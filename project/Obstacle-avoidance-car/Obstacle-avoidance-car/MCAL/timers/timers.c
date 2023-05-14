/*
 * timer.c
 *
 * Created: 4/8/2023 9:07:03 PM
 *  Author: atef
 */ 
#include "timers.h"
u32 TIMER_0_numberOfOVFs=0;
u16 g_TIMER_0_numberOfOVFs_flag=0;
/*************************Pointer to functions to be assigned to ISR*********************************/
static void (*Timer0_OVF_Fptr) (void)=NULLPTR;
static void (*Timer1_OVF_Fptr) (void)=NULLPTR;
static void (*Timer1_OCA_Fptr) (void)=NULLPTR;
static void (*Timer1_OCB_Fptr) (void)=NULLPTR;
static void (*Timer1_ICU_Fptr) (void)=NULLPTR;
/******************************************************************************************/
/*timer 0 functions*/
void timer_reset()
{
	TCCR0 &= 0x00; // clear last 3 bits (CS2:CS0) Clock selection bits
	CLR_BIT(TIFR, 0); // clear overflow flag
	TCNT0 = 0; // clear timer data
} 

 void timer_setTimerValue(u8 timerInitValue)
 {
	 TCNT0 = timerInitValue;
 }
void TIMER0_Init_all(Timer0Mode_type mode,Timer0Scaler_type scaler) //mode //scaler //start
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	TCCR0&=0XF8;//0b11111000
	TCCR0|=scaler;
} 
void TIMER0_Init(Timer0Mode_type mode) //mode
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
}
 EN_timerError_t timer_start(Timer0Scaler_type scaler) //scaler /start
{ //LCD_WriteNumber(55555);
	switch (scaler) {
		case TIMER0_STOP:
		case TIMER0_SCALER_1:
		case TIMER0_SCALER_8:
		case TIMER0_SCALER_64:
		case TIMER0_SCALER_256:
		case TIMER0_SCALER_1024:
		case EXTERNALl_FALLING:
		case EXTERNAL_RISING:
	    TCCR0&=0XF8;//0b11111000
	    TCCR0|=scaler;
		return TIMER_OK;
		default:
		return TIMER_Error;
	}
}
void TIMER0_OC0Mode(OC0Mode_type mode)
{
	switch (mode)
	{
		case OC0_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_NON_INVERTING:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		case OC0_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}

void TIMER0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void TIMER0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
}
void TIMER0_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}
////////////////////////////////////////////Timer 0 Call Back functions////////////////////////////////////////////
void TIMER0_OV_SetCallBack(void(*LocalFptr)(void))
{
	Timer0_OVF_Fptr=LocalFptr;
} 
////////////////////////////////////////////Timer 0 ISR functions////////////////////////////////////////////
ISR(TIMER0_OVF_vect)
{
	if(Timer0_OVF_Fptr!=NULLPTR)
	{
		Timer0_OVF_Fptr();
	}
}
////////////////////////////////////////////
//timer 1 functions//
/*
void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler)
{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	}

	TCCR1B&=0XF8;
	TCCR1B|=scaler;

}
void Timer1_OCRA1Mode(OC1A_Mode_type oc1a_mode)
{
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
}
void Timer1_OCRB1Mode(OC1B_Mode_type oc1b_mode)
{
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}
void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	SET_BIT(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	CLR_BIT(TCCR1B,ICES1);
}


////////////////////////////////////////////Timer 1 Interrupt functions////////////////////////////////////////////

void Timer1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1B);
}

////////////////////////////////////////////Timer 1 Call Back functions////////////////////////////////////////////

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}

////////////////////////////////////////////Timer 1 ISR functions////////////////////////////////////////////
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NULLPTR)
	{
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(Timer1_OCA_Fptr!=NULLPTR)
	{
		Timer1_OCA_Fptr();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(Timer1_OCB_Fptr!=NULLPTR)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(Timer1_ICU_Fptr!=NULLPTR)
	{
		Timer1_ICU_Fptr();
	}
}*/


///////////////////////////////////////////////////
void timer_delay(u16 Delay)
{
	double CPU_F = F_CPU;
	double oneTickTime = (8 / CPU_F ) * 1000; // in ms
	double maxDelay = oneTickTime * 256; // in ms
	int overflowsCount =(u32)((Delay / maxDelay));
	u8 timerInitValue;
	if (overflowsCount > 1)
	{
		timerInitValue = (u8)(256 - ((Delay - (maxDelay * (overflowsCount - 1))) / oneTickTime));
	}
	else
	{
		timerInitValue = (u8)((maxDelay - Delay)/oneTickTime);
	}
	TCNT0 = timerInitValue;

	timer_start(TIMER0_SCALER_8);


	while(overflowsCount--)
	{
		while((READ_BIT(TIFR, 0)) == 0);
		
		SET_BIT(TIFR, 0);
	}

	TCCR0 &= ~((1 << CS01) | (1 << CS00));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_time (u32 desiredTime){
	u32 CPU_F = F_CPU/1000000;
	u32 oneTickTime = (8 / CPU_F ); //micro
	u32 maxtime = oneTickTime * 256; // in micro
	TIMER_0_numberOfOVFs =( desiredTime*1000/ maxtime); 
   // LCD_WriteNumber( TIMER_0_numberOfOVFs);
	u8 timerInitValue; 
	if (TIMER_0_numberOfOVFs > 1)
	{
		timerInitValue = (256 - ((desiredTime - (maxtime * (TIMER_0_numberOfOVFs - 1))) / oneTickTime));
	}
	else
	{
		timerInitValue = ((maxtime - desiredTime)/oneTickTime);
	}
	
	TCNT0 = timerInitValue;
	// LCD_WriteNumber(   timerInitValue);
//	timer_start(TIMER0_SCALER_8);
	
	//LCD_WriteNumber(5);
} 



void timer_Ov()
{ static u32 S_OVC=0,f_c;
	S_OVC++ ;
	//g_TIMER_0_numberOfOVFs_flag =0;
	//LCD_WriteNumber(S_OVC);
	if (S_OVC  == TIMER_0_numberOfOVFs)
	{  		g_TIMER_0_numberOfOVFs_flag++ ;
		LCD_WriteNumber(g_TIMER_0_numberOfOVFs_flag);
		 TOGGLE_BIT(PORTB,0);
		if(Timer0_OVF_Fptr != NULLPTR)
		{
			//Timer0_OVF_Fptr();
			
		} 

		S_OVC  =	0;
		TCNT0 = 0;
		
	}
	}
	
//TIMER0_OV_SetCallBack(timer_Ov);


void stats()
{
	if(g_TIMER_0_numberOfOVFs_flag==1)
	{
		//TOGGLE_BIT(PORTB,0);
		SET_BIT(PORTB,0);
	} 
		else if(g_TIMER_0_numberOfOVFs_flag==2)
		{ //TOGGLE_BIT(PORTB,1);
			SET_BIT(PORTB,1);
		} 
				else if(g_TIMER_0_numberOfOVFs_flag==3)
				{ //TOGGLE_BIT(PORTB,2);
					SET_BIT(PORTB,2);
				}  
					else if(g_TIMER_0_numberOfOVFs_flag==4)
					{
						//TOGGLE_BIT(PORTB,0);
						CLR_BIT(PORTB,0);
					}
					else if(g_TIMER_0_numberOfOVFs_flag==5)
					{ //TOGGLE_BIT(PORTB,1);
						CLR_BIT(PORTB,1);
					}
					else if(g_TIMER_0_numberOfOVFs_flag==6)
					{ //TOGGLE_BIT(PORTB,2);
						CLR_BIT(PORTB,2);
						g_TIMER_0_numberOfOVFs_flag=0;
					}
			/*	else if(g_TIMER_0_numberOfOVFs_flag>6)
				{
					g_TIMER_0_numberOfOVFs_flag=1;
				}*/
}