/*
  @file     reConfigure.ino
  @author   Sandeepan Sengupta (http://sandeepan.info),
              Tamojit Saha(http://tamojitsaha.info)

  Arduino demonstration file to reConfigure miniDAC module
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
  NOTE #1:  Please find the custom datatype(s) used in this library in table given below
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
*/

void setup()
{
  myDAC.configure();
  myDAC.internalReference();

  myDAC.setRate();
  /*
    ABOUT : Set I2C clock frequency

    USAGE : Takes "rate" (transfer rate in Hz) as input

    ACCEPTED FORMATS :
    <put name here>.setRate();
    <put name here>.setRate(Rate);

    EXAMPLES:
    myDAC.setRate();               //Set I2C clock frequency to 100KHz (default)
    myDAC.setRate(FAST);           //Set I2C clock frequency to 400KHz
  */
  myDAC.setResolution();
  /*
    ABOUT : Defines LTC®2633 resolution

    USAGE : Takes "resolution" (resolution value in bits) as input

    ACCEPTED FORMATS :
    <put name here>.setResolution();      		//Defines resolution as 12 bits (default)
    <put name here>.setResolution(Resolution);	//Defines resolution as user specifies with proper keyword

    Note #2: Unless changed by calling function with proper resolution(Keyword) listed below, system initializes to 12 bits resolution setup.

    +--------------------------+-------------------------------+
    |         Keyword          |          Operation            |
    +--------------------------+-------------------------------+
    | viii, VIII, eight, EIGHT | Defines resolution as 8 bits  |
    | x, X, ten, TEN           | Defines resolution as 10 bits |
    | xii, XII, twelve, TWELVE | Defines resolution as 12 bits |
    +--------------------------+-------------------------------+

    WARNING #2: Even when using these function, make sure it matches to the particular LTC®2633 variant to avoid unexpected behavior.

    Please verify markings on IC with the following table:

    +------+------------------------------------------+
    | Bits |                 Marking(s)               |
    +------+------------------------------------------+
    |   12 | LTFTC, LTFTB, LTFSZ, LTFTV, LTFTF, LTFTD |
    |   10 | LTFTJ, LTFTH, LTFTG, LTFTW, LTFTM, LTFTK |
    |    8 | LTFTQ, LTFTP, LTFSZ, LTFTN, LTFTS, LTFTR |
    +------+------------------------------------------+

    EXAMPLES:
    myDAC.setResolution();      //Defines resolution as 12 bits
    myDAC.setResolution(X);		//Defines resolution as 10 bits
  */
}

void loop()
{
  ;
}
