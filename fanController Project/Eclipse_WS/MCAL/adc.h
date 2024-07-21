/*
 *  File: adc.h
 *
 *  Created on: Jun 6, 2024
 *      Author: Ahmed Aman
 */

#ifndef MCAL_ADC_H_
#define MCAL_ADC_H_

#include "../LIB/std_types.h"
#include "../LIB/common_macros.h"
#include "../LIB/avr_registers_types.h"
#include "../MCAL/gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	AREF, AVCC, INTERNAL=3

} ADC_ReferenceVoltage;

typedef enum
{
	F_CPU_1, F_CPU_2, F_CPU_4, F_CPU_8, F_CPU_16, F_CPU_32, F_CPU_64, F_CPU_128
} ADC_Prescaler;

typedef struct
{
	ADC_ReferenceVoltage refVolt;
	ADC_Prescaler prescaler;

} ADC_ConfigType;


/*******************************************************************************
 *                                ADC Macros                                   *
 *******************************************************************************/

/* Select the ADC channel by masking the upper 3 bits and setting the channel bits */
#define ADC_SELECT_CHANNEL(CHANNEL)   (ADMUX.byte = (ADMUX.byte & 0xE0) | (CHANNEL & 0x1F))

/* Set ADC Reference Voltage */
#define ADC_REFVOLT(ref_volt)      	  (ADMUX.byte |= (ref_volt << 6))

/* Enable the ADC by setting ADEN bit of the control register */
#define ADC_ENABLE                    (ADCSRA.bits.ADEN = 1)

/* Enable ADC interrupt by setting bit ADIE in the control register */
#define ADC_INTERRUPT_ENABLE          (ADCSRA.bits.ADIE = 1)

/* Disable ADC interrupt by clearing bit ADIE in the control register */
#define ADC_INTERRUPT_DISABLE         (ADCSRA.bits.ADIE = 0)

/* Start ADC conversion by setting bit ADSC in the control register */
#define ADC_START_CONVERSION          (ADCSRA.bits.ADSC = 1)

/* Set ADC prescaler by configuring ADPS2, ADPS1, and ADPS0 bits in the control register */
#define ADC_PRESCALER(prescaler)      (ADCSRA.byte |= prescaler)

/* ADC CLEAR FLAG */
#define ADC_CLEAR_FLAG                (ADCSRA.bits.ADIF = 1)

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType* Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* MCAL_ADC_H_ */
