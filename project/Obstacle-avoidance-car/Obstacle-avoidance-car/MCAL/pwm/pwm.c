/*
 * pwm.c
 *
 * Created: 5/15/2023 12:21:49 AM
 *  Author: atef
 */ 
#include "pwm.h"
u32 u32_ONTicks=0,u32_OFFTicks=0;
u8 req_value=0;
u8 u8_g_normalToPwm			=	0;

u16 u16_g_onTime, u16_g_offTime;

void waveGen()
{  static u32 OV=0;
	TCNT0=6;
	OV++;
	if (OV==(u32_OFFTicks+1))
	{
		DIO_writepin(PINB0,HIGH);//
	}
	else if (OV==(u32_ONTicks+u32_OFFTicks+2))
	{
		DIO_writepin(PINB0,LOW);//
		OV=0;
	}
	
}


void set_duty(u8 u8_DutyCycle,u32 u32_Freq,u16 u16_PRE_SCALER)
{
	f64 f64_wavePeriodTime = (f32)1 / u32_Freq;					         /* The Periodic Time for the Generated Pulse in Seconds */
	f64 f64_waveONTime = (f64_wavePeriodTime*u8_DutyCycle) / 100;		/* The HIGH Level Time in Seconds */
	f64 f64_waveOFFTime = f64_wavePeriodTime - f64_waveONTime;		   /* The LOW Level Time in Seconds */
	f64 f64_oneTickTime = 0.0;
	f64_oneTickTime =  ((f64)u16_PRE_SCALER /F_CPU );
	u32_ONTicks     =  f64_waveONTime/(f64_oneTickTime*256);
	u32_OFFTicks    =  f64_waveOFFTime/(f64_oneTickTime*256);
	/* Write the initial state of the pin to start the pulse time on it (HGIH LEVEL in this case) */
	//TCNT0 = req_value;
	//LCD_WriteNumber(req_value);
	DIO_writepin(PINB0,HIGH);
	
} 
void set_duty_hf(u8 u8_DutyCycle,u32 u32_Freq,u16 u16_PRE_SCALER)
{  
	 f64 f64_oneTickTime = 0.0;  
	f64_oneTickTime =  ((f64)u16_PRE_SCALER /F_CPU );
	f64 f64_wavePeriodTime = (f32)1 / u32_Freq;
	f64 f64_waveticks=f64_wavePeriodTime/f64_oneTickTime;
	LCD_WriteNumber((f64_waveticks ));
	f64 f64_waveONTime = (f64_wavePeriodTime*u8_DutyCycle) / 100;		/* The HIGH Level Time in Seconds */
	f64 f64_waveOFFTime = f64_wavePeriodTime - f64_waveONTime;		   /* The LOW Level Time in Seconds */
	u32_ONTicks     = (u8_DutyCycle*f64_waveticks)/100;
	u32_OFFTicks    =  f64_waveticks-u32_ONTicks;
	/* Write the initial state of the pin to start the pulse time on it (HGIH LEVEL in this case) */
	TCNT0 = 256-u32_OFFTicks;	
	DIO_writepin(PINB0,HIGH);
	
}


void waveGen2()
{ 
	 static u8 flag=0;

	if (flag==0)
	{ 
		DIO_writepin(PINB0,HIGH);	
		    
			TCNT0 = 256-u32_ONTicks ;
			
			flag=1;
	}
	else if (flag==1)
	{
		DIO_writepin(PINB0,LOW);
		TCNT0 = 256-u32_OFFTicks;
		
		flag=0;
	}
	
}


void TIMER_pwmGenerator(u32 u32_a_desiredDutyCycle)
{
	static u8 flag = 0;
	
		u16_g_onTime		= ((u32_a_desiredDutyCycle * 256)/100);
		u16_g_offTime	= 256 - u16_g_onTime;
		if (flag == 0)
		{
			TCNT0 = 256 - u16_g_onTime;
			flag = 1;
		}
		
	
}