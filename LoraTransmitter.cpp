#include <LoraTransmitter.h>

void initializeSerialCommunication()
{
  Serial.begin(SERIAL_BAUD);
  while (!Serial){} // wait until the serial port is ready and connected
}

void configureGPIO()
{
  pinMode(RFM95_RESET_PIN, OUTPUT);
  pinMode(RFM95_DIO0_PIN, INPUT);

  pinMode(GUVA_PIN, INPUT);
  pinMode(SOILCAP_PIN, INPUT);
  pinMode(SA_28_PIN, INPUT);
}

void configureLoraTransmitter()
{
  LoRa.setPins(SPI_CS0_PIN, RFM95_RESET_PIN, RFM95_DIO0_PIN);
  LoRa.setTxPower(MEDIUM_POWER_RF_AMPLIFIER, PA_OUTPUT_PA_BOOST_PIN);
}

CayenneLPP convertWeatherDataToLowPowerPayload(const WeatherData &weatherData)
{
  CayenneLPP lpp(PAYLOAD_SIZE);
  lpp.reset();

  lpp.addTemperature(BME_280_SENSOR_IDENTIFIER, weatherData.temperature);
  lpp.addRelativeHumidity(BME_280_SENSOR_IDENTIFIER, weatherData.humidity);
  lpp.addBarometricPressure(BME_280_SENSOR_IDENTIFIER, weatherData.pressure);
  lpp.addDigitalOutput(UV_SENSOR_IDENTIFIER, weatherData.uvIndex);
  lpp.addDigitalOutput(SOIL_MOISTURE_SENSOR_IDENTIFIER, weatherData.soilMoisture);
  lpp.addDigitalOutput(RAIN_SENSOR_IDENTIFIER, weatherData.rainPercent);

  return lpp;
}

String convertLowPowerPayloadToHexadecimalString(CayenneLPP &lpp)
{
  String lppString;

  for (int i = 0; i < lpp.getSize(); i++)
  {
    char buffer[3];
    sprintf(buffer, "%02X", lpp.getBuffer()[i]); // convert each byte to hex
    lppString += buffer;
  }

  return lppString;
}

String encodeWeatherData(const WeatherData &weatherData)
{
  CayenneLPP lpp = convertWeatherDataToLowPowerPayload(weatherData);
  String lppString = convertLowPowerPayloadToHexadecimalString(lpp);

  return lppString;
}

void sendMessage(const String &payload)
{
  // set radio to idle mode, set up packet, use explicit header mode
  uint8_t readyToTransmit = LoRa.beginPacket();

  if (readyToTransmit)
  {
    LoRa.print(payload); // write data to the packet
    LoRa.endPacket();    // finish packet and wait for transmission to complete
  }
}

void printWeatherDataToSerialMonitor(WeatherData &weatherData)
{
  Serial.printf("Temp: %.2f °C\n"
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
  delay(100); // delay to prevent buffer overflow
}

void endLibraries()
{
  LoRa.end(); // put the RFM95 in sleep mode & disable spi bus
  Wire.end();
}
