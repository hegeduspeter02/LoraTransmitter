#ifndef main_H
#define main_H

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

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#define SERIAL_BAUD 9600 // bps

#define RFM95_CS0_PIN 5
#define RFM95_DIO0_PIN 17
#define RFM95_RESET_PIN 16
#define SPI_MOSI_PIN 23
#define SPI_MISO_PIN 19
#define SPI_SCLK_PIN 18
#define SPI_CS0_PIN 5
#define uS_TO_S_FACTOR 1000000 // us
#define RFM95_SEND_RATE 5 // s

/* Transmitter's RF power amplifiers' predifined operation modes, set by the setTxPower function.
- For the high and default power setting, the PA_OUTPUT_PA_BOOST_PIN should be used (between +2 and +20 dBm).
- For the medium and low power setting, the PA_OUTPUT_RFO_PIN should be used (between 0 and +14 dBm), for lower current consumption.
*/
#define TX_HIGH_POWER_OPERATION 20 // dBm
#define TX_DEFAULT_POWER_OPERATION 17 // dBm
#define TX_MEDIUM_POWER_OPERATION 13 // dBm
#define TX_LOW_POWER_OPERATION 7 // dBm

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
  /// Set the configurable parameters of the RFM95 module.
void configureLoraTransmitter();

  ///////////////////////////////////////////////////////////////
  /// Set the resulution of the ADC and attenuation for a given pin.
void initializeADC(
  uint8_t resolution,
  uint8_t pin,
  adc_attenuation_t attenuation);

  ///////////////////////////////////////////////////////////////
  /// Create a JSON string from the weatherData struct.
String serializeWeatherData(const WeatherData& weatherData);

  ///////////////////////////////////////////////////////////////
  /// Initialize a packet, put the data in it, then send it.
void sendMessage(const String& string);

  ///////////////////////////////////////////////////////////////
  /// Prints the weatherData to the Serial Monitor.
void printMeasureToSerialMonitor(WeatherData& weatherData);

#endif // main_H