#ifndef SOILCAP_H
#define SOILCAP_H

#include <CommonFunctions.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#define SOILCAP_PIN 4
#define SOILCAP_NO_OF_SAMPLES 20
#define SOILCAP_MEASURED_MIN_VOLTAGE 1115
#define SOILCAP_MEASURED_MAX_VOLTAGE 2630

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

///////////////////////////////////////////////////////////////
/// Get the soil moisture percent based on the SOILCAP's
/// output voltage.
void determineSoilMoisture(uint8_t &soilMoisture);

#endif // SOILCAP_H