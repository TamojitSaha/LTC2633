/*
    @file     LTC®2633.h
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

#ifndef LTC2633_H
#define LTC2633_H

#include "LTC2633CFG.h"
#include <Wire.h>

#if ARDUINO >= 100
#include "Arduino.h"
#define WIRE_WRITE Wire.write
#else
#include "WProgram.h"
#define WIRE_WRITE Wire.send
#endif


/*Command Codes*/
#define write_input_reg     0x00  																//Write to Input Register n
#define update_dac_reg      0x01  																//Update (Power-Up) DAC Register n
#define write_update_all    0x02  																//Write to Input Register n, Update (Power-Up) All
#define write_update_dac    0x03  																//Write to and Update (Power-Up) DAC Register n
#define power_down_dac      0x04  																//Power-Down n
#define power_down_all      0x05  																//Power-Down Chip (All DAC’s and Reference)
#define internal_reference  0x06  																//Select Internal Reference (Power-Up Reference)
#define external_reference  0x07  																//Select External Reference (Power-Down Internal Reference)
#define no_operation        0x0F  																//No Operation


class LTC2633
{
  public:
    LTC2633();

    void configure(address _address = global, resolution _resolution = XII, rate _rate = slow);	//Set I2C Address;
    void setResolution(resolution = TWELVE);                                                    //Switch DAC resolution
    void setRate(rate = slow);																	                                //Set I2C frequency;


    void internalReference(void);                                                               //Switch to internal reference voltage
    void externalReference(void);                                                               //Switch to external reference voltage


    void powerOff(void);                                                                        //Shutdown entirely
    void powerDown(DAC _dac = both);                                                            //Power down all DAC, by default
    void volt(uint64_t _data, DAC _dac = both);                                          		    //Write voltage code and update BOTH DACs, by default
    void load(DAC _dac = both);                                                         		    //Updates previously stored value of both DAC registers
    void store(uint64_t _data, DAC _dac = both);                                          		  //Stores data to both DAC registers, by default


  private:
    uint8_t rsln = 0x0C;  //Default resolution is set to TWELVE
    uint8_t adrs = 0x73;  //Default address is set to GLOBAL

    uint8_t data_low = 0x00;
    uint8_t data_high = 0x00;

    void control(uint8_t _code);
    void dataman(uint64_t _data);
    void wireman(uint8_t _code, uint8_t _data_high, uint8_t _data_low);
};


#endif
