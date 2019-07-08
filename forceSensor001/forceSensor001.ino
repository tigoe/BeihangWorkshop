/*
  Press a force sensor, turn on multiple LEDs one at a time
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

}

void loop() {
  // put your main code here, to run repeatedly:
  // read the sensor:
  int forceSensor = analogRead(A0);
  
  // map its range to 24 pixels:
  int ledCount = forceSensor / 25;
  Serial.println(ledCount);
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
