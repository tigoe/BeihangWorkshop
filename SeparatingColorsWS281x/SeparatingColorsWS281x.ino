/*
  Shows how to separate colors from a single color variable
*/
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
  // pick a random color:
  long randomColor = random(4000000000);
  // loop over all the pixels:
  for (int pixel = 0; pixel < pixelCount; pixel++) {
    strip.setPixelColor(pixel, randomColor); // set the color for this pixel
  }
  // get the color of pixel 0 as a long integer:
  long thisColor = strip.getPixelColor(0);
  // print it:
  Serial.println(thisColor, HEX);

  // now separate the colors into four separate variables:
  // white is the top byte of thisColor. Shift right by 3 bytes (24 bits)
  // to eliminate the other three bytes:
  byte white = thisColor >> 24;        
  // red is the second byte. Shift right by 2 bytes (16 bits)
  // then take the lowest byte of the result:
  byte red = lowByte(thisColor >> 16);  
   // green is the third byte. Shift right by 1 byte (8 bits)
  // then take the lowest byte of the result:
  byte green = lowByte(thisColor >> 8);
  // blue is the lowest byte of thisColor:
  byte blue = lowByte(thisColor);

  // print them out
  Serial.print(white, HEX);
  Serial.print("\t");
  Serial.print(red, HEX);
  Serial.print("\t");
  Serial.print(green, HEX);
  Serial.print("\t");
  Serial.println(blue, HEX);

  strip.show();    // refresh the strip
  delay(1000);
}
