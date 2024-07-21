#include "./LIB/common_macros.h"
#include "./LIB/std_types.h"
#include "./HAL/lcd.h"
#include "./HAL/lm35.h"
#include "./HAL/motor.h"


int main(void)
{
    /* Initialize variables for temperature, fan speed, and motor state */
    uint8 temperature = 0, speed = 0, motor_state = STOP;

    /* Configuration for ADC (Analog-to-Digital Converter) */
    ADC_ConfigType ADC_Config = {INTERNAL, F_CPU_8};

    /* Initialize LCD display, ADC module, and DC motor control */
    LCD_init();
    ADC_init(&ADC_Config);
    DCMOTOR_Init();

    /* Display initial status messages on the LCD */
    LCD_displayStringRowColumn(0, 4, "FAN is ");
    LCD_displayStringRowColumn(1, 3, "Temp = ");

    /* Main loop to continuously monitor temperature and control fan */
    while (1)
    {
        /* Read temperature from LM35 temperature sensor */
        temperature = LM35_getTemperature();

        /* Display current temperature on LCD */
        LCD_moveCursor(1, 10);
        LCD_intgerToString(temperature);

        /* Clear any extra characters if temperature is less than 100 */
        if (temperature < 100)
        {
            LCD_displayString(" ");
        }

        /* Display Celsius symbol next to the temperature */
        LCD_displayStringRowColumn(1, 14, "C");

        /* Adjust fan speed and motor state based on temperature thresholds */
        if (temperature >= 120)
        {
            speed = 100;
            motor_state = CW;
            LCD_displayStringRowColumn(0, 10, " ON "); // Display "ON" status on LCD
        }
        else if (temperature >= 90)
        {
            speed = 75;
            motor_state = CW;
            LCD_displayStringRowColumn(0, 10, " ON "); // Display "ON" status on LCD
        }
        else if (temperature >= 60)
        {
            speed = 50;
            motor_state = CW;
            LCD_displayStringRowColumn(0, 10, " ON "); // Display "ON" status on LCD
        }
        else if (temperature >= 30)
        {
            speed = 25;
            motor_state = CW;
            LCD_displayStringRowColumn(0, 10, " ON "); // Display "ON" status on LCD
        }
        else if (temperature < 30)
        {
            speed = 0;
            motor_state = STOP;
            LCD_displayStringRowColumn(0, 10, " OFF"); // Display "OFF" status on LCD
        }

        /* Control DC motor rotation based on calculated speed and state */
        DCMOTOR_Rotate(motor_state, speed);
    }
}
