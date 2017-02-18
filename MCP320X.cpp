/*
  MCP320X.h - Library for interfacing with MCP320X series 12-bit ADC chips.
  Created by Lyudmil Vladimirov, Feb 2017
  
  Inspired by the Arduino Playground MCP3208 example. (http://playground.arduino.cc/Code/MCP3208)
*/

#include "MCP320X.h"

/* MCP320X() =================================================================================>
*	Constructor function.
*	Parameters:
*		* model: 	The 'X' part of the model identifier (i.e. MCP3204 -> model=4)
*		* clockpin: 	The SPI clock pin (CSK) of your choise.
*		* mosipin:	The SPI MOSI pin of your choice.
*		* misopin:	The SPI MISO pin of your choice.
*		* cspin:	The SPI CS pin of your choice.
* ============================================================================================> */
MCP320X::MCP320X(uint8_t model, uint8_t clockpin, uint8_t mosipin, uint8_t misopin, uint8_t cspin) {
    
    // define SPI outputs and inputs for bitbanging
    _pinNo = model; // the model id (X) defines the number of adc inputs
    _cspin = cspin;
    _clockpin = clockpin;
    _mosipin = mosipin;
    _misopin = misopin;
    
    pinMode(_cspin, OUTPUT);
    pinMode(_clockpin, OUTPUT);
    pinMode(_mosipin, OUTPUT);
    pinMode(_misopin, INPUT);
    
}


/* ~MCP320X() ================================================================================>
*	Destructor function
* ============================================================================================> */
MCP320X::~MCP320X(){}


/* readADC() =================================================================================>
*	Function to read from a channel.
*	Parameters:
*		* channel: The channel number to read from (MAX=_pinNo-1)
*	Returns:
*		* The ADC value of a given channel (0-VREF -> 0-4095), if a valid channel is given.
*		* -1 if the channel id is less than 0 or exceeds the pin number for the defined model.
* ============================================================================================> */
int16_t MCP320X::readADC(uint8_t channel)
{
	// If an invalid channel is passed, return -1
	if ((channel >= _pinNo) || (channel < 0)) return -1; 
	
	int adcvalue = 0;
	uint8_t cmd = B11000000; //command bits - start, mode, chn (3), dont care (3)

	// allow channel selection
	cmd|=((channel)<<3);

	digitalWrite(_cspin, LOW); //Select adc
	// setup bits to be written
	for (int i=7; i>=3; i--){
		digitalWrite(_mosipin, cmd & 1<<i);
		//cycle clock
		digitalWrite(_clockpin, HIGH);
		digitalWrite(_clockpin, LOW);    
	}

	digitalWrite(_clockpin, HIGH);    //ignores 2 null bits
	digitalWrite(_clockpin, LOW);
	digitalWrite(_clockpin, HIGH);  
	digitalWrite(_clockpin, LOW);

	// read bits from adc
	for (int i=11; i>=0; i--){
		adcvalue+=digitalRead(_misopin)<<i;
		//cycle clock
		digitalWrite(_clockpin, HIGH);
		digitalWrite(_clockpin, LOW);
	}
	digitalWrite(_cspin, HIGH); //turn off device
	
	// return the result
	return adcvalue;
}


