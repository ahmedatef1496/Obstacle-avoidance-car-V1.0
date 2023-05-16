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
}


void pwm_test()
{       
	
	PWM_set_duty(20,100);
	timer_start(TIMER0_SCALER_8);
	
}