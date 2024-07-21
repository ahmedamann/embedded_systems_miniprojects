/*
 * lm35.c
 *
 *  Created on: Jun 6, 2024
 *      Author: Ahmed Aman
 */

#include <util/delay.h> /* For the delay functions */
#include "lm35.h"

/*
 * Description:
 * Calculates the temperature based on the ADC digital value from an LM35 temperature sensor.
 *
 * Returns:
 * - Calculated temperature value in degrees Celsius (uint8).
 */
uint8 LM35_getTemperature(void)
{
    uint8 temp_value = 0;

    /* Read ADC channel where the LM35 temperature sensor is connected */
    uint16 adcResult = ADC_readChannel(SENSOR_CHANNEL_ID);

    /* Delay to ensure ADC result is updated (assuming synchronous ADC read) */
    _delay_ms(5);

    /* Calculate the temperature from the ADC value */
    temp_value = (uint8)(((uint32)adcResult * SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) /
                         (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE));

    return temp_value;
}


