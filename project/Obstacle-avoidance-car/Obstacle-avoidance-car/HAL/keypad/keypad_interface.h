

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#include "../../SERVIES/std_typs.h"
#include "keypad_config.h"

#define  No_PressedKey   '?'

#define KEYPAD_ROWS			3
#define KEYPAD_COLUMNS		3

/****************************************************************/
/** FUNCTION TO INITIALIZE KEY PAD */
/** ARGUMENTS : void */
/** RETURN : void */
/****************************************************************/
KEYPAD_initError KEYPAD_init(void) ;


/****************************************************************/
/** FUNCTION TO GET THE PRESSED KEY KEY PAD */
/** ARGUMENTS : void */
/** RETURN : u8 */
/****************************************************************/
KEYPAD_readError KEYPAD_getpressedkey(u8 *value) ;

 
#endif /* KEYPAD_INTERFACE_H_ */