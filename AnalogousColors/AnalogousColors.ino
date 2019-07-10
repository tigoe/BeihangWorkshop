/*
  Shows how to separate colors from a single color variable
*/
#include <Adafruit_NeoPixel.h>
#include <ColorConverter.h>

const int neoPixelPin = 4;  // control pin
const int pixelCount = 20;    // number of pixels

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRBW + NEO_KHZ800);

ColorConverter converter;

// pick a set of analogous colors from https://color.adobe.com/ :
long colorArray[] = {0x7B54FF, 0x5294FF, 0x5EFCFF, 0x4AE885, 0x8CFF52};

void setup() {
  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // refresh strip
}

void loop() {
  // loop over all the pixels:
  for (int pixel = 0; pixel < pixelCount; pixel++) {
    // you've got five colors and 20 pixels. divide to
    //determine which pixel gets which color:
    strip.setPixelColor(pixel, colorArray[pixel / 4]); // set the color for this pixel
    long thisColor = strip.getPixelColor(pixel);
  }

  strip.show();    // refresh the strip
}
