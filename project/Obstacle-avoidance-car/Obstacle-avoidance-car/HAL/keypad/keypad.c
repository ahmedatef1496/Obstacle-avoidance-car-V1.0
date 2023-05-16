

#include "keypad_config.h"
#include "keypad_interface.h"

u8 Col_Arr[KEYPAD_COLUMNS] = {COL_1, COL_2, COL_3};
u8 Row_Arr[KEYPAD_ROWS] = {ROW_1, ROW_2, ROW_3};
static u8 Button_Arr[KEYPAD_ROWS][KEYPAD_COLUMNS] =
	{
		// COLUMN 1
		{BUTTON1, BUTTON2, BUTTON3},
		// COLUMN 2
		{BUTTON4, BUTTON5, BUTTON6},
		// COLUMN 3
		{BUTTON7, BUTTON8, BUTTON9}};
			
KEYPAD_initError KEYPAD_init(void){
	
	/*Set Column Initial Values to 1 */
	DIO_writepin (COL_1,HIGH);
	DIO_writepin (COL_2,HIGH);
	DIO_writepin (COL_3,HIGH);
	
	/* Enable Pull Up Resistors at Input Rows */
	DIO_writepin (ROW_1,HIGH);
	DIO_writepin (ROW_2,HIGH);
	DIO_writepin (ROW_3,HIGH);
	
	return KEYPAD_initSuccess;
	
}


KEYPAD_readError KEYPAD_getpressedkey(u8 *value){

	// Scan all keypad rows
	for (u8 counter_row = 0; counter_row < KEYPAD_ROWS; counter_row++)
	{
		 // set current column pin low to test all row pins to find out which button has been pressed
		DIO_writepin (Row_Arr[counter_row],LOW);
		
		//scan and test all keypad columns pins
		 for (u8 counter_col = 0; counter_col < KEYPAD_COLUMNS; counter_col++)
		 {
			 
			 // check col value if it is 0 then this column and row is connected
			 DIO_readpin (Col_Arr[counter_col],value);
			 
			 if(*value == 0){
				 
				 *value= Button_Arr[counter_row][counter_col];
				 DIO_writepin (Row_Arr[counter_row],HIGH);
				  return KEYPAD_readSuccess;
				
			 }

		}
		
		// set current row pin HIGH again
		DIO_writepin (Row_Arr[counter_row],HIGH);

	}
	
	return KEYPAD_readFail;

}
