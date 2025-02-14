#include "SA_28.h"
#include "SOILCAP.h"
#include "GUVA.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"

#include <LoraTransmitter.h>

void initializeSerialCommunication()
{
  Serial.begin(SERIAL_BAUD);
  while(!Serial) {} // wait until the serial port is ready and connected
  delay(1000); // wait for Serial Monitor to initialize
}

void configureGPIO()
{
  gpio_set_direction((gpio_num_t) RFM95_RESET_PIN, (gpio_mode_t) GPIO_MODE_OUTPUT);

  gpio_set_direction((gpio_num_t) RFM95_DIO0_PIN, (gpio_mode_t) GPIO_MODE_INPUT);
  gpio_intr_enable((gpio_num_t) RFM95_DIO0_PIN);
  gpio_set_intr_type((gpio_num_t) RFM95_DIO0_PIN, (gpio_int_type_t) GPIO_INTR_POSEDGE);

  gpio_set_direction((gpio_num_t) GUVA_PIN, (gpio_mode_t) GPIO_MODE_INPUT);
  gpio_set_direction((gpio_num_t) SOILCAP_PIN, (gpio_mode_t) GPIO_MODE_INPUT);
  gpio_set_direction((gpio_num_t) SA_28_PIN, (gpio_mode_t) GPIO_MODE_INPUT);
}

void configureLoraTransmitter()
{
  LoRa.setPins(SPI_CS0_PIN, RFM95_RESET_PIN, RFM95_DIO0_PIN);
  LoRa.setTxPower(MEDIUM_POWER_RF_AMPLIFIER, PA_OUTPUT_PA_BOOST_PIN);
}

void initializeADC(uint8_t resolution, uint8_t pin, adc_attenuation_t attenuation)
{
  analogReadResolution(resolution);
  analogSetPinAttenuation(pin, attenuation);
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
