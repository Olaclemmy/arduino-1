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

#include "sn3218.h"
#include <Arduino.h>

#ifdef __AVR_ATtiny85__
#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#else
#include <Wire.h>
#endif

sn3218::sn3218(){}

sn3218::sn3218(int _sdaPin,int _sclPin){
	//sn3218::sdaPin=_sdaPin;
	//sn3218::sclPin=_sclPin;
	softWire=new SoftwareWire(_sdaPin,_sclPin);
	}

void sn3218::begin(){
#ifdef __AVR_ATtiny85__
  TinyWireM.begin();
#else
  Wire.begin();
#endif
  this->enable();
}

void sn3218::update(){
  this->writeReg(SN3218_CMD_UPDATE, 0x00);
}

void sn3218::reset(){
  this->writeReg(SN3218_CMD_RESET, 0x00);
  this->enable();
}

void sn3218::enable(){
  this->writeReg(SN3218_CMD_ENABLE_OUTPUT, 0x01);
}

void sn3218::disable(){
  this->writeReg(SN3218_CMD_ENABLE_OUTPUT, 0x00);
}

void sn3218::enable_leds( unsigned long enable_mask ){
  this->writeReg(SN3218_CMD_ENABLE_LEDS, enable_mask & 0x3F);
  this->writeReg(SN3218_CMD_ENABLE_LEDS + 1, (enable_mask >> 6) & 0x3F);
  this->writeReg(SN3218_CMD_ENABLE_LEDS + 2, (enable_mask >> 12) & 0x3F);

  this->update();
}

void sn3218::set( unsigned char chan, unsigned char val ){
  this->writeReg( SN3218_CMD_SET_PWM_VALUES + chan, val );
}

void sn3218::writeReg( unsigned char reg, unsigned char val ){
	if(softWire!=0){
		softWire->beginTransmission(SN3218_ADDR);
		softWire->write(reg);
		softWire->write(val);
  		softWire->endTransmission();
	}else{
#ifdef __AVR_ATtiny85__
  TinyWireM.beginTransmission(SN3218_ADDR);
  TinyWireM.send(reg);
  TinyWireM.send(val);
  TinyWireM.endTransmission();
#else
  Wire.beginTransmission(SN3218_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
#endif
	}
}
