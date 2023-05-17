/*
 * app.c
 *
 * Created: 5/16/2023 11:50:50 PM
 *  Author: atef
 */ 
#include "app.h"
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

}

u8 X ;

void pwm_test()
{       
	
	PWM_set_duty(90,100);
	timer_start(TIMER0_SCALER_8);
	Car_Moving_FWD();
	
}
void app_start()
{
	KEYPAD_getpressedkey(&X);
	LCD_Clear();
	LCD_WriteNumber(X);
}