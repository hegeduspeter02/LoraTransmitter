#include "esp32-hal-adc.h"
#include "hal/adc_types.h"
#include "src/BatLevel.h"

Battery batt = Battery(BAT_MIN_VOLTAGE_MV, BAT_MAX_VOLTAGE_MV, BAT_LEVEL_MEAS_PIN, ADC_BITWIDTH_12);

void initializeBatLevelMeasureCircuit()
{
  batt.begin(ADC_VREF_MV, VOLTAGE_DIVIDER_RATIO, &sigmoidal);
}

uint16_t determineBatVoltage(uint8_t msDelay)
{
  digitalWrite(BAT_LEVEL_MEAS_EN_PIN, HIGH); // turn on the battery level measure circuit
  analogRead(BAT_LEVEL_MEAS_PIN); // initializes the ADC circuitry
	delay(msDelay); // allow the ADC to stabilize
  uint16_t batVoltage = analogReadMilliVolts(BAT_LEVEL_MEAS_PIN) * VOLTAGE_DIVIDER_RATIO;
  digitalWrite(BAT_LEVEL_MEAS_EN_PIN, LOW);  // turn off the battery level measure circuit

  return batVoltage;
}

void determineBatLevel(uint8_t &batLevel)
{
  batLevel = batt.level(determineBatVoltage());
}
