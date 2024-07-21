 /******************************************************************************
 *
 * Module: ULTRASONIC Sensor
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the ULTRASONIC Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

#ifndef HAL_ULTRASONIC_H_
#define HAL_ULTRASONIC_H_

#include "../LIB/std_types.h"

#define TRIGGER_PORT_ID          PORTB_ID
#define TRIGGER_PIN_ID           PIN5_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Ultrasonic_init
 * Description:
 * Initializes the ultrasonic sensor module.
 */
void Ultrasonic_init(void);

/*
 * Ultrasonic_readDistance
 * Description:
 * Reads the distance from the ultrasonic sensor.
 *
 * Returns:
 * - Distance in centimeters.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Ultrasonic_edgeProcessing
 * Description:
 * Handles edge interrupts from the ultrasonic sensor for timing measurements.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* HAL_ULTRASONIC_H_ */
