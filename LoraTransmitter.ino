#include <LoraTransmitter.h>

WeatherData weatherData;

void setup()
{
  initializeSerialCommunication();

  Wire.begin(); // set the SDA and SCK pins on the ESP

  SPIClass spi;
  spi.begin(SPI_SCLK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS0_PIN); // set SPI pins

  configureGPIO();

  configureLoraTransmitter();

  initializeBME280();
  initializeADC(12, GUVA_PIN, ADC_11db); // set the attenuation to 11 dB
                                         // able to measure between 100 mV ~ 3100 mV
  initializeADC(12, SOILCAP_PIN, ADC_11db);

  // initialize LoRa library with 868 MHz communication frequency
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop()
{
  readBME280Data(weatherData.temperature, weatherData.humidity, weatherData.pressure);
  determineUVIndex(weatherData.uvIndex);
  determineSoilMoisture(weatherData.soilMoisture);
  determineRainStatus(weatherData.rainPercent);

  #if DEBUG_MODE
    printWeatherDataToSerialMonitor(weatherData);
  #endif

  String payload = encodeWeatherData(weatherData);
  sendMessage(payload);

  // enable sleep wakeup using a dedicated timer at RFM95_SEND_RATE
  esp_sleep_enable_timer_wakeup(RFM95_SEND_RATE * uS_TO_S_FACTOR); 

  LoRa.sleep(); // put the RFM95 in sleep mode
  esp_light_sleep_start();
}
