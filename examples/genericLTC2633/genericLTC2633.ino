/*
  @file     genericLTC2633.ino
  @author   Sandeepan Sengupta (http://sandeepan.info),
              Tamojit Saha(http://tamojitsaha.info)

  Arduino demonstration file for miniDAC module
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
#define __resolution 12 //demo only

LTC2633 myDAC;                  /*declare*/

/*
  NOTE #1:  Please find the custom datatype used in this library in table given below
  +-------------+--------------------------------+---------------+
  |  Data Type  |              Values            |  Description  |
  +-------------+--------------------------------+---------------+
  |             | FAST, fast,                    |    Set        |
  |  rate       | SLOW, slow,                    |  I2C Speed    |
  +-------------+--------------------------------+---------------+
  |             | VIII, viii, eight, EIGHT       |     Set       |
  |  resolution | X, x, ten, TEN                 |     DAC       |
  |             | XII, xii, twelve, TWELVE       |   Resolution  |
  +-------------+--------------------------------+---------------+
  |             | NC, nc,                        |               |
  |             | GND, gnd,                      |               |
  |  address    | VCC, vcc,                      | Select DAC    |
  |             | ALL, all,                      | address (I2C) |
  |             | GLOBAL, global                 |               |
  +-------------+--------------------------------+---------------+
  |configuration| various                        |  Structure    |
  +-------------+--------------------------------+---------------+
  
  NOTE #2:  The members(s) of the structure of "configuration" data type
  with coresponding member data type(s) described below
  
  +---------------+------------+--------------+
  |   Structure   | Member(s)  | Data Type(s) |
  +---------------+------------+--------------+
  |               | Rate       | rate         |
  | configuration | Address    | address      |
  |               | Resolution | resolution   |
  +---------------+------------+--------------+

  NOTE #3:  Please follow the keyword table given below
  +#######################################################################+
  +--------------+--------------+-----------------------------------------+
  |              |              | write_input_reg, update_dac_reg,        |
  |              | DATA, data,  | write_update_all, write_update_dac,     |
  | Extras       | VALUE, value | power_down_dac, power_down_all,         |
  |              |(free for use)| internal_reference, external_reference, |
  |              |              | no_operation                            |
  +--------------+--------------+-----------------------------------------+
*/

void setup()
{
  myDAC.configure();
  /*
    ABOUT : Confiure I2C transfer rate, DAC address and DAC resolution

    USAGE : Takes structure of data (data type: "configuration") having members:
              I2C transfer rate as input(s) (Data Type: "rate")
              and
              8bits of I2C Address (Data Type: "address")
              and
              DAC resolution in bit(s) (Data Type: "resolution")

    ACCEPTED FORMATS :
    <put name here>.configure();
    <put name here>.configure(Configuration);
      GIVEN :
      configuration Configuration = {slow};
      configuration Configuration = {.Rate = slow};
      configuration Configuration = {slow, global};
      configuration Configuration = {.Rate = slow, .Address = global};
      configuration Configuration = {slow, global, XII};
      configuration Configuration = {.Rate = slow, .Address = global, .Resolution = XII};

    EXAMPLES:
    myDAC.configure();
    //Switch 'myDAC' to default configuration:
      //Address = GLOBAL (0x73)
      //Resolution = XII (0x0C)
      //Rate = slow (0x0186A0)

    myDAC.configure({slow});
    //Switch 'myDAC' to given configuration:
      //Rate = slow (0x0186A0)

    myDAC.configure({.Address = VCC, .Resolution = XII});
    //Switch 'myDAC' to given configuration:
      //Address = VCC (0x12),
      //Resolution = XII (0x0C)

    myDAC.configure({slow, VCC, XII});
    //Switch 'myDAC' to given configuration:
      //Rate = slow (0x0186A0),
      //Address = VCC (0x12),
      //Resolution = XII (0x0C)

    configuration Configuration = {.Rate = slow, .Address = global, .Resolution = XII};
    myDAC.configure(Configuration);
    //Switch 'myDAC' to given configuration:
      //Rate = slow (0x0186A0),
      //Address = VCC (0x12),
      //Resolution = XII (0x0C)
  */

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

    Note #4: Unless changed by calling function with proper resolution(Keyword) listed below, system initializes to 12 bits resolution setup.

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
    Note #5:  The following parts have POWER-ON REFERANCE MODE set to external reference.

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

    Note #6 : Recommended to use after 'value' is '<put name here>.store()' -ed earlier

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
