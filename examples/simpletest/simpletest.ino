#include "MCP320X.h"

// (Optional) Define model and SPI pins
#define CS_PIN D4     // ESP8266 default SPI pins
#define CLOCK_PIN D5  // Should work with any other GPIO pins, since the library does not formally
#define MOSI_PIN D7   // use SPI, but rather performs pin bit banging to emulate SPI communication.
#define MISO_PIN D6   //
#define MCP3204 4     // (Generally "#define MCP320X X", where X is the last model digit/number of inputs)

// Create an instance of MCP320X object.
MCP320X mcp3204(MCP3204, CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);

void setup() {
  // Start the serial so we can see some output
  Serial.begin(9600);
}

void loop() {

  // Read from all available pins
  Serial.printf("\nReading from all %i pins of the MCP320X device:\n", MCP3204);
  Serial.println("==================================================>");
  for(int i=0; i<MCP3204; i++){
    Serial.printf("ADC%i: %i\n", i, mcp3204.readADC(i));
  }
  delay(2000);
  
}
