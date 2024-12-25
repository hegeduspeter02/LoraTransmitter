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
void ReadAnalogSensorVoltage(const uint16_t number_of_samples, const uint8_t pin)
{
  uint32_t sensorOutputVoltageSummed = 0;

  for (int i = 0; i < number_of_samples; i++) {
    sensorOutputVoltageSummed += analogReadMilliVolts(pin);
  }

  return (uint16_t)(sensorOutputVoltageSummed / number_of_samples);
}

/****************************************************************/
void ReMapOutputVoltageRange(uint16_t& sensorOutput,
                             const uint16_t fromLowVoltage, const uint16_t fromHighVoltage,
                             const uint16_t toLow, const uint16_t toHigh)
{
  return (uint16_t) map(sensorOutput, fromLowVoltage, fromHighVoltage, toLow, toHigh); 
}

/****************************************************************/
void PrintResultsToSerialMonitor(WeatherData& weatherData)
{
  Serial.printf("Temp: %.2f°C\t\tHumidity: %.2f%% RH\t\tPressure: %.2f hPa\n"
                "UV index: %d\n"
                "Soil moisture: %d%%\n"
                "Rain percent: %d%%\n"
                "---------------------------------------------------------\n", 
                weatherData.temperature, weatherData.humidity, weatherData.pressure,
                weatherData.uvIndex,
                weatherData.soilMoisture,
                weatherData.rainPercent);
}
