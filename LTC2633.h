/*
    @file     LTC2633.h
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

#ifndef LTC2633_H
#define LTC2633_H

#if ARDUINO >= 100
#include "Arduino.h"
#define WIRE_WRITE Wire.write
#else
#include "WProgram.h"
#define WIRE_WRITE Wire.send
#endif


/*LTC2633 I2C Transfer Rate*/
#define SLOW    			0x0186A0
#define slow    			0x0186A0
#define FAST    			0x061A80
#define fast    			0x061A80

/*LTC2633 Resolution*/
#define VIII    			0x08
#define viii    			0x08
#define X     				0x0A
#define x     				0x0a
#define XII    				0x0C
#define xii    				0x0c

/*LTC2633 Address Configuration*/
#define GND    				0x10
#define gnd    				0x10
#define NC     				0x11
#define nc     				0x11
#define VCC    				0x12
#define vcc    				0x12
#define ALL 				0x73
#define all 				0x73
#define GLOBAL 				0x73
#define global 				0x73
// #define CUSTOM 				0xZZ	//Reserved for custom address
// #define custom 				0xZZ

/*Command Codes*/
#define write_input_reg     0x00  //  Write to Input Register n
#define update_dac_reg      0x01  //  Update (Power-Up) DAC Register n
#define write_update_all    0x02  //  Write to Input Register n, Update (Power-Up) All
#define write_update_dac    0x03  //  Write to and Update (Power-Up) DAC Register n
#define power_down_dac      0x04  //  Power-Down n
#define power_down_all      0x05  //  Power-Down Chip (All DAC’s and Reference)
#define internal_reference  0x06  //  Select Internal Reference (Power-Up Reference)
#define external_reference  0x07  //  Select External Reference (Power-Down Internal Reference)
#define no_operation        0x0F  //  No Operation

/*Address Codes*/
#define DAC0                0x00  //Select DAC A
#define dac0                0x00
#define DAC1                0x01  //Select DAC B
#define dac1                0x01
#define BOTH                0x0F  //Select both the DACs
#define both                0x0f

#include<Wire.h>

class LTC2633
{
  public:
    LTC2633();

    void begin(uint8_t _address = 0x73, uint8_t _resolution = 0x0C, uint64_t _frequency = 0x061A80);  //Initialize, uses GLOBAL address and 12bits resolution, by default;
    /*
       Default resolution value is assigned to be used for the following parts:

       +---------+-----------------------------+
       | Marking |         Part Number(s)      |
       +---------+-----------------------------+
       | LTFTC   | LTC2633A-LI12, LTC2633-LI12 |
       | LTFTB   | LTC2633A-LX12, LTC2633-LX12 |
       | LTFSZ   | LTC2633A-LZ12, LTC2633-LZ12 |
       | LTFTV   | LTC2633A-LO12, LTC2633-LO12 |
       | LTFTF   | LTC2633A-HI12, LTC2633-HI12 |
       | LTFTD   | LTC2633A-HZ12, LTC2633-HZ12 |
       +---------+-----------------------------+

    */

    void write(uint64_t _data, uint8_t _dac = 0x0F);                                          //Write and update ALL DACs, by default
    void store(uint64_t _data, uint8_t _dac = 0x0F);                                          //Stores data to both DAC registers, by default
    void update(uint8_t _dac = 0x0F);                                                         //Updates previously stored value of both DAC registers
    void powerDown(uint8_t _dac = 0x0F);                                                      //Power down all DAC, by default
    void powerOff(void);                                                                      //Shutdown entirely
    void internalReference(void);                                                             //Switch to internal reference voltage
    void externalReference(void);                                                             //Switch to external reference voltage

  private:
    uint8_t data_high;
    uint8_t data_low;

    uint8_t addr;
    uint8_t res;
    bool freq;
    void dataman(uint64_t _data);
    void control(uint8_t _code);
    void writeWire(uint8_t _code, uint8_t _data_high = 0x00, uint8_t _data_low = 0x00);
};


#endif
