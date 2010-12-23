#ifndef DEVICE_H
#define DEVICE_H

// This version used to test the serial library is a
// work in progress and will be brought into process later
// Joe Pardue December 12, 2010

/*****************************************************
//!	Select the AVR type you are using
///		Remove '//' from device you are using
///		Add '//' to devices you are not using
///
///		//#define ATmega644
///		//#define ATmega32
///		//#define ATmega168
///		#define Butterfly
******************************************************/
//#define ATmega644
//#define ATmega32
//#define ATmega168
//#define ARDUINO
//#define BEAVR
#define Butterfly

#if defined (Butterfly)
#include "butterfly.h"
#define BAUD 19200
#else
#define BAUD 57600 //Arduino and BeAVR
#endif 


#endif



