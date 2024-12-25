#ifndef RFM95_sender_H
#define RFM95_sender_H

#include <LoRa.h>
#include <esp_sleep.h>

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
#define RFM95_SEND_RATE 5000000 // us

/*****************************************************************/
/* WORKER FUNCTIONS                                              */
/*****************************************************************/

  ///////////////////////////////////////////////////////////////
  /// Initialize a packet, put the data in it, then send it.
void sendPacket(const WeatherData& weatherData);

String weatherDataToString(const WeatherData& data)
{
    return to_string(data.temperature) + ";" + 
           to_string(data.humidity) + ";" + 
           to_string(data.pressure) + ";" + 
           to_string(data.uvIndex) + ";" + 
           to_string(data.soilMoisture) + ";" + 
           to_string(data.rainPercent);
}

#endif // RFM95_sender_H
