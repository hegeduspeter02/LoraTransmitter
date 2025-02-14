#include <GUVA.h>

uint8_t convertVoltageToUVIndex(uint16_t& guvaVoltage)
{
  uint16_t voltageToConvert = reMapOutputVoltageRange(guvaVoltage, GUVA_MEASURED_MIN_VOLTAGE,
                          GUVA_MEASURED_MAX_VOLTAGE, GUVA_TARGET_MIN_VOLTAGE,
                          GUVA_TARGET_MAX_VOLTAGE);

  if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[0]) return 0;
  else if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[1]) return 1;
  else if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[2]) return 2;
  else if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[3]) return 3;
  else if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[4]) return 4;
  else if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[5]) return 5;
  else if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[6]) return 6;
  else if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[7]) return 7;
  else if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[8]) return 8;
  else if (voltageToConvert < UV_VOLTAGE_UPPER_THRESHOLDS[9]) return 9;
  else return 10;
}

void determineUVIndex(uint8_t& uvIndex)
{
  uint16_t guvaVoltage = readAnalogSensorVoltage(GUVA_NO_OF_SAMPLES, GUVA_PIN);
  uvIndex = convertVoltageToUVIndex(guvaVoltage);
}