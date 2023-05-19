/*
 * app.c
 *
 * Created: 5/16/2023 11:50:50 PM
 *  Author: atef
 */ 
#include "app.h"

volatile u16 g_distance;
u8 g_counter=4, g_start_Flag=1, lcdFlag = 0, lcdFlag2 = 0;
s32 ovf;



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
		_delay_ms(3000);
}

void car_Backword_30()
{
	while (g_distance <= 20)
	{
		US_getdistance(&g_distance);
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
	_delay_ms(1000);
}

void Speed_50_check()
{
	if(g_speed_flag == 1)
	{
		
		if (ovf < mode_ovf ){
			ovf++;
		}
		else if ( ovf == mode_ovf && mode_ovf!=0)
		{
			ovf =0 ;
			if (car_mode ==0)
			{
				car_mode=1;
			}
			
		}
	}
}

void startStage(void) 
{
    u8 keyPressed = 0;								//Used to store the value of the key pressed 
	volatile u8 buttonCounter = 0;
	Button_State buttonState = 0;


	do {							
		KEYPAD_getpressedkey(&keyPressed);
		} while (keyPressed != '1');				//Key 1 is pressed. 
	
	LCD_WriteString("Set Def Rot");
	LCD_SetCursor(1, 0);
	LCD_WriteString("Right");
	
	mode_ovf = 200000;								//starts 5 seconds timer in ISR
	g_speed_flag = 1;
	
	while (car_mode == 0)
	{
		Is_pressed(BUTTON_PIN, &buttonState);
			if (buttonState == pressed)
			{
				buttonCounter++;
				while (buttonState == pressed) {
					Is_pressed(BUTTON_PIN, &buttonState);
				}
			}
			if ( (buttonCounter % 2 == 0 || buttonCounter == 0) && lcdFlag == 0 )
			{
				LCD_Clear();
				LCD_WriteString("Set Def. Rot.");
				LCD_SetCursor(1, 0);
				LCD_WriteString("Right");
				lcdFlag = 1;
				lcdFlag2 = 0;
			} 
			else if (lcdFlag2 == 0 && buttonCounter % 2 != 0)
				{
					LCD_Clear();
					LCD_WriteString("Set Def. Rot.");
					LCD_SetCursor(1, 0);
					LCD_WriteString("Left");
					lcdFlag2 = 1;
					lcdFlag = 0;
				}
	}
	_delay_ms(2000);
	g_start_Flag = 1;
	car_mode =0;
	mode_ovf =0;
	g_speed_flag=0;
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
	US_init();
	TIMER_2_INT();
	TIMER2_OV_SetCallBack(Speed_50_check);
}

void app_start()
{
	startStage();
	
	
	while (g_start_Flag)
	{
		US_getdistance(&g_distance);
		if (g_distance > 70 && car_mode == 0)
		{
			car_Forward_30();
			g_speed_flag = 1;
			mode_ovf = 100000;
		}
		else if (car_mode == 1 && g_distance > 70)
		{
			car_Forward_50();
		}
		else if (g_distance <= 70 && g_distance > 30)
		{
			car_mode = 0;
			mode_ovf=0;
			car_Forward_30();
		}
		else if (g_distance <= 30 && g_distance > 20)
		{
			Car_Stopping();
			car_Rotating();
		}
		else if (g_distance <= 20)
		{
			Car_Stopping();
			car_Backword_30();
		}
	}
}