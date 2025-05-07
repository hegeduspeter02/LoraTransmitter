#include "esp32-hal-gpio.h"
#include <LoraTransmitter.h>

void initializeSerialCommunication()
{
  Serial.begin(SERIAL_BAUD);
  while (!Serial)
  {
  } // wait until the serial port is ready and connected
}

void configureGPIO()
{
  pinMode(RFM95_RESET_PIN, OUTPUT);
  pinMode(RFM95_DIO0_PIN, INPUT);

  pinMode(GUVA_PIN, INPUT);
  pinMode(SOILCAP_PIN, INPUT);
  pinMode(SA_28_PIN, INPUT);
  gpio_set_pull_mode((gpio_num_t)SA_28_PIN, (gpio_pull_mode_t)GPIO_FLOATING);

  pinMode(LOW_PWR_MODE_PIN, INPUT_PULLUP);
  pinMode(HIGH_PWR_MODE_PIN, INPUT_PULLUP);

  pinMode(BAT_LEVEL_MEAS_EN_PIN, OUTPUT);
  pinMode(BAT_LEVEL_MEAS_PIN, INPUT);
}

PowerMode determinePowerMode()
{
  bool lowPowerPinState = digitalRead(LOW_PWR_MODE_PIN);
  bool highPowerPinState = digitalRead(HIGH_PWR_MODE_PIN);

  if (lowPowerPinState == HIGH && highPowerPinState == LOW)
  {
    return LOW_POWER_MODE;
  }
  else if (lowPowerPinState == HIGH && highPowerPinState == HIGH)
  {
    return MEDIUM_POWER_MODE;
  }
  else
  {
    return HIGH_POWER_MODE;
  }
}

void setLoRaPowerMode()
{
  PowerMode powerMode = determinePowerMode();

  switch (powerMode)
  {
  case LOW_POWER_MODE:
    LoRa.setTxPower(LOW_POWER_RF_AMPLIFIER, PA_OUTPUT_PA_BOOST_PIN);
    LoRa.setSpreadingFactor(LOW_POWER_SPREADING_FACTOR);
    LoRa.setSignalBandwidth(LOW_POWER_SIGNAL_BANDWIDTH);
    LoRa.setCodingRate4(MEDIUM_AND_LOW_POWER_CODING_RATE_DENOMINATOR);
    break;

  case MEDIUM_POWER_MODE:
    LoRa.setTxPower(MEDIUM_POWER_RF_AMPLIFIER, PA_OUTPUT_PA_BOOST_PIN);
    LoRa.setSpreadingFactor(MEDIUM_POWER_SPREADING_FACTOR);
    LoRa.setSignalBandwidth(HIGH_AND_MEDIUM_POWER_SIGNAL_BANDWIDTH);
    LoRa.setCodingRate4(MEDIUM_AND_LOW_POWER_CODING_RATE_DENOMINATOR);
    break;

  case HIGH_POWER_MODE:
    LoRa.setTxPower(HIGH_POWER_RF_AMPLIFIER, PA_OUTPUT_PA_BOOST_PIN);
    LoRa.setSpreadingFactor(HIGH_POWER_SPREADING_FACTOR);
    LoRa.setSignalBandwidth(HIGH_AND_MEDIUM_POWER_SIGNAL_BANDWIDTH);
    LoRa.setCodingRate4(HIGH_POWER_CODING_RATE_DENOMINATOR);
    break;
  }
}

String powerModeToString()
{
  PowerMode powerMode = determinePowerMode();
  switch (powerMode)
  {
  case LOW_POWER_MODE:
    return "Low Power Mode";
  case MEDIUM_POWER_MODE:
    return "Medium Power Mode";
  case HIGH_POWER_MODE:
    return "High Power Mode";
  }
}

CayenneLPP convertMeasureDataToLowPowerPayload(const MeasureData &measureData)
{
  CayenneLPP lpp(PAYLOAD_SIZE);
  lpp.reset();

  lpp.addTemperature(BME_280_TEMPERATURE_SENSOR_ID, measureData.temperature);
  lpp.addRelativeHumidity(BME_280_HUMIDITY_SENSOR_ID, measureData.humidity);
  lpp.addBarometricPressure(BME_280_PRESSURE_SENSOR_ID, measureData.pressure);
  lpp.addDigitalInput(UV_SENSOR_ID, measureData.uvIndex);
  lpp.addPercentage(SOIL_MOISTURE_SENSOR_ID, measureData.soilMoisture);
  lpp.addPercentage(RAIN_SENSOR_ID, measureData.rainPercent);
  lpp.addPercentage(BAT_LEVEL_ID, measureData.batLevel);

  return lpp;
}

void sendMessage(CayenneLPP &lpp)
{
  // set radio to idle mode, set up packet, use explicit header mode
  uint8_t readyToTransmit = LoRa.beginPacket();

  if (readyToTransmit)
  {
    LoRa.write(lpp.getBuffer(), lpp.getSize()); // write data to the packet

    unsigned long startTime = millis();
    LoRa.endPacket(); // finish packet and wait for transmission to complete
    unsigned long endTime = millis();

    #if DEBUG_MODE
      Serial.printf("Transmission time: %lu ms\n", endTime - startTime); // print the transmission time
    #endif
  }
}

void printMeasureDataToSerialMonitor(MeasureData &measureData)
{
  Serial.printf("Temp: %.2f °C\n"
                "Humidity: %.2f%% RH\n"
                "Pressure: %.2f hPa\n"
                "UV index: %d\n"
                "Soil moisture: %d%%\n"
                "Rain intensity: %d%%\n"
                "Battery level: %d%%\n"
                "---------------------------------------------------------\n",
                measureData.temperature,
                measureData.humidity,
                measureData.pressure,
                measureData.uvIndex,
                measureData.soilMoisture,
                measureData.rainPercent,
                measureData.batLevel);
  delay(100); // delay to prevent buffer overflow
}

void endLibraries()
{
  LoRa.end(); // put the RFM95 in sleep mode & disable spi bus
  Wire.end();
}
