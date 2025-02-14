#ifndef SA_28_H
#define SA_28_H

#include <CommonFunctions.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#define SA_28_PIN 33
#define SA_28_NO_OF_SAMPLES 1000
#define SA_28_MEASURED_MIN_VOLTAGE 998
#define SA_28_MEASURED_MAX_VOLTAGE 3129

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Get the soil moisture percent based on the SA_28's
  /// output voltage.
void determineRainStatus(uint8_t& rainPercent);

#endif // SA_28_H