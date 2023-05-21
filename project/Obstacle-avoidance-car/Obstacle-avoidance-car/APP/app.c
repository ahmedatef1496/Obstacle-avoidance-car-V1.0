/*
 * app.c
 *
 * Created: 5/16/2023 11:50:50 PM
 *  Author: atef
 */ 
#include "app.h"


/*****************************************************************************************************************************
*							Global Variables						     *
*****************************************************************************************************************************/

volatile u16 g_distance;
u8 g_start_Flag=1, lcdFlag = 0, lcdFlag2 = 0;
static u8 g_keyPressed = 0;								//Used to store the value of the key pressed 
volatile u8 g_buttonCounter = 0;
static u32 ovf =0;
static u8 g_Rotate_Counter;


/***********************************************************************************************************************************************
		This function is used to check if the STOP button is pressed or not and display this on the LCD.
/***********************************************************************************************************************************************/
void STOP_check (void)
{
	KEYPAD_getpressedkey(&g_keyPressed);
	if (g_keyPressed == '2')
	{
		LCD_Clear();
		LCD_SetCursor(0,4);
		LCD_WriteString("STOPPED!");
		Car_Stop();
		do {
			KEYPAD_getpressedkey(&g_keyPressed);
		} while (g_keyPressed != '1');				//Key 1 is pressed.
	}
}


/***********************************************************************************************************************************************
This function is used to set the direction of the car to forward and set the speed of it to 30% of the max speed and display this on the LCD.
/***********************************************************************************************************************************************/
void car_Forward_30()
{	
	PWM_set_duty(30,100);
	Car_Moving_FWD();
	LCD_SetCursor(0,0);
	LCD_WriteString("Speed:30% Dir:	F");
	LCD_SetCursor(1,0);
	LCD_WriteString("Dist.:");
	LCD_WriteNumber(g_distance);
	LCD_WriteString(" Cm");
}


/***********************************************************************************************************************************************
This function is used to set the direction of the car to forward and set the speed of it to 50% of the max speed and display this on the LCD.
/***********************************************************************************************************************************************/
void car_Forward_50()
{
	PWM_set_duty(50,100);
	Car_Moving_FWD();
	LCD_SetCursor(0,0);
	LCD_WriteString("Speed:50% Dir:	F");
	LCD_SetCursor(1,0);
	LCD_WriteString("Dist.:");
	LCD_WriteNumber(g_distance);
	LCD_WriteString(" Cm");
}


/***********************************************************************************************************************************************
This function is used to set the direction of the car to be rotating and set the speed of it to 30% of the max speed and display this on the LCD.
/***********************************************************************************************************************************************/
void car_Rotating()
{	
	while (car_mode == 0 && (g_distance <= 30 && g_distance > 20))
	{
		
		US_getdistance(&g_distance);
		STOP_check ();
		PWM_set_duty(30,100);
		LCD_SetCursor(0,0);
		LCD_WriteString("Speed:30% Dir:	R");
		LCD_SetCursor(1,0);
		LCD_WriteString("Dist.:");
		LCD_WriteNumber(g_distance);
		LCD_WriteString(" Cm");
		if (g_buttonCounter %2 == 0)
		{
			Car_Rotate_Right();
		}
		else
		{
			Car_Rotate_Left();
		}
	}
}


/***********************************************************************************************************************************************
This function is used to set the direction of the car to backward and set the speed of it to 30% of the max speed and display this on the LCD.
/***********************************************************************************************************************************************/
void car_Backword_30()
{
	while (g_distance <= 20)
	{
		STOP_check();
		US_getdistance(&g_distance);
		PWM_set_duty(30,100);
		Car_Moving_BWD();
		LCD_SetCursor(0,0);
		LCD_WriteString("Speed:30% Dir:	B");
		LCD_SetCursor(1,0);
		LCD_WriteString("Dist.:");
		LCD_WriteNumber(g_distance);
		LCD_WriteString(" Cm");
	}
	
}


