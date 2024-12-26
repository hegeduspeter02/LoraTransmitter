
#include <LoraTransmitter.h>

/****************************************************************/
void InitializeSerialCommunication()
{
  Serial.begin(SERIAL_BAUD);
  while(!Serial) {} // wait until the serial port is ready and connected
  delay(1000); // wait for Serial Monitor to initialize
}

/****************************************************************/
void InitializeADC(uint8_t resolution, uint8_t pin, adc_attenuation_t attenuation)
{
  analogReadResolution(resolution);
  analogSetPinAttenuation(pin, attenuation);
}

String serializeWeatherData(const WeatherData& weatherData)
{
  JsonDocument doc;
  JsonArray data = doc["data"].to<JsonArray>();
  data.add(weatherData.temperature);
  data.add(round(weatherData.humidity * 100.0f) / 100.0f);
  data.add(round(weatherData.pressure * 100.0f) / 100.0f);
  data.add(weatherData.uvIndex);
  data.add(weatherData.soilMoisture);
  data.add(weatherData.rainPercent);

  String serializedWeatherData;
  serializeJson(doc, serializedWeatherData);

  return serializedWeatherData;
}

/****************************************************************/
void sendMessage(const String& string)
{
  // set radio to idle mode, set up packet, use explicit header mode
  LoRa.beginPacket();

  // write data to the packet
  LoRa.print(string);     

  // finish packet and wait for transmission to complete
  LoRa.endPacket();

  Serial.println("Packet was sent.");
  delay(100); // Small delay to prevent buffer overflow
}

/****************************************************************/
void PrintMeasureToSerialMonitor(WeatherData& weatherData)
{
  Serial.printf("Temp: %.2f\xB0C\n"
                "Humidity: %.2f%% RH\n"
                "Pressure: %.2f hPa\n"
                "UV index: %d\n"
                "Soil moisture: %d%%\n"
                "Rain intensity: %d%%\n"
                "---------------------------------------------------------\n", 
                weatherData.temperature,
                weatherData.humidity,
                weatherData.pressure,
                weatherData.uvIndex,
                weatherData.soilMoisture,
                weatherData.rainPercent);
}
