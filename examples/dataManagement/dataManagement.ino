/*
  @file     dataManagement.ino
  @author   Sandeepan Sengupta (http://sandeepan.info),
              Tamojit Saha(http://tamojitsaha.info)

  Arduino demonstration file to generate analog voltage using miniDAC module
  Designed for Linear Technology LTC®2633

  ************************************************
  About LTC®2633
  ************************************************
  The LTC®2633 is a family of dual 12-, 10-, and 8-bit voltage-output DACs with an integrated, high accuracy, low drift reference in an 8-lead TSOT-23 package.

  These DACs communicate via a 2-wire I2C-compatible serial interface. The LTC®2633 operates in both the standard mode (clock rate of 100kHz) and the fast mode (clock rate of 400kHz).
  *************************************************

  WARNING : Parts with the following markings MUST have Vcc in the range between 4.5V and 5.5V

  +------+---------+-----------------------------+
  | Bits | Marking |       Part Number(s)        |
  +------+---------+-----------------------------+
  |   12 | LTFTF   | LTC2633A-HI12, LTC2633-HI12 |
  |      | LTFTD   | LTC2633A-HZ12, LTC2633-HZ12 |
  +------+---------+-----------------------------+
  |   10 | LTFTM   | LTC2633-HI10                |
  |      | LTFTK   | LTC2633-HZ10                |
  +------+---------+-----------------------------+
  |    8 | LTFTS   | LTC2633-HI8                 |
  |      | LTFTR   | LTC2633-HZ8                 |
  +------+---------+-----------------------------+

  Version : 1.0.0
  Released under CC-BY-NC-SA 4.0 (https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode)
  All text above, must be included in any redistribution
*/

#include <LTC2633.h>
#define __resolution 12 //demo only

LTC2633 myDAC;                  /*declare*/

/*
  NOTE #1:  Please find the custom datatype(s) used in this library in table given below
  +------------+--------------+---------------+
  | Data Type  |    Values    |  Description  |
  +------------+--------------+---------------+
  |            | DAC0, dac0,  |               |
  |    DAC     | DAC1, dac1,  |   Select DAC  |
  |            | BOTH, both   |               |
  +------------+--------------+---------------+

  NOTE #2:  Please follow the keyword table given below
  +#######################################################################+
  +--------------+--------------+
  |              | DATA, data,  |
  |    Extras    | VALUE, value |
  +--------------+--------------+
*/

void setup()
{
  myDAC.configure();
  myDAC.internalReference();
}

void loop()
{
  uint64_t value = random(0, pow(2, __resolution)); /*generate a random number in range (for testing purposes only)*/

  myDAC.store(value);
  /*
    ABOUT : Stores value to input register of LTC®2633

    USAGE : Takes 64bit unsigned integer (unsigned long long int)
            and
            "DAC" (8bits of DAC register address) as input(s)

    ACCEPTED FORMATS:
    <put name here>.store(VALUE);
    <put name here>.store(VALUE, DAC);

    EXAMPLES:
    myDAC.store(value);         //Given, 'value' is supplied, switch 'myDAC' to default configuration: DAC = BOTH
    myDAC.store(value, DAC0);   //For 'myDAC', 'value' must be supplied
  */

  myDAC.load(BOTH);
  /*
    ABOUT : Instructs LTC®2633 to transfer its input register data to respective DAC register

    USAGE : Takes "DAC" (8bits of DAC register address) as input as input

    Note #5 : Recommended to use after 'value' is '<put name here>.store()' -ed earlier

    ACCEPTED FORMATS:
    <put name here>.load();
    <put name here>.load(dac);

    EXAMPLES:
    myDAC.load();               //Switch 'myDAC' to default configuration: dac = BOTH
    myDAC.load(DAC0);
  */

  myDAC.volt(value, both);
  /*
    ABOUT : Stores 'value' to DAC register of LTC®2633

    USAGE : Takes 64bit unsigned DATA (unsigned long long int)
            and
            "DAC" (8bits of DAC register address) as input(s)

    ACCEPTED FORMATS:
    <put name here>.volt(VALUE);
    <put name here>.volt(value, dac);

    EXAMPLES:
    myDAC.volt(VALUE);          //Given, 'value' is supplied, switch 'myDAC' to default configuration: dac = BOTH
    myDAC.volt(value, DAC0);    //For 'myDAC', 'value' must be supplied
  */
}
