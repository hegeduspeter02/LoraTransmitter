#include <RFM95_sender.h>

/****************************************************************/
void sendPacket(WeatherData& weatherData)
{
  // set radio to idle mode, set up packet, use explicit header mode
  LoRa.beginPacket();

  // write data to the packet
  LoRa.print(weatherData.temperature + ";" + weatherData.humidity);     

  // finish packet and wait for transmission to complete
  LoRa.endPacket();

  Serial.println("Packet was sent.");
  delay(100); // Small delay to prevent buffer overflow
}
