#include <stdint.h>
#include <SA_28.h>

/****************************************************************/
void determineRainStatus(uint16_t& rainPercent)
{
  uint16_t sa28Voltage = ReadAnalogSensorVoltage(SA_28_NO_OF_SAMPLES, SA_28_PIN);
  rainPercent = ReMapOutputVoltageRange(sa28Voltage, SA_28_MEASURED_MIN_VOLTAGE,
                          SA_28_MEASURED_MAX_VOLTAGE, ONE_HUNDRED_PERCENT,
                          ZERO_PERCENT);
}