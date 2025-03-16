#ifndef BAT_LEVEL_H
#define BAT_LEVEL_H

#include <Arduino.h>
#include <Battery.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#define BAT_LEVEL_MEAS_EN_PIN 17
#define BAT_LEVEL_MEAS_PIN 33
#define BAT_MIN_VOLTAGE_MV 3000
#define BAT_MAX_VOLTAGE_MV 4200
#define ADC_RESOLUTION 12
#define ADC_VREF_MV 1100
#define VOLTAGE_DIVIDER_RATIO 1.3

/*****************************************************************/
/* INIT FUNCTIONS                                                */
/*****************************************************************/

///////////////////////////////////////////////////////////////
/// Initialize the external Battery Sense library.
void initializeBatLevelMeasureCircuit();

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

///////////////////////////////////////////////////////////////
/// Measure one of the battery's voltage.
uint16_t determineBatVoltage(uint8_t msDelay = 2);

///////////////////////////////////////////////////////////////
/// Use the Battery Sense library to get the battery level
/// from its voltage.
void determineBatLevel(uint8_t &batLevel);

#endif // BAT_LEVEL_H