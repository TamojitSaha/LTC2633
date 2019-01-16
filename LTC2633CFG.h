/*
    @file     LTC2633CFG.h
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


    ************************************************
    About LTC2633CFG.h
    ************************************************
    This file contains custom data types for LTC®2633 miniDAC library.

    Data types are described in the following table:

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
    |            | DAC0, dac0,                    |               |
    |    DAC     | DAC1, dac1,                    |   Select DAC  |
    |            | BOTH, both                     |               |
    +------------+--------------------------------+---------------+
    |            | NC, nc,                        |               |
    |            | GND, gnd,                      |               |
    |  address   | VCC, vcc,                      | Select DAC    |
    |            | ALL, all,                      | address (I2C) |
    |            | GLOBAL, global                 |               |
    +------------+--------------------------------+---------------+

    Version: 1.0.0
    Released under CC-BY-NC-SA 4.0 (https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode)
    All text above, must be included in any redistribution
*/

#ifndef LTC2633CFG_H
#define LTC2633CFG_H


/*Address Codes*/
typedef enum
{
  DAC0 = 0x00,
  dac0 = 0x00,
  DAC1 = 0x01,
  dac1 = 0x01,
  BOTH = 0x0F,
  both = 0x0f
} DAC;

/*LTC®2633 I2C Transfer Rate*/
typedef enum
{
  SLOW = 0x0186A0,
  slow = 0x0186A0,
  FAST = 0x061A80,
  fast = 0x061A80
} rate;

/*LTC®2633 Address Configuration*/
typedef enum
{
  GND = 0x10,
  gnd = 0x10,
  NC =  0x11,
  nc =  0x11,
  VCC = 0x12,
  vcc = 0x12,
  ALL = 0x73,
  all = 0x73,
  GLOBAL = 0x73,
  global = 0x73
           /*
             Reserved for custom address
             CUSTOM = 0xff,
             custom = 0xff
           */
} address;

/*LTC®2633 Resolution*/
typedef enum
{
  VIII = 0x08,
  viii = 0x08,
  eight = 0x08,
  EIGHT = 0x08,
  X = 0x0A,
  x = 0x0a,
  ten = 0x0a,
  TEN = 0x0a,
  XII = 0x0C,
  xii = 0x0c,
  twelve = 0x0c,
  TWELVE = 0x0c
} resolution;

/*LTC®2633 Configuration Structure*/
typedef struct
{
  rate Rate;
  address Address;
  resolution Resolution;
} configuration;

#endif
