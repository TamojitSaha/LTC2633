/*
    @file     LTC2633.cpp
    @author   Sandeepan Sengupta (http://sandeepan.info),
              Tamojit Saha(http://tamojitsaha.info)

    Arduino library part file for miniDAC module
    Designed for Linear Technology LTC®2633

    ************************************************
    About LTC®2633
    ************************************************
    The LTC®2633 is a family of dual 12-, 10-, and 8-bit voltage-output DACs with an integrated, high accuracy, low drift reference in an 8-lead TSOT-23 package.

    These DACs communicate via a 2-wire I2C-compatible serial interface. The LTC®2633 operates in both the standard mode (clock rate of 100kHz) and the fast mode (clock rate of 400kHz).
    *************************************************

    Version: 1.0.0
    Released under CC-BY-NC-SA 4.0 (https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode)
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

void LTC2633::configure(configuration _cfg)
{
  /*
    Takes 8bits of I2C Address (Data Type: "address")
    and
    DAC resolution in bit(s) (Data Type: "resolution")
    and
    I2C transfer rate as input(s) (Data Type: "rate")
  */
  Wire.begin();
  Wire.setClock(_cfg.Rate);
  Wire.end();
  adrs = _cfg.Address;
  rsln = _cfg.Resolution;
}

void LTC2633::setRate(rate _rte)
{
  /*
    Sets I2C transfer rate (clock frequency)
  */
  Wire.begin();
  Wire.setClock(_rte);
  Wire.end();
}

void LTC2633::setResolution(resolution _rsl)
{
  /*
    Sets DAC resolution
  */
  rsln = _rsl;
}

void LTC2633::volt(uint64_t data, DAC dac)
{
  /*
     Stores data to DAC register of LTC®2633
     Takes 64bit unsigned integer (unsigned long long int) and "DAC" (8bits of DAC register address) as input
     Manipulates the data using dataman() and uses wireman() to transmit it using I2C bus
  */
  uint8_t code = (write_update_dac << 4) | dac;
  dataman(data);
  wireman(code, byte(data_high), byte(data_low));
}

void LTC2633::load(DAC dac)
{
  /*
     Instructs LTC®2633 to transfer its input register data to DAC register address
     Takes "DAC" (8bits of DAC register address) as input
     Uses control() to transmit the instruction using I2C bus
  */
  uint8_t code = (write_input_reg << 4) | dac;
  control(code);
}

void LTC2633::store(uint64_t data, DAC dac)
{
  /*
     Stores data to input register of LTC®2633
     Takes 64bit unsigned integer (unsigned long long int) and "DAC" (8bits of DAC register address) as input
     Manipulates the data using dataman() and uses wireman() to transmit it using I2C bus
  */
  dataman(data);
  wireman(dac, data_high, data_low); /*Actually it should be -> wireman(((write_input_reg << 4) | dac), data_high, data_low)*/
}

void LTC2633::powerOff(void)
{
  /*
     Instructs LTC®2633 to power off completely
     Uses control() to transmit the instruction using I2C bus
  */
  uint8_t code = power_down_all;
  control(code);
}

void LTC2633::powerDown(DAC dac)
{
  /*
     Instructs LTC®2633 to power down its individual DAC
     Takes "DAC" (8bits of DAC register address) as input
     Uses control() to transmit the instruction using I2C bus
  */
  uint8_t code = (power_down_dac << 4) | dac;
  control(code);
}

void LTC2633::internalReference(void)
{
  /*
     When called, it instructs LTC®2633 to switch to internal reference mode and allows user to use the DAC with internal reference voltage
  */
  uint8_t code = (internal_reference << 4) | 0x0f;
  control(code);
}

void LTC2633::externalReference(void)
{
  /*
     When called, it instructs LTC®2633 to switch to external reference mode and allows user to use the DAC with external reference voltage
  */
  uint8_t code = (external_reference << 4) | 0x0f;
  control(code);
}

void LTC2633::control(uint8_t code)
{
  /*
     DECLARED IN PRIVATE : RESTRICTED ACCESS !!!
     Takes 8bits of number representing instruction (byte)
     Transfers it to LTC®2633 over I2C but using WIRE_WRITE
  */
  Wire.begin(adrs);
  WIRE_WRITE(code);
  Wire.end();
}

void LTC2633::wireman(uint8_t code, uint8_t data_high, uint8_t data_low)
{
  /*
     DECLARED IN PRIVATE : RESTRICTED ACCESS !!!
     Takes three 8bits of number representing instruction (byte), higher data bits and lower data bits
     Transfers them to LTC®2633 over I2C but using WIRE_WRITE in three packets
  */
  Wire.begin(adrs);
  WIRE_WRITE(code);
  WIRE_WRITE(data_high);
  WIRE_WRITE(data_low);
  Wire.end();
}

void LTC2633::dataman(uint64_t data)
{
  /*
     DECLARED IN PRIVATE : RESTRICTED ACCESS !!!
     Data manager and manipulator
     Takes 64bit unsigned integer (unsigned long long int)
     Constrains it in range relative to initialized resolution and segments in two 8bits of unsigned integer (declared in private)
  */
  uint16_t Data = (uint16_t)constrain(data, 0, pow(2, rsln)); /*Constraining data in range relative to resolution*/;

  Data = Data << (16 - rsln);

  data_high = Data >> 8;
  data_low  = Data & 0xff;
}
