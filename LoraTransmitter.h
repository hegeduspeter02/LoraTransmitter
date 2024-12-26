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

  ///////////////////////////////////////////////////////////////
  /// Initialize a packet, put the data in it, then send it.
String serializeWeatherData(const WeatherData& weatherData);

  ///////////////////////////////////////////////////////////////
  /// Initialize a packet, put the data in it, then send it.
void sendMessage(const String& string);

  ///////////////////////////////////////////////////////////////
  /// Prints the weatherData to the Serial Monitor.
void PrintMeasureToSerialMonitor(WeatherData& weatherData);

#endif // main_H