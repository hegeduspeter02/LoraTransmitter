#include <stdint.h>
#include <SA_28.h>

void determineRainStatus(uint8_t& rainPercent)
{
  uint16_t sa28Voltage = readAnalogSensorVoltage(SA_28_NO_OF_SAMPLES, SA_28_PIN);
  Serial.printf("rain voltage: %d\n", sa28Voltage);
  rainPercent = reMapOutputVoltageRange(sa28Voltage, SA_28_MEASURED_MIN_VOLTAGE,
                          SA_28_MEASURED_MAX_VOLTAGE, ONE_HUNDRED_PERCENT,
                          ZERO_PERCENT);
                          Serial.printf("rain percent: %d\n", rainPercent);
}