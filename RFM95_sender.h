#ifndef RFM95_sender_H
#define RFM95_sender_H

#include <LoRa.h>
#include <esp_sleep.h>
#include <LoraTransmitter.h>

/*****************************************************************/
/* GLOBAL CONSTS                                                 */
/*****************************************************************/
#define RFM95_CS0_PIN 5
#define RFM95_DIO0_PIN 17
#define RFM95_RESET_PIN 16
#define SPI_MOSI_PIN 23
#define SPI_MISO_PIN 19
#define SPI_SCLK_PIN 18
#define SPI_CS0_PIN 5
#define uS_TO_S_FACTOR 1000000 // us
#define RFM95_SEND_RATE 5 // s

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Initialize a packet, put the data in it, then send it.
void sendMessage(const WeatherData& weatherData);

#endif // RFM95_sender_H
