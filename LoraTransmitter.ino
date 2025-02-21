#include <LoraTransmitter.h>
#include <esp_sleep.h>

WeatherData weatherData;

void setup()
{
  initializeSerialCommunication();
  
  setCpuFrequencyMhz(80); // MHz

  Wire.begin(); // set the SDA and SCK pins on the ESP

  configureGPIO();

  SPI.begin(SPI_SCLK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS0_PIN); // set SPI pins
  LoRa.setSPI(SPI);

  configureLoraTransmitter();

  initializeBME280();

  if (!LoRa.begin(RFM95_COMM_FREQ)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  esp_sleep_enable_timer_wakeup(RFM95_SEND_RATE * uS_TO_S_FACTOR); 
}

void loop()
{
  readBME280Data(weatherData.temperature, weatherData.humidity, weatherData.pressure);
  determineUVIndex(weatherData.uvIndex);
  determineSoilMoisture(weatherData.soilMoisture);
  determineRainStatus(weatherData.rainPercent);

  String payload = encodeWeatherData(weatherData);
  sendMessage(payload);

  #if DEBUG_MODE
    printWeatherDataToSerialMonitor(weatherData);
  #endif

  endLibraries();

  esp_deep_sleep_start();
}
