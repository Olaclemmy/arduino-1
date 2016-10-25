/*
  A library for the sn3218 18 channel LED driver
  Original version2014/10/06 - Pimoroni Ltd.  http://www.pimoroni.com

  Modified 11/11/2015 by Egor Kraev to allow the option of using the SoftwareWire library

  Usage:
    Make sure to include <Wire.h> or <USI_TWI_Master.h> and <TinyWireM.h> as appropriate.
    Make sure to include <SoftwareWire.h> if you want to control the sn3218 through arbitrary pins

    sn3218() // call constructor without arguments to use the hardware I2C

    sn3218(2, 3) // call construnctor with sda_pin and scl_pin args to use software I2C with those pins

	sn3218.begin();

	sn3218.enable_leds(SN3218_CH_00 + SN3218_CH_01); // Enable channel 0 and 1

	sn3218.set(0, 50); // Set channel 0 to 50/255

	sn3218.update();   // Signal the sn3218 to update outputs from its input registers

  This library is free software; you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation; either version 3 of the License, or any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
  PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/


#ifndef _SN3218_H
#define _SN3218_H

#define SN3218_ADDR 0x54

#define SN3218_NUM_CHANNELS 18

#define SN3218_CMD_ENABLE_OUTPUT 0x00
#define SN3218_CMD_SET_PWM_VALUES 0x01
#define SN3218_CMD_ENABLE_LEDS 0x13
#define SN3218_CMD_UPDATE 0x16
#define SN3218_CMD_RESET 0x17

#define SN3218_CH_ALL 0x3FFFF
#define SN3218_CH_00 0x00001
#define SN3218_CH_01 0x00002
#define SN3218_CH_02 0x00004
#define SN3218_CH_03 0x00008
#define SN3218_CH_04 0x00010
#define SN3218_CH_05 0x00020
#define SN3218_CH_06 0x00040
#define SN3218_CH_07 0x00080
#define SN3218_CH_08 0x00100
#define SN3218_CH_09 0x00200
#define SN3218_CH_10 0x00400
#define SN3218_CH_11 0x00800
#define SN3218_CH_12 0x01000
#define SN3218_CH_13 0x02000
#define SN3218_CH_14 0x04000
#define SN3218_CH_15 0x08000
#define SN3218_CH_16 0x10000
#define SN3218_CH_17 0x20000

#include <SoftwareWire.h>

class sn3218
{
  public:
  	//int sdaPin; // these should really be const
  	//int sclPin; // these should really be const
  	sn3218(int _sdaPin,int _sclPin);
  	sn3218();
    void begin();
    void update();
    void enable();
    void enable_leds( unsigned long enable_mask );
    void disable();
    void reset();
    void set( unsigned char chan, unsigned char val );
 private:
    void writeReg( unsigned char reg, unsigned char val );
    SoftwareWire* softWire=0;

};

//namespace { _sn3218 sn3218; }

#endif
