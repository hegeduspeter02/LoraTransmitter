#include <stdint.h>
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

/****************************************************************/
uint16_t ReadAnalogSensorVoltage(const uint16_t number_of_samples, const uint8_t pin)
{
  uint32_t sensorOutputVoltageSummed = 0;

  for (int i = 0; i < number_of_samples; i++) {
    sensorOutputVoltageSummed += analogReadMilliVolts(pin);
  }

  return (uint16_t)(sensorOutputVoltageSummed / number_of_samples);
}

/****************************************************************/
uint16_t ReMapOutputVoltageRange(uint16_t& sensorOutput,
                             const uint16_t fromLowVoltage, const uint16_t fromHighVoltage,
                             const uint16_t toLow, const uint16_t toHigh)
{
  return (uint16_t) map(sensorOutput, fromLowVoltage, fromHighVoltage, toLow, toHigh); 
}

/****************************************************************/
void PrintResultsToSerialMonitor(WeatherData& weatherData)
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
