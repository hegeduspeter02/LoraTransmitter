/*
  Connecting the BME280 Sensor:
  Sensor              ->  Board
  -----------------------------
  Vin (Voltage In)    ->  3.3V
  Gnd (Ground)        ->  Gnd
  SDA (Serial Data)   ->  D21 (defined in variants\doitESP32devkitV1\pins_arduino.h)
  SCK (Serial Clock)  ->  D22 (defined in variants\doitESP32devkitV1\pins_arduino.h)
*/

#ifndef BME_280_H
#define BME_280_H

#include <BME280I2C.h> // predifined library's header file
#include <LoraTransmitter.h>

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
void InitializeBME280();

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Set the BME280's temperature unit, options:
  /// - BME280::TempUnit_Celsius,
  /// - BME280::TempUnit_Fahrenheit
  /// Set the BME280's pressure unit, options:
  /// - BME280::PresUnit_Pa
  /// - BME280::PresUnit_hPa
  /// - BME280::PresUnit_inHg
  /// - BME280::PresUnit_atm
  /// - BME280::PresUnit_bar
  /// - BME280::PresUnit_mbar
  /// - BME280::PresUnit_torr
  /// - BME280::PresUnit_psi
  /// Read the BME280's output and store it in weatherData

  /// Pressure levels in hPa approx. in Hungary
  /// - Normal: ~1013 hPa
  /// - High: above 1016 hPa
  /// - Low: below 1010 hPa
void ReadBME280Data(BME280::TempUnit tempUnit,
                    BME280::PresUnit presUnit,
                    WeatherData& weatherData);

#endif // BME_280_H