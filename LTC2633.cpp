/*
    @file     LTC2633.cpp
    @author   Tamojit Saha(github.com/TamojitSaha),
              Sandeepan Sengupta (sandeepan.info)

    Arduino library part file for miniDAC module
    Designed for Linear Technology LTC®2633

    ************************************************
    About LTC®2633
    ************************************************
    The LTC®2633 is a family of dual 12-, 10-, and 8-bit voltage-output DACs with an integrated, high accuracy, low drift reference in an 8-lead TSOT-23 package.

    These DACs communicate via a 2-wire I2C-compatible serial interface. The LTC2633 operates in both the standard mode (clock rate of 100kHz) and the fast mode (clock rate of 400kHz).
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

void LTC2633::begin(uint8_t address, uint8_t resolution, bool frequency)
{
  /*
    Inatializer
    Takes ADDRESS, RESOLUTION and FREQUENCY as input
    ADDRESS is 8 bits
    RESOLUTION is 8, 10 or 12, dependant on particular variant
    FREQUENCY is HIGH (400KHz) or LOW (100KHz)
  */
  addr = address;
  if ((resolution == 8) || (resolution == 10) || (resolution == 12))
  {
    res = resolution;
  }

  freq = frequency;
  //  TWCR = 0; //Suited for AVR only
  Wire.begin();
  if (frequency)
  {
    Wire.setClock(400000L);
  }
  else
  {
    Wire.setClock(100000L);
  }
  Wire.begin();
}

void LTC2633::store(uint64_t data, uint8_t dac)
{
  /*
     Stores data to INPUT REGISTER of LTC2633
     Takes 64bit unsigned DATA (unsigned loong long int) and 8bits (byte) of DAC register address (Keywords: DAC0, DAC1, BOTH)
     Manipulates the data using dataman() and uses writeWire() to transmit it using I2C bus
  */
  dataman(data);
  writeWire(dac, data_high, data_low); /*Actually it should be -> writeWire(((write_input_reg << 4) | dac), data_high, data_low)*/
}

void LTC2633::update(uint8_t dac)
{
  /*
     Instructs LTC2633 to transfer its INPUT REGISTER data to DAC register address
     Takes DAC register address as input (8bits of unsigned int -> Keywords: DAC0, DAC1, BOTH)
     Uses control() to transmit the instruction using I2C bus
  */
  uint8_t code = (write_input_reg << 4) | dac;
  control(code);
}

void LTC2633::write(uint64_t data, uint8_t dac)
{
  /*
     Stores data to DAC register of LTC2633
     Takes 64bit unsigned DATA (unsigned loong long int) and 8bits (byte) of DAC register address (Keywords: DAC0, DAC1, BOTH)
     Manipulates the data using dataman() and uses writeWire() to transmit it using I2C bus
  */
  uint8_t code = (write_update_dac << 4) | dac;
  dataman(data);
  writeWire(code, byte(data_high), byte(data_low));
}

void LTC2633::internalReference(void)
{
  /*
     When called, it instructs LTC2633 to switch to internal reference mode and allows user to use the DAC with internal refernce voltage
  */
  uint8_t code = (internal_reference << 4) | BOTH;
  control(code);
}

void LTC2633::externalReference(void)
{
  /*
     When called, it instructs LTC2633 to switch to external reference mode and allows user to use the DAC with external refernce voltage
  */
  uint8_t code = (external_reference << 4) | BOTH;
  control(code);
}

void LTC2633::powerDown(uint8_t dac)
{
  /*
     Instructs LTC2633 to power down its individual DAC
     Takes DAC register address as input (8bits of unsigned int -> Keywords: DAC0, DAC1, BOTH)
     Uses control() to transmit the instruction using I2C bus
  */
  uint8_t code = (power_down_dac << 4) | dac;
  control(code);
}

void LTC2633::powerOff(void)
{
  /*
     Instructs LTC2633 to power off completely
     Uses control() to transmit the instruction using I2C bus
  */
  uint8_t code = power_down_all;
  control(code);
}

void LTC2633::control(uint8_t code)
{
  /*
     DECLARED IN PRIVATE : RESTRICTED ACCESS !!!
     Takes 8bits of unsigned int as instruction
     Transfers it to LTC2633 over I2C but using WIRE_WRITE
  */
  Wire.beginTransmission(addr);
  WIRE_WRITE(code);
  Wire.endTransmission();
}
void LTC2633::writeWire(uint8_t code, uint8_t data_high, uint8_t data_low)
{
  /*
     DECLARED IN PRIVATE : RESTRICTED ACCESS !!!
     Takes three 8bits of unsigned int representaing instruction, higher data bits and lower data bits
     Transfers them to LTC2633 over I2C but using WIRE_WRITE in three packets
  */
  Wire.beginTransmission(addr);
  WIRE_WRITE(code);
  WIRE_WRITE(data_high);
  WIRE_WRITE(data_low);
  Wire.endTransmission();
}

void LTC2633::dataman(uint64_t data)
{
  /*
     DECLARED IN PRIVATE : RESTRICTED ACCESS !!!
     Data manager and manipulator
     Takes 64bit unsigned DATA (unsigned loong long int)
     Constrains it in range relative to initialized resolution and segments in two 8bits of unsigned integer (declared in private)
  */
  data = constrain(data, 0, pow(2, res)); /*Constraining data in range relative to resolution*/
  uint16_t Data = (uint16_t)data;

  data = data << (16 - res);

  data_high = data >> 8;
  data_low  = data & 0xff;
}
