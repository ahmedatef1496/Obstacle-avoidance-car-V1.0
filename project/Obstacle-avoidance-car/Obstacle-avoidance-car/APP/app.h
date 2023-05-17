/*
 * app.h
 *
 * Created: 5/16/2023 11:44:40 PM
 *  Author: atef
 */ 


#ifndef APP_H_
#define APP_H_
#include "../HAL/lcd/lcd.h"
#include "../MCAL/pwm/pwm.h"
#include "../HAL/keypad/keypad_interface.h"
#include "../HAL/button/button_interface.h"
#include "../HAL/lcd/lcd.h"
#include "../HAL/motor/motor.h"
#include "../MCAL/dio/dio.h"


void app_init();
void pwm_test();

#endif /* APP_H_ */