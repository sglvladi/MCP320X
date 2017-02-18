# MCP320X Arduino library
Arduino library to interface with MCP320X family (MCP3201, MCP3202, MCP3204 and MCP3208) 12-bit Analogue-to-Digital Converter chips.<br>
Put together by Lyudmil Vladimirov, Feb 2017

Inspired by the Arduino Playground MCP3208 example. (http://playground.arduino.cc/Code/MCP3208)  

## Using the MCP320X library
* (Optional) Define model and SPI pins
```c++
#define CS_PIN D4     // ESP8266 default SPI pins
#define CLOCK_PIN D5  // Should work with any other GPIO pins, since the library does not formally
#define MOSI_PIN D7   // use SPI, but rather performs pin bit banging to emulate SPI communication.
#define MISO_PIN D6   //

#define MCP3204 4     // (Generally "#define MCP320X X", where X is the last model digit/number of inputs)
````
* Create an instance of MCP320X object.
```c++
MCP320X mcp3204 = MCP320X(MCP3204, CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);
````
* Read from the channel of interest.
````c++
int adc = mcp3204.readADC(0); // Read from channel 0
````
The output should be a number from 0 to 4095, proportional to the range GND to VREF.<br>
If -1 is received instead, it means you have either specified the wrong model number, or an invalid channel for the given model.

## Compatible devices
The library has only been tested on an ESP8266 chip (WeMos D1 mini) with a MCP3204, however should work with all MCP320X models and on any Arduino compatible device.
