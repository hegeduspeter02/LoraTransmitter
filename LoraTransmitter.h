#ifndef main_H
#define main_H

#include <Ticker.h>
#include <Wire.h>
#include <Arduino.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#define SERIAL_BAUD 9600 // bps
#define SENSORS_READ_RATE 1 // s
#define ZERO_PERCENT 0
#define ONE_HUNDRED_PERCENT 100

#ifndef DEBUG_MODE
#define DEBUG_MODE 1
#endif

/*****************************************************************/
/* STRUCTURES                                                    */
/*****************************************************************/
struct WeatherData {
  float temperature;
  float humidity;
  float pressure;
  uint8_t uvIndex;
  uint16_t soilMoisture;
  uint16_t rainPercent;
};

struct AnalogSensorVoltage {
  uint16_t guvaVoltage;
  uint16_t soilCapVoltage;
  uint16_t sa28Voltage;
};

/*****************************************************************/
/* INIT FUNCTIONS                                                */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Start the Serial communication at SERIAL_BAUD rate.
  /// Wait for the serial port and the Monitor to be ready.
void InitializeSerialCommunication();

  ///////////////////////////////////////////////////////////////
  /// Set the resulution of the ADC and attenuation for a given pin.
void InitializeADC(
  uint8_t resolution,
  uint8_t pin,
  adc_attenuation_t attenuation);

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Measure the voltage of a pin, avarage it with 
  /// number_of_samples and store it in the result param.
uint16_t ReadAnalogSensorVoltage(
  const uint16_t number_of_samples,
  const uint8_t pin);

  ///////////////////////////////////////////////////////////////
  /// Re-map the ReadAnalogSensorData's output to a number
  /// range defined by TO_LOW and TO_HIGH and store it in result param.
uint16_t ReMapOutputVoltageRange(
  uint16_t& sensorOutput,
  const uint16_t fromLowVoltage,
  const uint16_t fromHighVoltage,
  const uint16_t toLow,
  const uint16_t toHigh);

  ///////////////////////////////////////////////////////////////
  /// Prints the weatherData to the Serial Monitor.
void PrintResultsToSerialMonitor(WeatherData& weatherData);

#endif // main_H