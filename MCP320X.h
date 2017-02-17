/*
  MCP320X.h - Library for interfacing with MCP320X series 12-bit ADC chips.
  Created by Lyudmil Vladimirov, Feb 2017
  
  Inspired by the Arduino Playground MCP3208 example. (http://playground.arduino.cc/Code/MCP3208)  
*/

#ifndef MCP320X_h
#define MCP320X_h

#include "Arduino.h"
#include "SPI.h"

/* MCP320X Class * ===========================================================================> 
*  See MCP320X.cpp for more details
* ============================================================================================> */	
class MCP320X
{
	public:
		MCP320X(uint8_t model, uint8_t clockpin, uint8_t mosipin, uint8_t misopin, uint8_t cspin);
		~MCP320X();
		uint16_t readChannel(uint8_t ch);
		
	private:
		  uint8_t _pinNo, _clockpin, _mosipin, _misopin, _cspin;
};


#endif 
