/*
  Connecting the BME280 Sensor:
  Sensor              ->  Board
  -----------------------------
  Vin (Voltage In)    ->  3.3V
  Gnd (Ground)        ->  Gnd
  SDA (Serial Data)   ->  D21 (defined in variants\doitESP32devkitV1\pins_arduino.h)
  SCK (Serial Clock)  ->  D22 (defined in variants\doitESP32devkitV1\pins_arduino.h)
*/

#include "src/BME_280.h"

/****************************************************************/
BME280I2C::Settings bmeSettings(
    BME280I2C::OSR_X1,             // temperature oversampling 1x
    BME280I2C::OSR_X1,             // humidity oversampling 1x
    BME280I2C::OSR_X1,             // pressure oversampling 1x
    BME280I2C::Mode_Forced,        // forced mode -> make the measure, then go back to sleep
    BME280I2C::StandbyTime_1000ms, // standby time 1s, but it doesn't matter in forced mode,
                                   // because measure only happens if it is forced by the master
    BME280I2C::Filter_Off,         // turn off IIR filter
    BME280I2C::SpiEnable_False     // disable SPI mode
);

BME280I2C bme(bmeSettings);

void initializeBME280()
{
  if (!bme.begin())
  {
    Serial.println("Starting BME280 failed!");
    while (1);
  }
}

void readBME280Data(float &temperature,
                    float &humidity,
                    float &pressure)
{
  bme.read(pressure, temperature, humidity, TEMP_UNIT, PRES_UNIT);
}