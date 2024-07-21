#include "lib/std_types.h"
#include "HAL/lcd.h"
#include "HAL/keypad.h"
#include <util/delay.h>

/*
 * Description :
 * Perform the mathematical operation specified by the operator on two operands.
 * The supported operations are addition (+), subtraction (-), multiplication (*), and division (%).
 * Returns the result of the operation.
 */

uint32 doOperation(uint32 firstOperand, uint32 secondOperand, uint8 Operation){
	switch (Operation){
		case '+':
			return (firstOperand + secondOperand);
			break;
		case '-':
			return (firstOperand - secondOperand);
			break;
		case '*':
			return (firstOperand * secondOperand);
		break;
			break;
		case '%':
			return (firstOperand / secondOperand);
			break;
	}
	return 0;

}

int main(void)
{
	uint8 key;               /* Variable to store the pressed key value */
	uint8 operation = 0;     /* Variable to store the operation (+, -, *, /) */
	sint32 result;           /* Variable to store the result of the operation*/

	sint32 first = 0;        /* Variable to store the first operand*/
	sint32 second = 0;       /*Variable to store the second operand*/
	sint32 num = 0;          /* Variable to store the currently entered number*/

	LCD_init();              /* Initialize the LCD*/
	_delay_ms(100);          /* Wait for 100 ms*/


	while(1)
	{
		key = KEYPAD_getPressedKey();
		_delay_ms(200);

		if (key >= 0 && key <= 9){
			LCD_intgerToString(key);

			if (num){
                num *= 10; /* Shift the current number to the left by one decimal place */
                num += key; /* Add the pressed key */
			}
			else {
                num = key; /* Set the current number to the pressed key */
			}

		}

		else if (num && (key == '*' || key == '%' || key == '-' || key == '+')){
			if (first){
                first = doOperation(first, num, operation); /* Perform the operation with the current number and the previous result */
                LCD_clearScreen(); /* Clear the LCD display */
                LCD_intgerToString(first); /* Display the updated result on the LCD */
			}
            else
            {
                first = num; /* Set the first operand to the current number */
            }
            num = 0; /* Reset the current number */
            operation = key; /* Set the operation to the pressed key */
            LCD_displayCharacter(key); /* Display the operation symbol on the LCD */
        }

		else if (key == '='){
			if (first && num){
				second = num;
				num = 0;
				result = doOperation(first, second, operation);

				LCD_clearScreen(); /* Clear the LCD display */

				LCD_intgerToString(result);
				first = 0; /* Reset the first operand */
				second = 0; /* Reset the second operand */
				operation = 0; /* Reset the operation */
				num = result;
			}
		}
        else if(key == 13)
        {
            LCD_clearScreen(); /* Clear the LCD display */
            first = 0; /* Reset the first operand */
            second = 0; /* Reset the second operand */
            operation = 0; /* Reset the operation */
            num = 0; /* Reset the current number */
        }
    }
}
