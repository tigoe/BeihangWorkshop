
#include <Adafruit_NeoPixel.h>

const int neoPixelPin = 4;  // control pin
const int pixelCount = 8;    // number of pixels

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRBW + NEO_KHZ800);

void setup() {
  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // refresh strip
}

void loop() {
  // loop over all the pixels:
  int knob = analogRead(A0);  // read the potentiometer
  int red = knob / 4;         // red = the position of the potentiometer
  int blue = 255 - (knob / 4);// blue = the inverse of the position of the potentiometer
  int green = 0;              // white and green are zero
  int white = 0;
  // set the color on the strip:
  for (int pixel = 0; pixel < pixelCount; pixel++) {
    strip.setPixelColor(pixel, red, green, blue, white); // set the color for this pixel
  }
  strip.show();    // refresh the strip
}
