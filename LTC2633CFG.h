#ifndef LTC2633CFG_H
#define LTC2633CFG_H


/*LTC2633 I2C Transfer Rate*/
typedef enum
{
  SLOW = 0x0186A0,
  slow = 0x0186A0,
  FAST = 0x061A80,
  fast = 0x061A80
} rate;

/*LTC2633 Resolution*/
typedef enum
{
  VIII = 0x08,
  viii = 0x08,
  X = 0x0A,
  x = 0x0a,
  XII = 0x0C,
  xii = 0x0c
} resolution;

/*LTC2633 Address Configuration*/
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


#endif
