/*
  @file     powerManagement.ino
  @author   Sandeepan Sengupta (http://sandeepan.info),
              Tamojit Saha(http://tamojitsaha.info)

  Arduino demonstration file for miniDAC module powerManagement
  Designed for Linear Technology LTC®2633

  ************************************************
  About LTC®2633
  ************************************************
  The LTC®2633 is a family of dual 12-, 10-, and 8-bit voltage-output DACs with an integrated, high accuracy, low drift reference in an 8-lead TSOT-23 package.

  These DACs communicate via a 2-wire I2C-compatible serial interface. The LTC®2633 operates in both the standard mode (clock rate of 100kHz) and the fast mode (clock rate of 400kHz).
  *************************************************

  WARNING #1: Parts with the following markings MUST have Vcc in the range between 4.5V and 5.5V

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

LTC2633 myDAC;                  /*declare*/

/*
  NOTE:  Please find the custom datatype(s) used in this library in table given below
  +------------+--------------------------------+---------------+
  | Data Type  |              Values            |  Description  |
  +------------+--------------------------------+---------------+
  |            | DAC0, dac0,                    |               |
  |    DAC     | DAC1, dac1,                    |   Select DAC  |
  |            | BOTH, both                     |               |
  +------------+--------------------------------+---------------+
*/

void setup()
{
  myDAC.configure();

  myDAC.powerDown();
  /*
    ABOUT : Instructs LTC®2633 to power down its individual DACs

    USAGE : Takes "DAC" (8bits of DAC register address) as input as input

    ACCEPTED FORMATS:
    <put name here>.powerDown();
    <put name here>.powerDown(dac);

    EXAMPLES:
    myDAC.powerDown();          //Switch 'myDAC' to default configuration: dac = BOTH
    myDAC.powerDown(DAC0);      //For 'myDAC'
  */

  myDAC.powerOff();
  /*
    ABOUT : Instructs LTC®2633 to power off completely

    USAGE : It's a void type function can be used just by calling it

    ACCEPTED FORMAT:
    <put name here>.powerDown();

    EXAMPLE:
    myDAC.powerOff();           //For 'myDAC'
  */
}

void loop()
{
  ;
}
