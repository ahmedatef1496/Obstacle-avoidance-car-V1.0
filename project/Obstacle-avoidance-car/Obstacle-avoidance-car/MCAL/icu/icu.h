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





#define  ICU_EXI_INT  EX_INT2
void    ICU_init ();
u8 ICU_Read(u16 *pu16_PeriodTime);
#endif /* ICU_H_ */