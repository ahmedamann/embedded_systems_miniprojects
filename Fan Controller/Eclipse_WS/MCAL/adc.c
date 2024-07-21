/*
 *  File: adc.c
 *
 *  Created on: Jun 15, 2024
 *  Author: Ahmed Aman
 */

#include "adc.h"

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*
 * Initializes the ADC module based on the provided configuration.
 *
 * Config_Ptr: Pointer to a structure containing ADC configuration parameters.
 *             - refVolt: Reference voltage selection.
 *             - prescaler: ADC clock prescaler.
 * Returns: None
 */
void ADC_init(const ADC_ConfigType* Config_Ptr)
{
    /* Initialize the ADC control register to 0 */
    ADCSRA.byte = 0;

    /* Enable the ADC */
    ADC_ENABLE;

    /* Set ADC reference voltage */
    ADC_REFVOLT(Config_Ptr->refVolt);

    /* Set ADC prescaler */
    ADC_PRESCALER(Config_Ptr->prescaler);
}

/*
 * Reads the ADC value from the specified channel synchronously.
 *
 * channel_num: ADC channel number (0 to 7).
 * Returns: 16-bit ADC conversion result from the specified channel.
 */
uint16 ADC_readChannel(uint8 channel_num)
{
    /* Ensure channel number is within valid range */
    channel_num &= 0x07;

    /* Select ADC channel */
    ADC_SELECT_CHANNEL(channel_num);

    /* Start ADC conversion */
    ADC_START_CONVERSION;

    /* Wait until ADC conversion completes (polling) */
    while(ADCSRA.bits.ADIF == 0);

    /* Clear ADC conversion complete flag */
    ADC_CLEAR_FLAG;

    /* Return ADC conversion result */
    return ADC.twoBytes;
}

