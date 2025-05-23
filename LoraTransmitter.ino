#include <LoraTransmitter.h>

MeasureData measureData;

void setup()
{
  initializeSerialCommunication();

  setCpuFrequencyMhz(80); // MHz

  configureGPIO();

  Wire.begin(); // set the SDA and SCK pins on the ESP

  SPI.begin(SPI_SCLK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS0_PIN); // set SPI pins
  LoRa.setSPI(SPI);

  LoRa.setPins(SPI_CS0_PIN, RFM95_RESET_PIN, RFM95_DIO0_PIN);

  initializeBME280();
  initializeBatLevelMeasureCircuit();

  if (!LoRa.begin(RFM95_COMM_FREQ))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  setLoRaPowerMode();
  esp_sleep_enable_timer_wakeup(RFM95_SEND_RATE * uS_TO_S_FACTOR);
}

void loop()
{
  readBME280Data(measureData.temperature, measureData.humidity, measureData.pressure);
  determineUVIndex(measureData.uvIndex);
  determineSoilMoisture(measureData.soilMoisture);
  determineRainStatus(measureData.rainPercent);
  determineBatLevel(measureData.batLevel);

  CayenneLPP lpp = convertMeasureDataToLowPowerPayload(measureData);
  sendMessage(lpp);

#if DEBUG_MODE
  printMeasureDataToSerialMonitor(measureData);
#endif

  endLibraries();

  esp_deep_sleep_start();
}
