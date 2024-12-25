#ifndef SOILCAP_H
#define SOILCAP_H

#include <LoraTransmitter.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#define SOILCAP_PIN 36
#define SOILCAP_NO_OF_SAMPLES 1000
#define SOILCAP_MEASURED_MIN_VOLTAGE 1163
#define SOILCAP_MEASURED_MAX_VOLTAGE 2643

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Get the soil moisture percent based on the SOILCAP's
  /// output voltage.
void determineSoilMoisture(uint16_t& soilMoisture);

#endif // SOILCAP_H