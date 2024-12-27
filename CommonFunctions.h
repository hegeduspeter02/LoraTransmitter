#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include <Arduino.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#define ZERO_PERCENT 0
#define ONE_HUNDRED_PERCENT 100

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Measure the voltage of a pin, avarage it with 
  /// number_of_samples and store it in the result param.
uint16_t readAnalogSensorVoltage(
  const uint16_t number_of_samples,
  const uint8_t pin);

  ///////////////////////////////////////////////////////////////
  /// Re-map the ReadAnalogSensorData's output to a number
  /// range defined by TO_LOW and TO_HIGH and store it in result param.
uint16_t reMapOutputVoltageRange(
  uint16_t& sensorOutput,
  const uint16_t fromLowVoltage,
  const uint16_t fromHighVoltage,
  const uint16_t toLow,
  const uint16_t toHigh);


#endif // COMMONFUNCTIONS_H