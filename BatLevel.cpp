#include "hal/adc_types.h"
#include <BatLevel.h>

Battery batt = Battery(BAT_MIN_VOLTAGE_MV, BAT_MAX_VOLTAGE_MV, BAT_LEVEL_MEAS_PIN, ADC_BITWIDTH_12);

void initializeBatLevelMeasureCircuit()
{
  batt.begin(ADC_VREF_MV, VOLTAGE_DIVIDER_RATIO, &sigmoidal);

  // automatically turn on/off the battery level sensing circuit
  batt.onDemand(BAT_LEVEL_MEAS_EN_PIN, HIGH);
}

void determineBatLevel(uint8_t &batLevel)
{
  batLevel = batt.level();
}
