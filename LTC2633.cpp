/*
    @file     LTC2633.cpp
    @author   Tamojit Saha(github.com/TamojitSaha),
              Sandeepan Sengupta (sandeepan.info)

    Arduino library for Linear Technology LTC®2633

    ************************************************
    About LTC®2633
    ************************************************
    The LTC®2633 is a family of dual 12-, 10-, and 8-bit voltage-output DACs with an integrated, high accuracy, low drift reference in an 8-lead TSOT-23 package.

    These DACs communicate via a 2-wire I2C-compatible serial interface. The LTC2633 operates in both the standard mode (clock rate of 100kHz) and the fast mode (clock rate of 400kHz).
    *************************************************

    v0.1 - Alpha Release
    All text above, must be included in any redistribution

*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include "LTC2633.h"

LTC2633::LTC2633()
{

}

void LTC2633::begin(uint8_t i2caddr, uint8_t res)
{
  _i2caddr = i2caddr;
  _res = res;
  TWCR = 0;
  Wire.begin();
  Wire.setClock(400000L);
  Wire.begin();
}

void LTC2633::dataman(uint64_t data, uint8_t &data_high, uint8_t &data_low)
{
  data = constrain(data, 0, pow(2, _res)); /*Constraining data in range relative to resolution*/
  uint16_t Data = (uint16_t)data;

  data = data << (16 - _res);
  data_high = data >> 8;
  data_low  = data & 0xff;
}

void LTC2633::store(uint16_t data, uint8_t dac)
{
  uint8_t data_high, data_low;
  dataman(data, data_high, data_low);
  writeWire(dac, data_high, data_low); /*writeWire(((write_input_reg << 4) | dac), data_high, data_low)*/
}

void LTC2633::update(uint8_t dac)
{
  uint8_t code = (write_input_reg << 4) | dac;
  writeWire(code, 0x00, 0x00);
}

void LTC2633::write(uint16_t data, uint8_t dac)
{
  uint8_t code = (write_update_dac << 4) | dac;

  uint8_t data_high, data_low;
  dataman(data, data_high, data_low);

  writeWire(code, byte(data_high), byte(data_low));
}

void LTC2633::internalReference(void)
{
  uint8_t code = (internal_reference << 4) | DAC;
  writeWire(code, 0x00, 0x00);
}

void LTC2633::externalReference(void)
{
  uint8_t code = (external_reference << 4) | DAC;
  writeWire(code, 0x00, 0x00);
}

void LTC2633::powerDown(uint8_t dac)
{
  uint8_t code = (power_down_dac << 4) | dac;
  writeWire(code, 0x00, 0x00);
}

void LTC2633::deepSleep(void)
{
  uint8_t code = power_down_all;
  writeWire(code, 0x00, 0x00);
}

void LTC2633::writeWire(uint8_t code, uint8_t data_high, uint8_t data_low)
{
  Wire.beginTransmission(_i2caddr);
  WIRE_WRITE(code);
  WIRE_WRITE(data_high);
  WIRE_WRITE(data_low);
  Wire.endTransmission();
}

