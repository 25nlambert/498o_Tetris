/* ----------------------------------------------------------------------
Once the RGB matrix is initialized, most functions of the Adafruit_GFX
library are available for drawing -- code from other projects that use
LCDs or OLEDs can be easily adapted, or may be insightful for reference.
GFX library is documented here:
https://learn.adafruit.com/adafruit-gfx-graphics-library
------------------------------------------------------------------------- */

#include <Adafruit_Protomatter.h>

//ARDUINO_ADAFRUIT_MATRIXPORTAL_ESP32S3 MatrixPortal ESP32-S3
uint8_t rgbPins[]  = {42, 41, 40, 38, 39, 37};
uint8_t addrPins[] = {45, 36, 48, 35, 21};
uint8_t clockPin   = 2;
uint8_t latchPin   = 47;
uint8_t oePin      = 14;

uint8_t x          = 0;
uint8_t y          = 0;

uint16_t colors[8];

Adafruit_Protomatter matrix(
  32,          // Width of matrix (or matrix chain) in pixels
  6,           // Bit depth, 1-6
  1, rgbPins,  // # of matrix chains, array of 6 RGB pins for each
  3, addrPins, // # of address pins (height is inferred), array of pins
  clockPin, latchPin, oePin, // Other matrix control pins
  false);      // No double-buffering here (see "doublebuffer" example)

// SETUP - RUNS ONCE AT PROGRAM START --------------------------------------

void setup(void) {
  Serial.begin(9600);

  // Initialize matrix...
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if(status != PROTOMATTER_OK) {
    // DO NOT CONTINUE if matrix setup encountered an error.
    for(;;);
  }

  matrix.fillScreen(0); // Fill background black
  matrix.show(); // Copy data to matrix buffers

  colors[0] = matrix.color565(64, 64, 64);  // Dark Gray
  colors[1] = matrix.color565(120, 79, 23); // Brown
  colors[2] = matrix.color565(228,  3,  3); // Red
  colors[3] = matrix.color565(255,140,  0); // Orange
  colors[4] = matrix.color565(255,237,  0); // Yellow
  colors[5] = matrix.color565(  0,128, 38); // Green
  colors[6] = matrix.color565(  0, 77,255); // Blue
  colors[7] = matrix.color565(117,  7,135); // Purple

  
}

void loop(void) {
  // Since there's nothing more to be drawn, this loop() function just
  // shows the approximate refresh rate of the matrix at current settings.

  uint16_t printColor = colors[(x%8)];

  matrix.drawPixel(x, y, printColor);
  matrix.show(); // Copy data to matrix buffers
  delay(10);

  if(32 >= x){

    x++;

  } else {

    x = 0;

  }

  if((x == 32)){

    y++;

  } else if(y == 16) {

    y = 0;
    matrix.fillScreen(0); // Fill background black
    matrix.show(); // Copy data to matrix buffers

  }

}

