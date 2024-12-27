#ifndef GUVA_H
#define GUVA_H

#include <CommonFunctions.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#define GUVA_PIN 32
#define GUVA_NO_OF_SAMPLES 1000
#define GUVA_MEASURED_MIN_VOLTAGE 142
#define GUVA_TARGET_MIN_VOLTAGE 0
#define GUVA_MEASURED_MAX_VOLTAGE 3129
#define GUVA_TARGET_MAX_VOLTAGE 1079

// voltage levels in mV, 
const uint16_t UV_VOLTAGE_UPPER_THRESHOLDS[] = { 50, 27, 318, 408, 503, 606, 696, 795, 881, 976 };

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Converts the sensor's output voltage to 0-10 UV index range.
uint8_t convertVoltageToUVIndex(uint16_t& guvaVoltage);

  ///////////////////////////////////////////////////////////////
  /// Get the UV index based on the GUVA sensor's data.
void determineUVIndex(uint8_t& uvIndex);


#endif // GUVA_H