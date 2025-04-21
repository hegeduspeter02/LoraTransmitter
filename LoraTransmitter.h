#ifndef main_H
#define main_H

#include <Arduino.h>
#include <Wire.h>
#include <LoRa.h>
#include <BME_280.h>
#include <GUVA.h>
#include <SOILCAP.h>
#include <SA_28.h>
#include <BatLevel.h>
#include <CayenneLPP.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#ifndef DEBUG_MODE
#define DEBUG_MODE 1
#endif

#define SERIAL_BAUD 115200 // bps
#define RFM95_COMM_FREQ 868E6
#define uS_TO_S_FACTOR 1000000 // us
#define RFM95_SEND_RATE 10     // s
#define NO_OF_MEASURED_DATA 7
#define LPP_DATA_ID_SIZE 1      // byte
#define LPP_DATA_CHANNEL_SIZE 1 // byte
#define LPP_DATA_SIZE (LPP_TEMPERATURE_SIZE +         \
                       LPP_RELATIVE_HUMIDITY_SIZE +   \
                       LPP_BAROMETRIC_PRESSURE_SIZE + \
                       LPP_DIGITAL_INPUT_SIZE +       \
                       (LPP_PERCENTAGE_SIZE * 3)) // bytes
#define PAYLOAD_SIZE ((LPP_DATA_ID_SIZE * NO_OF_MEASURED_DATA) +      \
                      (LPP_DATA_CHANNEL_SIZE * NO_OF_MEASURED_DATA) + \
                      LPP_DATA_SIZE) // bytes

// pins
#define RFM95_RESET_PIN 25
#define RFM95_DIO0_PIN 26
#define SPI_CS0_PIN 5
#define SPI_SCLK_PIN 18
#define SPI_MISO_PIN 19
#define SPI_MOSI_PIN 23
#define HIGH_PWR_MODE_PIN 12
#define LOW_PWR_MODE_PIN 14

// ids for packet decoding
#define BME_280_TEMPERATURE_SENSOR_ID 0
#define BME_280_HUMIDITY_SENSOR_ID 1
#define BME_280_PRESSURE_SENSOR_ID 2
#define UV_SENSOR_ID 3
#define SOIL_MOISTURE_SENSOR_ID 4
#define RAIN_SENSOR_ID 5
#define BAT_LEVEL_ID 6

/*****************************************************************/
/* PREDIFINED CONSTS FOR OPTIMIZING POWER CONSUMPTION- START     */
/*****************************************************************/
/*
  For the high and medium power rf amplifier setting,
  the PA_OUTPUT_PA_BOOST_PIN needs to be used (between +2 and +20 dBm).

  For the low power rf amplifier setting, the PA_OUTPUT_RFO_PIN
  should be used (between 0 and +14 dBm), for lower current consumption.
*/
#define HIGH_POWER_RF_AMPLIFIER 20   // dBm
#define MEDIUM_POWER_RF_AMPLIFIER 17 // dBm
#define LOW_POWER_RF_AMPLIFIER 7     // dBm

#define HIGH_POWER_SPREADING_FACTOR 12
#define MEDIUM_POWER_SPREADING_FACTOR 10
#define LOW_POWER_SPREADING_FACTOR 7

#define HIGH_AND_MEDIUM_POWER_SIGNAL_BANDWIDTH 125E3
#define LOW_POWER_SIGNAL_BANDWIDTH 250E3

#define HIGH_POWER_CODING_RATE_DENOMINATOR 8           // 4/8
#define MEDIUM_AND_LOW_POWER_CODING_RATE_DENOMINATOR 5 // 4/5
/*****************************************************************/
/* PREDIFINED CONSTS FOR OPTIMIZING POWER CONSUMPTION- END       */
/*****************************************************************/

/*****************************************************************/
/* STRUCTURES                                                    */
/*****************************************************************/
struct MeasureData
{
  float temperature;
  float humidity;
  float pressure;
  uint8_t uvIndex;
  uint8_t soilMoisture;
  uint8_t rainPercent;
  uint8_t batLevel;
};

/*****************************************************************/
/* ENUMS                                                         */
/*****************************************************************/
enum PowerMode
{
  LOW_POWER_MODE,
  MEDIUM_POWER_MODE,
  HIGH_POWER_MODE
};

/*****************************************************************/
/* INIT FUNCTIONS                                                */
/*****************************************************************/

///////////////////////////////////////////////////////////////
/// Start the Serial communication at SERIAL_BAUD rate.
/// Wait for the serial port and the Monitor to be ready.
void initializeSerialCommunication();

///////////////////////////////////////////////////////////////
/// Configure the ESP32's IO pins.
void configureGPIO();

///////////////////////////////////////////////////////////////
/// Determine LOW/MEDIUM/HIGH power mode based on the switch's state.
PowerMode determinePowerMode();

///////////////////////////////////////////////////////////////
/// Convert the power mode to a string for debugging purposes.
String powerModeToString(); 

///////////////////////////////////////////////////////////////
/// Configure the radio's params based on the power mode.
void setLoRaPowerMode();

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

///////////////////////////////////////////////////////////////
/// Create a Cayenne Low Power Payload, containing the measured data.
CayenneLPP convertMeasureDataToLowPowerPayload(const MeasureData &measureData);

///////////////////////////////////////////////////////////////
/// Initialize a packet, put the data in it, then send it.
void sendMessage(CayenneLPP &lpp);

///////////////////////////////////////////////////////////////
/// Prints the measureData to the Serial Monitor.
void printMeasureDataToSerialMonitor(MeasureData &measureData);

///////////////////////////////////////////////////////////////
/// Stop the used libraries.
void endLibraries();

#endif // main_H