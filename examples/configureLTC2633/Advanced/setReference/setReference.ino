/*
  @file     setReference.ino
  @author   Sandeepan Sengupta (http://sandeepan.info),
              Tamojit Saha(http://tamojitsaha.info)

  Arduino demonstration file to change reference voltage source for miniDAC module
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

void setup()
{
  myDAC.configure();

  myDAC.externalReference();
  /*
    ABOUT : Instructs LTC®2633 to switch to external reference mode and allows user to use the DAC with external reference voltage

    USAGE : It's a void type function can be used just by calling it

    ACCEPTED FORMAT:
    <put name here>.externalReference();

    EXAMPLE:
    myDAC.externalReference()   //For 'myDAC'
  */

  /*
    Note :  The following parts have POWER-ON REFERANCE MODE set to external reference.

    WARNING #2: Either use external voltage reference IC or remember switching to internal reference mode while using these parts.

    +------+------------------------------+---------+
    | Bits |        Part Number(s)        | Marking |
    +------+------------------------------+---------+
    |   12 | LTC2633A-LX12, LTC2633A-LX12 | LTFTB   |
    |   10 | LTC2633-LX10                 | LTFTH   |
    |    8 | LTC2633-LX8                  | LTFTP   |
    +------+------------------------------+---------+
  */

  myDAC.internalReference();
  /*
    ABOUT : Instructs LTC®2633 to switch to internal reference mode and allows user to use the DAC with internal reference voltage

    USAGE : It's a void type function can be used just by calling it

    ACCEPTED FORMAT:
    <put name here>.internalReference();

    EXAMPLE:
    myDAC.internalReference();  //For 'myDAC'
  */
}

void loop()
{
  ;
}