/*****************************************************************************************************************************
			This function is used to set the car to 0 and display this on the LCD.
/*****************************************************************************************************************************/
void Car_Stopping()
{
	PWM_set_duty(0,100);
	Car_Stop();
	LCD_SetCursor(0,0);
	LCD_WriteString("Speed:00% Dir:	S");
	LCD_SetCursor(1,0);
	LCD_WriteString("Dist.:");
	LCD_WriteNumber(g_distance);
	LCD_WriteString(" Cm");
}


/*****************************************************************************************************************************
		This function is used to set the timers functionalities needed within the application.
/*****************************************************************************************************************************/
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


					/********************************************/
/*****************************************************************************************************************************
			This function is used to initialize our peripherals used in the application.
/*****************************************************************************************************************************/
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


/***********************************************************************************************************************************************
	This function is the first stage in the mainflow of our program, it contains the welcome messege and the direction set option.
/***********************************************************************************************************************************************/
void startStage(void) 
{	
	Button_State buttonState = 0;


	do {
		LCD_SetCursor(0,4);
		LCD_WriteString("WELCOME!");
		LCD_SetCursor(1, 0);
		LCD_WriteString("press 1 to start");				
		KEYPAD_getpressedkey(&g_keyPressed);
		} while (g_keyPressed != '1');				//Key 1 is pressed. 
	
	LCD_SetCursor(0, 0);
	LCD_WriteString("Set Def Rot     ");
	LCD_SetCursor(1, 0);
	LCD_WriteString("Right           ");
	
	ovf = 0;
	mode_ovf = 156250;								//starts 5 seconds timer in ISR
	g_speed_flag = 1;
	
	while (car_mode == 0)
	{
		Is_pressed(BUTTON_PIN, &buttonState);
			if (buttonState == pressed)
			{
				g_buttonCounter++;
				while (buttonState == pressed) {
					Is_pressed(BUTTON_PIN, &buttonState);
				}
			}
			if ( (g_buttonCounter % 2 == 0 || g_buttonCounter == 0) && lcdFlag == 0 )
			{
				LCD_SetCursor(0, 0);
				LCD_WriteString("Set Def. Rot.");
				LCD_SetCursor(1, 0);
				LCD_WriteString("Right");
				lcdFlag = 1;
				lcdFlag2 = 0;
			} 
			else if (lcdFlag2 == 0 && g_buttonCounter % 2 != 0)
				{
					LCD_SetCursor(0, 0);
					LCD_WriteString("Set Def. Rot.");
					LCD_SetCursor(1, 0);
					LCD_WriteString("Left ");
					lcdFlag2 = 1;
					lcdFlag = 0;
				}
	}
	_delay_ms(1000);
	g_start_Flag = 1;
	car_mode =0;
	mode_ovf =0;
	g_speed_flag=0;
	ovf = 0;
}


/***********************************************************************************************************************************************
This function is an infinite loop used for the project sequence logic and achieving the functionalities requried according to distance readings.
/***********************************************************************************************************************************************/
void app_start()
{
	
	startStage();
	
	
	while (g_start_Flag)
	{
		STOP_check ();
		US_getdistance(&g_distance);
		if (g_distance > 70 && car_mode == 0)
		{
			car_Forward_30();
			g_speed_flag = 1;
			mode_ovf = 156250;								//starts 5 sec. timer to increase the speed
		}
		else if (car_mode == 1 && g_distance > 70)
		{
			car_Forward_50();
		}
		else if (g_distance <= 70 && g_distance > 30)
		{
			car_mode = 0;
			mode_ovf=0;
			ovf = 0;
			g_speed_flag =0;
			g_Rotate_Counter = 0;
			car_Forward_30();
		}
		else if (g_distance <= 30 && g_distance > 20)
		{
			Car_Stopping();
			g_speed_flag = 1;
			ovf = 0;
			mode_ovf = 62500;								//starts timer for 90 degree rotation
					
			car_Rotating();
						
			car_mode = 0;
			mode_ovf = 0;
			g_speed_flag = 0;
			g_Rotate_Counter++;
			if (g_Rotate_Counter == 4)
			{
				while (g_distance <= 30 && g_distance > 20)
				{
					US_getdistance(&g_distance);
					Car_Stopping();
				}
				
			}
		}
		
		else if (g_distance <= 20)
		{
			g_Rotate_Counter = 0;
			Car_Stopping();
			car_Backword_30();
		}
	}
}
