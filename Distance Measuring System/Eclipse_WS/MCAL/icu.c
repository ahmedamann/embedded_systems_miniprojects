 /******************************************************************************
 *
 * Module: Input Capture Unit (ICU)
 *
 * File Name: icu.c
 *
 * Description: Source file for the ICU Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/


#include "icu.h"
#include "../LIB/common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*
 * ISR (TIMER1_CAPT_vect)
 * Description:
 * Interrupt service routine for TIMER1 capture event.
 * Calls the callback function if it is not NULL.
 */
ISR (TIMER1_CAPT_vect)
{
    if(g_callBackPtr != NULL_PTR)
    {
        (*g_callBackPtr)();
    }
}

/*
 * ICU_init
 * Description:
 * Initializes the Input Capture Unit (ICU) with the given configuration.
 *
 * Parameters:
 * - Config_Ptr: Pointer to the configuration structure containing clock and edge settings.
 */
void ICU_init(const ICU_ConfigType *Config_Ptr)
{
    CLEAR_BIT(DDRD, PD6);
    TCNT1 = 0;
    ICR1 = 0;
    TCCR1A = (1 << FOC1A) | (1 << FOC1B);
    TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);
    TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge) << ICES1);
    SET_BIT(TIMSK, TICIE1);
}

/*
 * ICU_setEdgeDetection
 * Description:
 * Sets the edge detection type for the ICU.
 *
 * Parameters:
 * - a_edge_type: Edge type to set (FALLING_EDGE or RISING_EDGE).
 */
void ICU_setEdgeDetection(const ICU_EdgeType a_edge_type)
{
    TCCR1B = (TCCR1B & 0xBF) | (a_edge_type << ICES1);
}

/*
 * ICU_getTimerValue
 * Description:
 * Retrieves the current timer value captured by the ICU.
 *
 * Returns:
 * - Current timer value.
 */
uint16 ICU_getTimerValue(void)
{
    return ICR1;
}

/*
 * ICU_clearTimerValue
 * Description:
 * Clears the timer value captured by the ICU.
 */
void ICU_clearTimerValue(void)
{
    TCNT1 = 0;
}

/*
 * ICU_setCallBack
 * Description:
 * Sets a callback function to be called when an ICU event occurs.
 *
 * Parameters:
 * - a_ptr: Pointer to the callback function.
 */
void ICU_setCallBack(void(*a_ptr)(void))
{
    g_callBackPtr = a_ptr;
}

/*
 * ICU_deinit
 * Description:
 * De-initializes the ICU, resetting it to its default state.
 */
void ICU_deinit(void)
{
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    ICR1 = 0;
    CLEAR_BIT(TIMSK, TICIE1);
    g_callBackPtr = NULL_PTR;
}
