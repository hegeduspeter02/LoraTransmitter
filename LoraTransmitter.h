#ifndef main_H
#define main_H

#include "driver/gpio.h"
#include <stdint.h>
#include <math.h>
#include <Ticker.h>
#include <Wire.h>
#include <Arduino.h>
#include <LoRa.h>
#include <esp_sleep.h>
#include <BME_280.h>
#include <GUVA.h>
#include <SOILCAP.h>
#include <SA_28.h>
#include <ArduinoJson.h>
#include <CayenneLPP.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#ifndef DEBUG_MODE
#define DEBUG_MODE 1
#endif

#define SERIAL_BAUD 9600 // bps

#define RFM95_RESET_PIN 25
#define RFM95_DIO0_PIN 26

#define SPI_CS0_PIN 5
#define SPI_SCLK_PIN 18
#define SPI_MISO_PIN 19
#define SPI_MOSI_PIN 23

#define uS_TO_S_FACTOR 1000000 // us
#define RFM95_SEND_RATE 5 // s

#define MAX_PAYLOAD_SIZE 51 // bytes
#define BME_280_SENSOR_IDENTIFIER 1
#define UV_SENSOR_IDENTIFIER 2
#define SOIL_MOISTURE_SENSOR_IDENTIFIER 3
#define RAIN_SENSOR_IDENTIFIER 4

/*****************************************************************/
/* PREDIFINED CONSTS FOR OPTIMIZING POWER CONSUMPTION- START     */
/*****************************************************************/
// For the high and default power setting, the PA_OUTPUT_PA_BOOST_PIN should be used (between +2 and +20 dBm).
// For the low power setting, the PA_OUTPUT_RFO_PIN should be used (between 0 and +14 dBm), for lower current consumption.
#define HIGH_POWER_RF_AMPLIFIER 20 // dBm
#define MEDIUM_POWER_RF_AMPLIFIER 17 // dBm
#define LOW_POWER_RF_AMPLIFIER 7 // dBm

#define HIGH_POWER_SPREADING_FACTOR 12
#define MEDIUM_POWER_SPREADING_FACTOR 10
#define LOW_POWER_SPREADING_FACTOR 7

#define HIGH_POWER_SIGNAL_BANDWIDTH 7.8E3
#define MEDIUM_POWER_SIGNAL_BANDWIDTH 125E3

#define HIGH_POWER_CODING_RATE_DENOMINATOR 8 // 4/8
#define MEDIUM_POWER_CODING_RATE_DENOMINATOR 5 // 4/5
/*****************************************************************/
/* PREDIFINED CONSTS FOR OPTIMIZING POWER CONSUMPTION- END       */
/*****************************************************************/

/*****************************************************************/
/* STRUCTURES                                                    */
/*****************************************************************/
struct WeatherData {
  float temperature;
  float humidity;
  float pressure;
  uint8_t uvIndex;
  uint8_t soilMoisture;
  uint8_t rainPercent;
};

/*****************************************************************/
/* INIT FUNCTIONS                                                */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Start the Serial communication at SERIAL_BAUD rate.
  /// Wait for the serial port and the Monitor to be ready.
void initializeSerialCommunication();

  ///////////////////////////////////////////////////////////////
  /// Configure the ESP32's pins.
void configureGPIO();

  ///////////////////////////////////////////////////////////////
  /// Set the configurable parameters of the RFM95 module.
void configureLoraTransmitter();

  ///////////////////////////////////////////////////////////////
  /// Set the resulution of the ADC and attenuation for a given pin.
void initializeADC(
  uint8_t resolution,
  uint8_t pin,
  adc_attenuation_t attenuation);

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

CayenneLPP convertWeatherDataToLowPowerPayload(const WeatherData& weatherData);

String convertLowPowerPayloadToHexadecimalString(CayenneLPP& lpp);

  ///////////////////////////////////////////////////////////////
  /// Call convertWeatherDataToLowPowerPayload, then convertLowPowerPayloadToHexadecimalString.
String encodeWeatherData(const WeatherData& weatherData);

  ///////////////////////////////////////////////////////////////
  /// Initialize a packet, put the data in it, then send it.
void sendMessage(const String& payload);

  ///////////////////////////////////////////////////////////////
  /// Prints the weatherData to the Serial Monitor.
void printWeatherDataToSerialMonitor(WeatherData& weatherData);

#endif // main_H