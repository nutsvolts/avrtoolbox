/*****************************************************
	device.h Joe Pardue December 11, 2010
******************************************************/

/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2008, Smiley Micros, All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer. 
 *   
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 *   
 *  - Neither the name of the Smiley Micros nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission. 
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 */

/*****************************************************
	device.h
******************************************************/

#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>
/*****************************************************
	To use this source code you must select the device
	in the #define list AND you must set the processor
	for the device in the Configuration Options
	
	Select the device from the #define list:
	Remove '//' from device you are using
	Add '//' to devices you are not using

	Select the processor from Projects menu item 
	Configuration Options - Device:
	Butterfly - ATmega169
	Arduino - ATmega328
	BeAVR - ATmega644

	You must make both selections for this to compile
	properly in AVRStudio
******************************************************/
#define Butterfly
//#define Arduino
//#define BeAVR40

// Constants used to calculate the register
// settings for each device baudrate
#if defined(Butterfly)
void butterfly_init(void);
void OSCCAL_calibration(void);
void Delay(uint16_t);
#include <avr/interrupt.h>
#define F_CPU 1000000L
#define BAUD 19200
#elif (defined(Arduino) || defined(BeAVR40))
#define F_CPU 16000000L
#define BAUD 57600
#else
   #error "No device F_CPU and BAUD defined."
#endif
// requires F_CPU
#include <util\delay.h>

/*****************************************************
	And you'll want an avrdude script for each:

	avrdude -p m169 -c butterfly -P com4 -b 19200 -F -U flash:w:CylonEyesSPI.hex
	avrdude -p m328p -c arduino -P com3 -b 57600 -F -U flash:w:CylonEyesSPI.hex
	avrdude -p m644p -c avr109 -P com3 -b 57600 -F -U flash:w:CylonEyesSPI.hex
	
	Just remember that in the Command Prompt window to 
	make sure you are in the same directory as hex file 
	and that you have changed the comX port to your port.
	and that you are using the correct baud rate
******************************************************/

#endif
