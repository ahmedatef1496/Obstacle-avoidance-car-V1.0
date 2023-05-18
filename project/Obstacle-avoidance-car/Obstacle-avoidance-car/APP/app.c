/*
 * app.c
 *
 * Created: 5/16/2023 11:50:50 PM
 *  Author: atef
 */ 
#include "app.h"

volatile u16 g_distance;
u8 g_counter=4, g_start_Flag=1;




void car_Forward_30()
{	
	LCD_Clear();
	PWM_set_duty(30,100);
	timer_start(TIMER0_SCALER_8);
	Car_Moving_FWD();
	LCD_SetCursor(0,0);
	LCD_WriteString("Speed:30% Dir:	F");
	LCD_SetCursor(1,0);
	LCD_WriteString("Dist.:");
	LCD_WriteNumber(g_distance);
	LCD_WriteString(" Cm");
}

void car_Forward_50()
{
	LCD_Clear();
	PWM_set_duty(50,100);
	timer_start(TIMER0_SCALER_8);
	Car_Moving_FWD();
	LCD_SetCursor(0,0);
	LCD_WriteString("Speed:50% Dir:	F");
	LCD_SetCursor(1,0);
	LCD_WriteString("Dist.:");
	LCD_WriteNumber(g_distance);
	LCD_WriteString(" Cm");
}

void car_Rotating()
{
	LCD_Clear();
	PWM_set_duty(30,100);
	timer_start(TIMER0_SCALER_8);
	LCD_SetCursor(0,0);
	LCD_WriteString("Speed:30% Dir:	R");
	LCD_SetCursor(1,0);
	LCD_WriteString("Dist.:");
	LCD_WriteNumber(g_distance);
	LCD_WriteString(" Cm");
	if (g_counter %2 == 0)
	{
		Car_Rotate_Right();
	}
	else
	{
		Car_Rotate_Left();
	}
}


void car_Backword_30()
{
	LCD_Clear();
	PWM_set_duty(30,100);
	timer_start(TIMER0_SCALER_8);
	Car_Moving_BWD();
	LCD_SetCursor(0,0);
	LCD_WriteString("Speed:30% Dir:	B");
	LCD_SetCursor(1,0);
	LCD_WriteString("Dist.:");
	LCD_WriteNumber(g_distance);
	LCD_WriteString(" Cm");
}


void Car_Stopping()
{
	LCD_Clear();
	PWM_set_duty(0,100);
	timer_start(TIMER0_SCALER_8);
	Car_Stop();
	LCD_SetCursor(0,0);
	LCD_WriteString("Speed:00% Dir:	S");
	LCD_SetCursor(1,0);
	LCD_WriteString("Dist.:");
	LCD_WriteNumber(g_distance);
	LCD_WriteString(" Cm");
}



void app_init()
{
	LCD_PinsInit();
	LCD_Init();
	GLOBALE_ENABLE();
	pwm_init();
	Car_Motors_init();
	LCD_Init();
	KEYPAD_init();
	DIO_initpin(PIND6,INPULL);
	DIO_Init_All();
	TIMER_2_INT();
}

void app_start()
{
	//Start_stage();
	
	
	while (g_start_Flag)
	{
		g_distance = US_getdistance();
		if (g_distance > 70 && car_mode == 0)
		{
			car_Forward_30();
			mode_ovf = 100;
		}
		else if (car_mode == 1 && g_distance > 70)
		{
			car_Forward_50();
		}
		else if (g_distance <= 70 && g_distance > 30)
		{
			car_Forward_30();
		}
		else if (g_distance <= 30 && g_distance > 20)
		{
			Car_Stopping();
			_delay_ms(4000);
			car_Rotating();
			_delay_ms(5000);

		}
		else if (g_distance <= 20)
		{
			Car_Stopping();
			_delay_ms(4000);
			car_Backword_30();
			_delay_ms(5000);
		}
	}
}