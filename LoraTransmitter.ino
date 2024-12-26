#include <LoraTransmitter.h>

WeatherData weatherData;

void setup()
{
  InitializeSerialCommunication();

  Wire.begin(); // set the SDA and SCK pins on the ESP

  SPIClass spi;
  // set SPI pins
  spi.begin(SPI_SCLK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS0_PIN);

  // set RFM95 pins
  LoRa.setPins(RFM95_CS0_PIN, RFM95_RESET_PIN, RFM95_DIO0_PIN);

  InitializeBME280();
  InitializeADC(12, GUVA_PIN, ADC_11db); // set the attenuation to 11 dB
                                         // able to measure between 100 mV ~ 3100 mV
  InitializeADC(12, SOILCAP_PIN, ADC_11db);

  // initialize LoRa library with 868 MHz communication frequency
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop()
{
  ReadBME280Data(weatherData.temperature, weatherData.humidity, weatherData.pressure);
  determineUVIndex(weatherData.uvIndex);
  determineSoilMoisture(weatherData.soilMoisture);
  determineRainStatus(weatherData.rainPercent);

  #if DEBUG_MODE
    PrintMeasureToSerialMonitor(weatherData);
  #endif

  String serializedWeatherData = serializeWeatherData(weatherData);
  sendMessage(serializedWeatherData);

  // enable sleep wakeup using a dedicated timer at RFM95_SEND_RATE
  esp_sleep_enable_timer_wakeup(RFM95_SEND_RATE * uS_TO_S_FACTOR); 

  LoRa.sleep(); // put the RFM95 in sleep mode
  esp_light_sleep_start();
}
