/*
  @file     LTC2633.ino
  @author   Tamojit Saha (http://github.com/TamojitSaha),
            Sandeepan Sengupta (http://sandeepan.info)

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
  |      | LTFTD   | LTC2633A-HZ12, LTC2633-HZ12 |
  +------+---------+-----------------------------+
  |   10 | LTFTM   | LTC2633-HI10                |
  |      | LTFTK   | LTC2633-HZ10                |
  +------+---------+-----------------------------+
  |    8 | LTFTS   | LTC2633-HI8                 |
  |      | LTFTR   | LTC2633-HZ8                 |
  +------+---------+-----------------------------+

  Version : 0.1.0
  Released under CC-BY-NC-SA 4.0 (https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode)
  All text above, must be included in any redistribution
*/

#include <LTC2633.h>
LTC2633 myDAC;                              /*declare*/

/*
  NOTE #1:  Please follow the keyword table given below
  +--------------+--------------+-----------------------------------------+
  |     Type     |  Variables   |                Constants                |
  +--------------+--------------+-----------------------------------------+
  | I2C Address  | BOX, box     | NC, nc,                                 |
  |              |              | GND, gnd,                               |
  |              |              | VCC, vcc,                               |
  |              |              | ALL, all,                               |
  |              |              | GLOBAL, global,                         |
  |              |              | CUSTOM, custom                          |
  +--------------+--------------+-----------------------------------------+
  | DAC Register | DAC, dac     | DAC0, dac0,                             |
  |              |              | DAC1, dac1,                             |
  |              |              | BOTH, both                              |
  +--------------+--------------+-----------------------------------------+
  | Resolution   | BITS, bits   | VIII, viii,                             |
  |              |              | X, x,                                   |
  |              |              | XII, xii                                |
  +--------------+--------------+-----------------------------------------+
  | Frequency    | RATE, rate   | SLOW, slow,                             |
  |              |              | FAST, fast                              |
  +--------------+--------------+-----------------------------------------+
  | Extras       | DATA, data,  | write_input_reg, update_dac_reg,        |
  |              | VALUE, value | write_update_all, write_update_dac,     |
  |              |              | power_down_dac, power_down_all,         |
  |              |              | internal_reference, external_reference, |
  |              |              | no_operation                            |
  +--------------+--------------+-----------------------------------------+
*/

#define bits xii                            /*Resolution is set here*/

void setup()
{
  myDAC.begin(global, bits, fast);
  /*
    ABOUT : Initialize with Address, Resolution and Frequency

    USAGE : Takes two 8bits (byte) value and a boolean as input

    ACCEPTED FORMATS :
    <put name here>.begin();
    <put name here>.begin(Address);
    <put name here>.begin(Address, Resolution);
    <put name here>.begin(Address, Resolution, Frequency);

    Note #2: Resolution value other than 8, 10 or 12 will be rejected and program will switch to 12 bits resolution setup

    WARNING #2: Even when using values 8, 10 or 12, make sure its according to LTC2633 specification.

    Please verify markings on IC with the following table:

    +------+------------------------------------------+
    | Bits |                 Marking(s)               |
    +------+------------------------------------------+
    |   12 | LTFTC, LTFTB, LTFSZ, LTFTV, LTFTF, LTFTD |
    |   10 | LTFTJ, LTFTH, LTFTG, LTFTW, LTFTM, LTFTK |
    |    8 | LTFTQ, LTFTP, LTFSZ, LTFTN, LTFTS, LTFTR |
    +------+------------------------------------------+

    EXAMPLES:
    myDAC.begin();                         //Switch 'myDAC' to default configuration: Address = GLOBAL, Resolution = 12, Frequency = FAST
    myDAC.begin(VCC);                      //Switch 'myDAC' to default configuration: Resolution = 12, Frequency = HIGH
    myDAC.begin(NC, XII);                  //Given, 'Resolution' value is supplied, Switch 'myDAC' to default configuration: Frequency = FAST
    myDAC.begin(GND, BITS, SLOW);          //'Resolution' value for 'myDAC' must be supplied
 */

  myDAC.externalReference();
   /*
    ABOUT : Instructs LTC2633 to switch to external reference mode and allows user to use the DAC with external reference voltage

    USAGE : It's a void type funcion can be used just by calling it

    ACCEPTED FORMAT:
    <put name here>.externalReference();

    EXAMPLE:
    myDAC.externalReference()              //For 'myDAC'
  */

  /*
    Note #3:  The following parts have POWER-ON REFERANCE MODE set to external reference.

    WARNING #3: Either use external voltage reference IC or remember switching to internal reference mode while using these parts.

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
    ABOUT : Instructs LTC2633 to switch to internal reference mode and allows user to use the DAC with internal reference voltage

    USAGE : It's a void type funcion can be used just by calling it

    ACCEPTED FORMAT:
    <put name here>.internalReference();

    EXAMPLE:
    myDAC.internalReference()              //For 'myDAC'
  */
}

void loop()
{
  uint64_t value = random(0, pow(2, bits)); /*generate a random number in range (for testing purposes only)*/

  myDAC.store(value);
  /*
    ABOUT : Stores value to input register of LTC2633

    USAGE : Takes 64bit unsigned integer (unsigned long long int) and 8bits of DAC register address (byte)

    ACCEPTED FORMATS:
    <put name here>.store(VALUE);
    <put name here>.store(VALUE, DAC);

    EXAMPLES:
    myDAC.store(value);                    //Given, 'value' is supplied, switch 'myDAC' to default configuration: DAC = BOTH
    myDAC.store(value, DAC0);              //For 'myDAC', 'value' must be supplied
  */

  myDAC.update(BOTH);
  /*
    ABOUT : Instructs LTC2633 to transfer its input register data to respective DAC register

    USAGE : Takes 8bits of DAC register address (byte) as input

    Note  : Recommended to use after 'value' is '<put name here>.store()' -ed earlier

    ACCEPTED FORMATS:
    <put name here>.update();
    <put name here>.update(DAC);

    EXAMPLES:
    myDAC.update();                        //Switch 'myDAC' to default configuration: DAC = BOTH
    myDAC.update(DAC0);
  */

  myDAC.write(value, both);
  /*
    ABOUT : Stores 'value' to DAC register of LTC2633

    USAGE : Takes 64bit unsigned DATA (unsigned long long int) and 8bits (byte) of DAC register address

    ACCEPTED FORMATS:
    <put name here>.write(VALUE);
    <put name here>.write(VALUE, DAC);

    EXAMPLES:
    myDAC.write(value);                    //Given, 'value' is supplied, switch 'myDAC' to default configuration: DAC = BOTH
    myDAC.write(value, DAC0);              //For 'myDAC', 'value' must be supplied
  */

  myDAC.powerDown();
  /*
    ABOUT : Instructs LTC2633 to power down its individual DACs

    USAGE : Takes 8bits of DAC register address (byte) as input

    ACCEPTED FORMATS:
    <put name here>.powerDown();
    <put name here>.powerDown(DAC);

    EXAMPLES:
    myDAC.powerDown();                     //Switch 'myDAC' to default configuration: DAC = BOTH
    myDAC.powerDown(DAC0);                 //For 'myDAC'
  */

  myDAC.powerOff();
  /*
    ABOUT : Instructs LTC2633 to power off completely

    USAGE : It's a void type funcion can be used just by calling it

    ACCEPTED FORMAT:
    <put name here>.powerDown();

    EXAMPLE:
    myDAC.powerOff();                      //For 'myDAC'
  */
}
