/*
  @file     Basic.ino
  @author   Sandeepan Sengupta (http://sandeepan.info),
              Tamojit Saha(http://tamojitsaha.info)

  Arduino demonstration file to configure miniDAC module
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
  NOTE :  Please find the custom datatype(s) used in this library in table given below
  +------------+--------------------------------+---------------+
  | Data Type  |              Values            |  Description  |
  +------------+--------------------------------+---------------+
  |            | FAST, fast,                    |    Set        |
  |   rate     | SLOW, slow,                    |  I2C Speed    |
  +------------+--------------------------------+---------------+
  |            | VIII, viii, eight, EIGHT       |     Set       |
  | resolution | X, x, ten, TEN                 |     DAC       |
  |            | XII, xii, twelve, TWELVE       |   Resolution  |
  +------------+--------------------------------+---------------+
  |            | NC, nc,                        |               |
  |            | GND, gnd,                      |               |
  |  address   | VCC, vcc,                      | Select DAC    |
  |            | ALL, all,                      | address (I2C) |
  |            | GLOBAL, global                 |               |
  +------------+--------------------------------+---------------+

*/

void setup()
{
  myDAC.configure();
  /*
    ABOUT : Confiure DAC address, resolution and I2C transfer rate

    USAGE : Takes 8bits of I2C Address (Data Type: "address")
            and
            DAC resolution in bit(s) (Data Type: "resolution")
            and
            I2C transfer rate as input(s) (Data Type: "rate")

    ACCEPTED FORMATS :
    <put name here>.configure();
    <put name here>.configure(Address);
    <put name here>.configure(Address, Resolution);
    <put name here>.configure(Address, Resolution, Rate);

    EXAMPLES:
    myDAC.cfgr();
    //Switch 'myDAC' to default configuration:
      //Address = GLOBAL (0x73)
      //Resolution = XII (0x0C)
      //Rate = slow (0x0186A0)

    myDAC.configure(VCC);
    //Switch 'myDAC' to given configuration:
      //Address = VCC (0x12)

    myDAC.configure(VCC, XII);
    //Switch 'myDAC' to given configuration:
      //Address = VCC (0x12),
      //Resolution = XII (0x0C)

    myDAC.configure(VCC, xii, slow);
    //Switch 'myDAC' to given configuration:
      //Address = VCC (0x12),
      //Resolution = XII (0x0C),
      //Rate = slow (0x0186A0)
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
