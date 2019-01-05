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

    Version: 0.1.0
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

void LTC2633::link(uint8_t address)
{
  /*
    Takes 8bits of I2C address as input
  */
  if ((address == 0x10) || (address == 0x11) || (address == 0x12) || (address == 0x73))
  {
	    adrs = address;
  }
  else
  {
	  adrs = 0x73;
  }
}

void LTC2633::slow()
{
  /*
	Set I2C frequency to 100KHz
  */
  Wire.begin();
  Wire.setClock(0x0186A0);
  Wire.begin();
}

void LTC2633::fast()
{
  /*
	Set I2C frequency to 400KHz
  */
  Wire.begin();
  Wire.setClock(0x061A80);
  Wire.begin();
}

void LTC2633::volt(uint64_t data, uint8_t dac)
{
  /*
     Stores data to DAC register of LTC2633
     Takes 64bit unsigned integer (unsigned long long int) and 8bits (byte) of DAC register address
     Manipulates the data using dataman() and uses writeWire() to transmit it using I2C bus
  */
  uint8_t code = (write_update_dac << 4) | dac;
  dataman(data);
  writeWire(code, byte(data_high), byte(data_low));
}

void LTC2633::load(uint8_t dac)
{
  /*
     Instructs LTC2633 to transfer its input register data to DAC register address
     Takes 8bits of DAC register address (byte) as input
     Uses control() to transmit the instruction using I2C bus
  */
  uint8_t code = (write_input_reg << 4) | dac;
  control(code);
}

void LTC2633::store(uint64_t data, uint8_t dac)
{
  /*
     Stores data to input register of LTC2633
     Takes 64bit unsigned integer (unsigned long long int) and 8bits (byte) of DAC register address
     Manipulates the data using dataman() and uses writeWire() to transmit it using I2C bus
  */
  dataman(data);
  writeWire(dac, data_high, data_low); /*Actually it should be -> writeWire(((write_input_reg << 4) | dac), data_high, data_low)*/
}


void LTC2633::x08(void)
{
  /*
	Defines resolution as 8bits
  */
  rsln = 0x08;
}

void LTC2633::x0A(void)
{
  /*
	Defines resolution as 10bits
  */
  rsln = 0x0A;
}

void LTC2633::x0C(void)
{
  /*
	Defines resolution as 12bits
  */
  rsln = 0x0C;
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

void LTC2633::powerDown(uint8_t dac)
{
  /*
     Instructs LTC2633 to power down its individual DAC
     Takes DAC 8bits of register address (byte) as input
     Uses control() to transmit the instruction using I2C bus
  */
  uint8_t code = (power_down_dac << 4) | dac;
  control(code);
}

void LTC2633::internalReference(void)
{
  /*
     When called, it instructs LTC2633 to switch to internal reference mode and allows user to use the DAC with internal reference voltage
  */
  uint8_t code = (internal_reference << 4) | BOTH;
  control(code);
}

void LTC2633::externalReference(void)
{
  /*
     When called, it instructs LTC2633 to switch to external reference mode and allows user to use the DAC with external reference voltage
  */
  uint8_t code = (external_reference << 4) | BOTH;
  control(code);
}

void LTC2633::control(uint8_t code)
{
  /*
     DECLARED IN PRIVATE : RESTRICTED ACCESS !!!
     Takes 8bits of number representing instruction (byte)
     Transfers it to LTC2633 over I2C but using WIRE_WRITE
  */
  Wire.beginTransmission(adrs);
  WIRE_WRITE(code);
  Wire.endTransmission();
}
void LTC2633::writeWire(uint8_t code, uint8_t data_high, uint8_t data_low)
{
  /*
     DECLARED IN PRIVATE : RESTRICTED ACCESS !!!
     Takes three 8bits of number representing instruction (byte), higher data bits and lower data bits
     Transfers them to LTC2633 over I2C but using WIRE_WRITE in three packets
  */
  Wire.beginTransmission(adrs);
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
     Takes 64bit unsigned integer (unsigned long long int)
     Constrains it in range relative to initialized resolution and segments in two 8bits of unsigned integer (declared in private)
  */
  uint16_t Data = (uint16_t)constrain(data, 0, pow(2, rsln)); /*Constraining data in range relative to resolution*/;

  Data = Data << (16 - rsln);

  data_high = Data >> 8;
  data_low  = Data & 0xff;
}
