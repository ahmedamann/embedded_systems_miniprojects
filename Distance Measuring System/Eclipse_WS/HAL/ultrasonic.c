 /******************************************************************************
 *
 * Module: ULTRASONIC Sensor
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the ULTRASONIC Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/


#include "ultrasonic.h"
#include "../MCAL/icu.h"
#include "../MCAL/gpio.h"
#include <util/delay.h>

static volatile uint8 g_edgeCount = 0;
static uint16 timerValue = 0;

static void Ultrasonic_Trigger(void);

/*
 * Ultrasonic_init
 * Description:
 * Initializes the ultrasonic sensor module.
 * Configures ICU for distance measurement and sets up GPIO for trigger pin.
 */
void Ultrasonic_init(void)
{
    ICU_ConfigType ICU_Configurations = {F_CPU_8, RISING_EDGE};
    ICU_init(&ICU_Configurations);
    ICU_setCallBack(Ultrasonic_edgeProcessing);
    GPIO_setupPinDirection(TRIGGER_PORT_ID, TRIGGER_PIN_ID, PIN_OUTPUT);
}

/*
 * Ultrasonic_Trigger
 * Description:
 * Sends a trigger pulse to the ultrasonic sensor.
 */
static void Ultrasonic_Trigger(void)
{
    GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_HIGH);
    _delay_us(10);
    GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);
}

/*
 * Ultrasonic_readDistance
 * Description:
 * Reads the distance from the ultrasonic sensor.
 *
 * Returns:
 * - Distance in centimeters.
 */
uint16 Ultrasonic_readDistance(void)
{
    uint16 distance = 0;
    Ultrasonic_Trigger();
    while (g_edgeCount != 2);
    g_edgeCount = 0;
    distance = 1 + (timerValue / 58);
    return distance;
}

/*
 * Ultrasonic_edgeProcessing
 * Description:
 * Handles edge interrupts from the ICU for ultrasonic sensor timing.
 */
void Ultrasonic_edgeProcessing(void)
{
    g_edgeCount++;
    if (g_edgeCount == 1)
    {
        ICU_clearTimerValue();
        ICU_setEdgeDetection(FALLING_EDGE);
    }
    else if (g_edgeCount == 2)
    {
        timerValue = ICU_getTimerValue();
        ICU_setEdgeDetection(RISING_EDGE);
        ICU_clearTimerValue();
    }
}
