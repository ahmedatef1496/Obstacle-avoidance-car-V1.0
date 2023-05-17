// /*
//  * ultrasonic.c
//  *
//  * Created: 5/16/2023 2:42:01 PM
//  *  Author: atef
//  */ 
// #include "ultrasonic.h"
// 
//  void Func_US_exi(void)
//  {
// 	 if (flag==0)
// 	 {
// 		 t1=TCNT1;
// 		 EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
// 		 flag=1;
// 	 }
// 	 else if (flag==1)
// 	 {
// 		 t2=TCNT1;
// 		 flag=2;
// 	 }
//  }
//  
//  
//  void US_test_exi()
//  {
// 	 u8 duty;
// 	 u32 frq;
// 	 u16 time,d;
// 	 DIO_initpin(PINB3,OUTPUT);
// 	 DIO_initpin(PINB2,INFREE);
// 	 Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
// 	 EXI_Enable(EX_INT2);
// 	 TCNT1=0;
// 	 LCD_WriteString("US");
// 	 EXI_SetCallBack(EX_INT2,Func_US_exi);
// 	 EXI_TriggerEdge(EX_INT2,RISING_EDGE);
// 	 
// 	 
// 	 
// 	 while(1)
// 	 {
// 		 TCNT1=0;
// 		 flag=0;
// 		 EXI_TriggerEdge(EX_INT2,RISING_EDGE);
// 		 DIO_writepin(PINB3,HIGH);
// 		 _delay_us(10);
// 		 DIO_writepin(PINB3,LOW);
// 		 while(flag<2);
// 		 time=(t2-t1);
// 		 d=(time/58);
// 		 LCD_SetCursor(1,0);
// 		 LCD_WriteNumber(d);
// 		 _delay_ms(10);
// 		 
// 		 
// 	 }
//  }
//  
//  
//  void Func_US(void)
//  {
// 	 if (flag==0)
// 	 {
// 		 t1=ICR1;
// 		 Timer1_InputCaptureEdge(FALLING);
// 		 flag=1;
// 	 }
// 	 else if (flag==1)
// 	 {
// 		 t2=ICR1;
// 		 flag=2;
// 	 }
//  }
//  
//  
//  void US_test()
//  {
// 	 u8 duty;
// 	 u32 frq;
// 	 u16 time,d;
// 	 DIO_initpin(PIND2,OUTPUT);
// 	 DIO_initpin(PIND6,INFREE);
// 	 Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
// 	 TCNT1=0;
// 	 LCD_WriteString("US");
// 	 Timer1_ICU_SetCallBack(Func_US);
// 	 Timer1_InputCaptureEdge(RISING);
// 	 Timer1_ICU_InterruptEnable();
// 	 
// 	 
// 	 while(1)
// 	 {
// 		 TCNT1=0;
// 		 flag=0;
// 		 Timer1_InputCaptureEdge(RISING);
// 		 DIO_writepin(PIND2,HIGH);
// 		 _delay_us(10);
// 		 DIO_writepin(PIND2,LOW);
// 		 while(flag<2);
// 		 
// 		 {
// 			 LCD_SetCursor(1,10);
// 			 LCD_WriteNumber(flag);
// 		 }
// 		 time=(t2-t1);
// 		 d=(time/58)/2;
// 		 LCD_SetCursor(1,0);
// 		 LCD_WriteNumber(d);
// 		 _delay_ms(10);
// 		 
// 		 
// 	 }
//  }
