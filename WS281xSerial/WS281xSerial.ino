/*
  Reads serial input to turn on LEDs in a WS281x addressable LED string
  Use with the ProcessingSerialWrite example.
*/
#include <Adafruit_NeoPixel.h>

const int neoPixelPin = 0;  // control pin
const int pixelCount = 24;    // number of pixels

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRBW + NEO_KHZ800);

long int color = 0x502AFF5F;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // update strip
  Serial.setTimeout(10);
}

void loop() {
  int ledCount = 0;
  // put your main code here, to run repeatedly:
  // listen for serial input:
  if (Serial.available() > 0) {
    ledCount = Serial.parseInt();
    // constrain the output to the number of LEDS:
    ledCount = constrain(ledCount, 0, pixelCount);
  }
  // map its range to 24 pixels:
  // if the number of LEDs to turn on > 0,
  // then turn on ledCount leds:
  if (ledCount > 0) {
    for (int p = 0; p < ledCount; p++) {
      strip.setPixelColor(p, color);
      strip.show();
      delay(1);
    }
    // if ledCount is 0, turn off ALL the LEDS:
  } else {
    for (int p = pixelCount; p >= 0; p--) {
      strip.setPixelColor(p, 0);
      strip.show();
      delay(3);
    }
  }
}
