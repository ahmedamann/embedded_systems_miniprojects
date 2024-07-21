 /******************************************************************************
 *
 * Module: Input Capture Unit (ICU)
 *
 * File Name: icu.h
 *
 * Description: Header file for the ICU Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include "../LIB/std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
    NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
} ICU_ClockType;

typedef enum
{
    FALLING_EDGE, RISING_EDGE
} ICU_EdgeType;

typedef struct
{
    ICU_ClockType clock;
    ICU_EdgeType edge;
} ICU_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Initializes the Input Capture Unit (ICU) with the given configuration.
 *
 * Parameters:
 * - Config_Ptr: Pointer to the configuration structure containing clock and edge settings.
 */
void ICU_init(const ICU_ConfigType *Config_Ptr);

/*
 * Description:
 * Sets the edge detection type for the ICU.
 *
 * Parameters:
 * - a_edge_type: Edge type to set (FALLING_EDGE or RISING_EDGE).
 */
void ICU_setEdgeDetection(const ICU_EdgeType a_edge_type);

/*
 * Description:
 * Retrieves the current timer value captured by the ICU.
 *
 * Returns:
 * - Current timer value.
 */
uint16 ICU_getTimerValue(void);

/*
 * Description:
 * Clears the timer value captured by the ICU.
 */
void ICU_clearTimerValue(void);

/*
 * Description:
 * Sets a callback function to be called when an ICU event occurs.
 *
 * Parameters:
 * - a_ptr: Pointer to the callback function.
 */
void ICU_setCallBack(void(*a_ptr)(void));

/*
 * Description:
 * De-initializes the ICU, resetting it to its default state.
 */
void ICU_deinit(void);

#endif /* ICU_H_ */
