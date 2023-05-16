/*
 * pwm.h
 *
 * Created: 5/15/2023 12:22:05 AM
 *  Author: atef
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "utils.h"
#include "memmap.h"
#include "std_typs.h"
#include "timer.h"
#include "pwm_lcfg.h"
#include "lcd.h"
#include "dio.h"

typedef struct
{
	DIO_Pin_type ChannelID;
	u32  u32_ONTicks;
	u32  u32_OFFTicks;
	u32  u32_NxtTicks;

}st_Pwm_ChannelData_t;


void waveGen();
void waveGen2();
void set_duty(u8 u8_DutyCycle,u32 u32_Freq,u16 u16_PRE_SCALER);
void set_duty_hf(u8 u8_DutyCycle,u32 u32_Freq,u16 u16_PRE_SCALER);

#endif /* PWM_H_ */