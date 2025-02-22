#include <CommonFunctions.h>

uint16_t readAnalogSensorVoltage(const uint16_t number_of_samples, const uint8_t pin)
{
  uint32_t sensorOutputVoltageSummed = 0;

  for (int i = 0; i < number_of_samples; i++)
  {
    sensorOutputVoltageSummed += analogReadMilliVolts(pin);
  }

  return (uint16_t)(sensorOutputVoltageSummed / number_of_samples);
}

uint16_t reMapOutputVoltageRange(uint16_t &sensorOutput,
                                const uint16_t fromLowVoltage, const uint16_t fromHighVoltage,
                                const uint16_t toLow, const uint16_t toHigh)
{
  return (uint16_t)map(sensorOutput, fromLowVoltage, fromHighVoltage, toLow, toHigh);
}