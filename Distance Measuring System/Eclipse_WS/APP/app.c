 /******************************************************************************
 *
 * File Name: app.c
 *
 * Description: The source file for the application.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

#include "../HAL/ultrasonic.h"
#include "../LIB/avr_registers_types.h"
#include "../HAL/lcd.h"

int main(void)
{
	uint16 distance = 0; /* Declaring a unsigned short variable to store distance */

	SREG.bits.I_BIT = 1; /* Enabling Interrupts */


	LCD_init(); /* Initializing the LCD */
	Ultrasonic_init(); /* Initializing the ULTRASONIC sensor */

	LCD_displayString("Distance = ");  /* Displaying the initial messsage on LCD */

	while(1)  /* Main Loop */
	{
		distance = Ultrasonic_readDistance(); /* Reading the distance from the ULTRASONIC into the distance variable */

		if(distance > 100)
		{
			LCD_moveCursor(0,11);
			LCD_integerToString(distance);
		}
		else
		{
			LCD_moveCursor(0,11);
			LCD_integerToString(distance);
			LCD_displayString(" ");
		}
		LCD_displayStringRowColumn(0,14,"cm");   /* Displaying "cm" on LCD after the value */
	}
}

