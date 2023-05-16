

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#include "../../MCAL/dio/dio.h"

/*Keypad initialization error*/
typedef enum KEYPAD_initError
{
	KEYPAD_initSuccess,KEYPAD_initFail
}KEYPAD_initError;

/*Keypad read error*/
typedef enum KEYPAD_readError
{
	KEYPAD_readSuccess,KEYPAD_readFail
}KEYPAD_readError;


/******** Columns Definition *********/
#define COL_1		PIND0
#define COL_2		PIND1
#define COL_3		PIND2

/******** Rows Definition *********/
#define ROW_1		PIND3
#define ROW_2		PIND4
#define ROW_3		PIND5

/******** Buttons Definition ********/
#define BUTTON1    '1'
#define BUTTON2    '2'
#define BUTTON3    '3'
#define BUTTON4    '4'
#define BUTTON5    '5'
#define BUTTON6    '6'
#define BUTTON7    '7'
#define BUTTON8    '8'
#define BUTTON9    '9'


#endif /* KEYPAD_CONFIG_H_ */