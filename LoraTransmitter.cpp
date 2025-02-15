#include <LoraTransmitter.h>

adc_oneshot_unit_handle_t adc1_handle;
adc_oneshot_unit_handle_t adc2_handle;

adc_oneshot_chan_cfg_t adc_config = {
  .atten = ADC_ATTEN_DB_12,
  .bitwidth = ADC_BITWIDTH_12,
};

void initializeSerialCommunication()
{
  Serial.begin(SERIAL_BAUD);
  while(!Serial) {} // wait until the serial port is ready and connected
  delay(1000); // wait for Serial Monitor to initialize
}

void initializeADCs()
{
  adc_oneshot_unit_init_cfg_t adc1_init_config = {
    .unit_id = ADC_UNIT_1,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
  };

  adc_oneshot_unit_init_cfg_t adc2_init_config = {
    .unit_id = ADC_UNIT_2,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
  };

  ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc1_init_config, &adc1_handle));
  ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc2_init_config, &adc2_handle));
}

void configureADC(adc_unit_t unit_id, adc_channel_t channel)
{
  if (unit_id == ADC_UNIT_1) {
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, channel, &adc_config));
  }
  else {
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc2_handle, channel, &adc_config));
  }
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

CayenneLPP convertWeatherDataToLowPowerPayload(const WeatherData& weatherData)
{
  CayenneLPP lpp(MAX_PAYLOAD_SIZE);
  lpp.reset();

  lpp.addTemperature(BME_280_SENSOR_IDENTIFIER, weatherData.temperature);
  lpp.addRelativeHumidity(BME_280_SENSOR_IDENTIFIER, weatherData.humidity);
  lpp.addBarometricPressure(BME_280_SENSOR_IDENTIFIER, weatherData.pressure);
  lpp.addDigitalOutput(UV_SENSOR_IDENTIFIER, weatherData.uvIndex);
  lpp.addDigitalOutput(SOIL_MOISTURE_SENSOR_IDENTIFIER, weatherData.soilMoisture);
  lpp.addDigitalOutput(RAIN_SENSOR_IDENTIFIER, weatherData.rainPercent);

  return lpp;
}

String convertLowPowerPayloadToHexadecimalString(CayenneLPP& lpp)
{
  String lppString;

  for (int i = 0; i < lpp.getSize(); i++) {
    char buffer[3];
    sprintf(buffer, "%02X", lpp.getBuffer()[i]); // convert each byte to hex
    lppString += buffer;
  }

  return lppString;
}

String encodeWeatherData(const WeatherData& weatherData)
{
  CayenneLPP lpp = convertWeatherDataToLowPowerPayload(weatherData);
  String lppString = convertLowPowerPayloadToHexadecimalString(lpp);

  return lppString;
}

void sendMessage(const String& payload)
{
  // set radio to idle mode, set up packet, use explicit header mode
  uint8_t readyToTransmit = LoRa.beginPacket();

  if(readyToTransmit)
  {
    // write data to the packet
    LoRa.print(payload);

    // finish packet and wait for transmission to complete
    LoRa.endPacket();

    Serial.println("Packet was sent.");
    delay(100); // Small delay to prevent buffer overflow
  }
}

void printWeatherDataToSerialMonitor(WeatherData& weatherData)
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
}
