/*
 * icu.h
 *
 * Created: 5/16/2023 12:00:37 AM
 *  Author: atef
 */ 


#ifndef ICU_H_
#define ICU_H_

#include "../timers/timer.h"
#include "../Interrupt/exi.h"

#define ICU_CH     PINB2 


void PWM_Measure(u32* Pfreq,u8* Pduty);
static void Func_ICU(void);
void PWM_Measure_exi(u32* Pfreq,u8* Pduty);
static void Func_ICU_exi(void);
void ICU_SW(u32* Pfreq,u8* Pduty);
#endif /* ICU_H_ */