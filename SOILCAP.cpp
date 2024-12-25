#include <SOILCAP.h>

/****************************************************************/
void determineSoilMoisture(uint16_t& soilMoisture)
{
  uint16_t soilCapVoltage = ReadAnalogSensorVoltage(SOILCAP_NO_OF_SAMPLES, SOILCAP_PIN);
  soilMoisture = ReMapOutputVoltageRange(soilCapVoltage, SOILCAP_MEASURED_MIN_VOLTAGE,
                          SOILCAP_MEASURED_MAX_VOLTAGE, ONE_HUNDRED_PERCENT,
                          ZERO_PERCENT);
}