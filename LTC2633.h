/*
    @file     LTC2633.h
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

#ifndef LTC2633_H
#define LTC2633_H

#if ARDUINO >= 100
#include "Arduino.h"
#define WIRE_WRITE Wire.write
#else
#include "WProgram.h"
#define WIRE_WRITE Wire.send
#endif


//Chip Address Configuration
#define LTC2633_addr_GND    (0x10)
#define LTC2633_addr_NC     (0x11)
#define LTC2633_addr_VCC    (0x12)
#define LTC2633_addr_GLOBAL (0x73)

//Command Codes
#define write_input_reg     (0x00)  //  Write to Input Register n
#define update_dac_reg      (0x01)  //  Update (Power-Up) DAC Register n
#define write_update_all    (0x02)  //  Write to Input Register n, Update (Power-Up) All
#define write_update_dac    (0x03)  //  Write to and Update (Power-Up) DAC Register n
#define power_down_dac      (0x04)  //  Power-Down n
#define power_down_all      (0x05)  //  Power-Down Chip (All DAC’s and Reference)
#define internal_reference  (0x06)  //  Select Internal Reference (Power-Up Reference)
#define external_reference  (0x07)  //  Select External Reference (Power-Down Internal Reference)
#define no_operation        (0x0F)  //  No Operation

//Address Codes
#define DAC_A               (0x00)  //Select DAC A
#define DAC_B               (0x01)  //Select DAC B
#define DAC_ALL             (0x0f)  //Select both the DACs

#include<Wire.h>

class LTC2633
{
  public:
    LTC2633();

    void begin(uint8_t CA0_state = LTC2633_addr_GLOBAL, uint8_t resolution = 12); //uses GLOBAL address and 12bits resolution, by default;
    void write(uint16_t _data, uint8_t _dac = DAC_ALL); //write and update ALL DACs, by default
    void store(uint16_t _data, uint8_t _dac = DAC_ALL); //stores data to both DAC registers, by default
    void update(uint8_t _dac = DAC_ALL); //updates previously stored value of both DAC registers
    void powerDown(uint8_t _dac = DAC_ALL);  //power down all DAC, by default
    void deepSleep(void);
    void internalReference(void);
    void externalReference(void);
    uint8_t DAC = DAC_ALL;
    uint8_t DAC0 = DAC_A;
    uint8_t DAC1 = DAC_B;

  private:
    uint8_t _i2caddr;
    uint8_t _res;
    void dataman(uint64_t _data, uint8_t &_data_high, uint8_t &_data_low);
    void writeWire(byte _code, uint8_t _data_high, uint8_t _data_low);
};


#endif
