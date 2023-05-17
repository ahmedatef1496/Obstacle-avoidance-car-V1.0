/*
 * CFile1.c
 *
 * Created: 4/1/2023 3:51:57 PM
 *  Author: atef
 */
#define  F_CPU  16000000
#include <util/delay.h>

#include "LCD_Cfg.h"
#include "lcd.h"

#if LCD_MODE==_8_BIT
static void WriteIns(u8 ins)
{
	
	DIO_writepin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_writepin(EN,HIGH);
	_delay_ms(1);
	DIO_writepin(EN,LOW);
	_delay_ms(1);
	
}

static void WriteData(u8 data)
{
	DIO_writepin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_writepin(EN,HIGH);
	_delay_ms(1);
	DIO_writepin(EN,LOW);
	_delay_ms(1);
}



void LCD_Init(void)
{
	_delay_ms(50);
	
	WriteIns(0x38);//5*7 2 lines
	WriteIns(0x0c);//0x0c,0x0e,0x0f cursor
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);// increment DDRAM address, no shift
	CLR_BIT(PORTA,2);
	
}

#elif LCD_MODE ==_4_BIT
static void WriteIns(u8 ins)
{
	
	
	DIO_writepin(RS,LOW);
	DIO_writepin(D7,READ_BIT(ins,7));
	DIO_writepin(D6,READ_BIT(ins,6));
	DIO_writepin(D5,READ_BIT(ins,5));
	DIO_writepin(D4,READ_BIT(ins,4));
	
	DIO_writepin(EN,HIGH);
	_delay_ms(1);
	DIO_writepin(EN,LOW);
	_delay_ms(1);
	DIO_writepin(D7,READ_BIT(ins,3));
	DIO_writepin(D6,READ_BIT(ins,2));
	DIO_writepin(D5,READ_BIT(ins,1));
	DIO_writepin(D4,READ_BIT(ins,0));
	DIO_writepin(EN,HIGH);
	_delay_ms(1);
	DIO_writepin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	DIO_writepin(RS,HIGH);
	DIO_writepin(D7,READ_BIT(data,7));
	DIO_writepin(D6,READ_BIT(data,6));
	DIO_writepin(D5,READ_BIT(data,5));
	DIO_writepin(D4,READ_BIT(data,4));

	DIO_writepin(EN,HIGH);
	_delay_ms(1);
	DIO_writepin(EN,LOW);
	_delay_ms(1);
	DIO_writepin(D7,READ_BIT(data,3));
	DIO_writepin(D6,READ_BIT(data,2));
	DIO_writepin(D5,READ_BIT(data,1));
	DIO_writepin(D4,READ_BIT(data,0));
	DIO_writepin(EN,HIGH);
	_delay_ms(1);
	DIO_writepin(EN,LOW);
	_delay_ms(1);
}



void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);//5*7 2 lines
	WriteIns(0x0c);//0x0c,0x0e,0x0f cursor
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);// increment DDRAM address, no shift
	
}

#endif

//should be send address in ddram befor this function
void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}
void LCD_WriteString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
	
}
void LCD_SetCursor(u8 line,u8 cell)
{
	if (line==0)
	{
		WriteIns(0x80|cell);
	}
	else if (line ==1)
	{
		WriteIns(0x80+0x40+cell);
	}
	
}
void LCD_Clear(void)
{
	WriteIns(CLR_INS);
	_delay_ms(1);
}


void LCD_WriteNumber(s32 num)
{
	u8 str[10],i=0,j;
	if (num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if (num<0)
	{
		num=num*(-1);
		LCD_WriteChar('-');
	}
	
	while(num)
	{
		str[i]=num%10 +'0';
		i++;
		num=num/10;
	}
	for (j=i;j>0;j--)
	{
		LCD_WriteChar(str[j-1]);
	}

}


void LCD_WriteBinary(u8 num)
{
	s8 i;
	for (i=7;i>=0;i--)
	{
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
	
}


void LCD_ClearLoc(u8 line ,u8 cell,u8 num)
{
	u8 i;
	LCD_SetCursor(line,cell);
	for (i=0;i<num;i++)
	{
		LCD_WriteChar(' ');
	}
	
}


void LCD_WriteNumber_3D(u16 num)
{
	//LCD_WriteChar(((num%100000)/10000)+'0');
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}


void LCD_CustomChar(u8 loc,u8*pattern)
{
	WriteIns(0x40+loc*8);
	for(u8 i=0;i<8;i++)
	{
		WriteData(pattern[i]);
	}
	WriteIns(0x80);
}
   void LCD_PinsInit ()
   {
	   DIO_initpin(RS,OUTPUT);
	   DIO_initpin(EN,OUTPUT);
	   DIO_initpin(RW,OUTPUT);
	   DIO_initpin(D4,OUTPUT);
	   DIO_initpin(D5,OUTPUT);
	   DIO_initpin(D6,OUTPUT);
	   DIO_initpin(D7,OUTPUT);

   }