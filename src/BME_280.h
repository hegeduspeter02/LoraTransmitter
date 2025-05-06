#ifndef BME_280_H
#define BME_280_H

#include "src/CommonFunctions.h"
#include <BME280I2C.h> // library's header file

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
const BME280::TempUnit TEMP_UNIT = BME280::TempUnit_Celsius;
const BME280::PresUnit PRES_UNIT = BME280::PresUnit_hPa;

/*****************************************************************/
/* GLOBAL VARIABLES                                              */
/*****************************************************************/
extern BME280I2C::Settings bmeSettings;
extern BME280I2C bme;

/*****************************************************************/
/* INIT FUNCTIONS                                                */
/*****************************************************************/

///////////////////////////////////////////////////////////////
/// Wait for initializing BME280's settings
void initializeBME280();

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

/// Read the BME280's output and store it in measureData
/// Pressure levels in hPa approx. in Hungary
/// - Normal: ~1013 hPa
/// - High: above 1016 hPa
/// - Low: below 1010 hPa
void readBME280Data(
    float &temperature,
    float &humidity,
    float &pressure);

#endif // BME_280_H