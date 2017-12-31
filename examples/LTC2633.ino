/*
    @file     LTC2633.ino
    @author   Tamojit Saha(github.com/TamojitSaha),
              Sandeepan Sengupta (sandeepan.info)

    Arduino demonstration file for miniDAC module
    Designed for Linear Technology LTC®2633

    ************************************************
    About LTC®2633
    ************************************************
    The LTC®2633 is a family of dual 12-, 10-, and 8-bit voltage-output DACs with an integrated, high accuracy, low drift reference in an 8-lead TSOT-23 package.

    These DACs communicate via a 2-wire I2C-compatible serial interface. The LTC2633 operates in both the standard mode (clock rate of 100kHz) and the fast mode (clock rate of 400kHz).
    *************************************************

    WARNING #1: Parts with the following markings MUST be have Vcc in the range between 4.5V and 5.5V
    
    +------+---------+-----------------------------+
    | Bits | Marking |       Part Number(s)        |
    +------+---------+-----------------------------+
    |   12 | LTFTF   | LTC2633A-HI12, LTC2633-HI12 |
    |   12 | LTFTD   | LTC2633A-HZ12, LTC2633-HZ12 |
    |   10 | LTFTM   | LTC2633-HI10                |
    |   10 | LTFTK   | LTC2633-HZ10                |
    |    8 | LTFTS   | LTC2633-HI8                 |
    |    8 | LTFTR   | LTC2633-HZ8                 |
    +------+---------+-----------------------------+

    Version: 1.0.0
    Released under CC-BY-NC-SA 4.0 (https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode)
    All text above, must be included in any redistribution
*/

#include "LTC2633.h"
LTC2633 myDAC; /*declare*/

#define resolution 12                               //here you can set resolution

void setup()
{
  myDAC.begin();
  /* USAGE:

     Initialize with ADDRESS, RESOLUTION and FREQUENCY

     Accepted formats:
     <put name here>.begin(ADDRESS, RESOLUTION, FREQUENCY);

     ADDRESS keywords: VCC, NC, GND, GLOBAL
     RESOLUTION keywords/values: 8, 10, 12
     FREQUENCY keywords/values: LOW (0) or HIGH (1)

     Note #1    : RESOLUTION value other than 8, 10 or 12 will be rejected and system will switch to 12 bits resolution setup

     WARNING #2 : Even when using values 8, 10 or 12, make sure its according to LTC2633 specification.
     Please verify markings on IC with the following table:

     +------+------------------------------------------+
     | Bits |                 Marking(s)               |
     +------+------------------------------------------+
     |   12 | LTFTC, LTFTB, LTFSZ, LTFTV, LTFTF, LTFTD |
     |   10 | LTFTJ, LTFTH, LTFTG, LTFTW, LTFTM, LTFTK |
     |    8 | LTFTQ, LTFTP, LTFSZ, LTFTN, LTFTS, LTFTR |
     +------+------------------------------------------+

     examples:
     <put name here>.begin();                       //Switch to default configuration: ADDRESS = GLOBAL, RESOLUTION = 12, FREQUENCY = HIGH
     <put name here>.begin(VCC);                    //Switch to default configuration: RESOLUTION = 12, FREQUENCY = HIGH
     <put name here>.begin(NC, resolution);         //Given, 'resolution' value is supplied, Switch to default configuration: FREQUENCY = HIGH
     <put name here>.begin(GND, resolution, LOW);   //'resolution' value must be supplied
  */

  myDAC.externalReference();
  /* USAGE:

     Instructs LTC2633 to switch to external reference mode and allows user to use the DAC with external refernce voltage

     Accepted format:
     <put name here>.externalReference();

     Example
     myDAC.externalReference()                      //For 'myDAC'

  */

  /* Note #2    :The following parts have POWER-ON REFERANCE MODE set to EXTERNAL REFERENCE.
     Either use external voltage reference IC or remember switching to INTERNAL REFERANCE mode while using these parts.

     +------+------------------------------+---------+
     | Bits |        Part Number(s)        | Marking |
     +------+------------------------------+---------+
     |   12 | LTC2633A-LX12, LTC2633A-LX12 | LTFTB   |
     |   10 | LTC2633-LX10                 | LTFTH   |
     |    8 | LTC2633-LX8                  | LTFTP   |
     +------+------------------------------+---------+
  */

  myDAC.internalReference();
  /* USAGE:

     Instructs LTC2633 to switch to internal reference mode and allows user to use the DAC with internal refernce voltage

     Accepted format:
     <put name here>.internalReference();

     Example
     myDAC.internalReference()                      //For 'myDAC'
  */

}

void loop()
{
  uint64_t value = random(0, pow(2, resolution));   //generate a random number in range (for testing purposes only)

  myDAC.store(value);
  /* USAGE:

     Stores VALUE to INPUT REGISTER of LTC2633
     Takes 64bit unsigned VALUE (unsigned loong long int) and 8bits (byte) of DAC register address

     Accepted formats:
          <put name here>.store(VALUE);
     <put name here>.store(VALUE, DAC);

     DAC register keywords: DAC0, DAC1, BOTH

     examples:
     myDAC.store(value);                            //Given, 'value' is supplied for 'myDAC', switch to default configuration: DAC = BOTH
     myDAC.store(value, DAC0);                      //For 'myDAC', 'value' must be supplied
  */

  myDAC.update();
  /* USAGE:

     Instructs LTC2633 to transfer its INPUT REGISTER data to DAC register
     Takes 8bits of DAC register address (byte) as input

     Note: Recomended to use after 'value' is '<put name here>.store()' -ed earlier

     Accepted formats:
     <put name here>.update();
     <put name here>.update(DAC);

     DAC register keywords: DAC0, DAC1, BOTH

     examples:
     myDAC.update();                                //Switch 'myDAC' to default configuration: DAC = BOTH
     myDAC.update(DAC0);
  */

  myDAC.write(value);
  /* USAGE:

     Stores 'value' to DAC register of LTC2633
     Takes 64bit unsigned DATA (unsigned loong long int) and 8bits (byte) of DAC register address

     Accepted formats:
     <put name here>.write(VALUE);
     <put name here>.write(VALUE, DAC);

     DAC register keywords: DAC0, DAC1, BOTH

     examples:
     myDAC.write(value);                            //Given, 'value' is supplied for 'myDAC', switch to default configuration: DAC = BOTH
     myDAC.write(value, DAC0);                      //For 'myDAC', 'value' must be supplied
  */

  myDAC.powerDown();
  /* USAGE:

     Instructs LTC2633 to power down its individual DACs
     Takes 8bits of DAC register address (byte) as input

     Accepted formats:
     <put name here>.powerDown();
     <put name here>.powerDown(DAC);

     DAC register keywords: DAC0, DAC1, BOTH

     examples:
     myDAC.powerDown();                              //Switch 'myDAC' to default configuration: DAC = BOTH
     myDAC.powerDown(DAC0);                          //For 'myDAC'
  */

  myDAC.powerOff();
  /* USAGE:

     Instructs LTC2633 to power off completely

     Accepted format:
     <put name here>.powerDown();

     example:
     myDAC.powerOff();                              //For 'myDAC'
  */
}
