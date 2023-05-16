/*
 * motor.c
 *
 * Created: 15-May-23 4:13:12 PM
 *  Author: Amr
 */ 


#include "motor.h"
/*********************************func_implementation********************************************************/
/**DESCRIPTION:-
  this function initializes the DIO pins connected to the motors to be output
  **/
en_MotorError_t Car_Motors_init (void)
{
	DIO_initpin(motor1_0,OUTPUT);
	DIO_initpin(motor1_1,OUTPUT);
	DIO_initpin(motor2_0,OUTPUT);
	DIO_initpin(motor2_1,OUTPUT);

	return motor_ok;
}


/**************************************************************************************************************/
/**DESCRIPTION:-
this function is used to drive the motor to move in the +VE direction which will lead the car to move FWD
**/
en_MotorError_t Car_Moving_FWD(void)
{
	DIO_writepin(motor1_0,LOW);          //this is used to provide voltage to the +ve pin of the motor 
	DIO_writepin(motor1_1,HIGH);           //this is used to provide the ground to the -ve pin of 
	DIO_writepin(motor2_0,LOW);
	DIO_writepin(motor2_1,HIGH);
	
	return motor_ok;

}

/**************************************************************************************************************/
/**DESCRIPTION:-
this function is used to drive the motor to move in the -VE direction which will lead the car to move BWD
**/
en_MotorError_t Car_Moving_BWD(void)
{
	DIO_writepin(motor1_0,HIGH);          //this is used to provide voltage to the -ve pin of the motor
	DIO_writepin(motor1_1,LOW);           //this is used to provide the ground to the +ve pin of
	DIO_writepin(motor2_0,HIGH);
	DIO_writepin(motor2_1,LOW);
	
	return motor_ok;
}


/***********************************************************************************************************************/
/**DESCRIPTION:-
this function is used to stop the 4 wheels by stopping the 4 motors*/
en_MotorError_t Car_Stop(void)
{
	
	
  DIO_writepin(motor1_0,LOW);          
  DIO_writepin(motor1_1,LOW);           
  DIO_writepin(motor2_0,LOW);
  DIO_writepin(motor2_1,LOW);

	return motor_ok;
}

/***********************************************************************************************************************/
/**DESCRIPTION:-
this function is used to drive the right wheels to move BWD, and the left wheels to move FWD,
which will lead to rotation of the car */
en_MotorError_t Car_Rotate_Right(void)
{
	//this is used to provide the ground to the -ve pin of
	DIO_writepin(motor1_0,HIGH);
	DIO_writepin(motor1_1,LOW);
	
	//this is used to provide voltage to the +ve pin of the motor
	DIO_writepin(motor2_0,LOW);
	DIO_writepin(motor2_1,HIGH);

	return motor_ok;
}

/***********************************************************************************************************************/
/**DESCRIPTION:-
this function is used to drive the right wheels to move FWD, and the left wheels to move BWD,
which will lead to rotation of the car */
en_MotorError_t Car_Rotate_Left(void)
{
	//this is used to provide the ground to the +ve pin of
	DIO_writepin(motor1_0,LOW);
	DIO_writepin(motor1_1,HIGH);
	
	//this is used to provide voltage to the -ve pin of the motor
	DIO_writepin(motor2_0,HIGH);
	DIO_writepin(motor2_1,LOW);

	return motor_ok;
}