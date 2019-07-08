/*
  Example of how to use the realtime clock
  The current second shows up white, and all the pixels fade through the color wheel
  once per second
*/
#include <RTCZero.h>
#include <Adafruit_NeoPixel.h>

const int neoPixelPin = 0;  // control pin
const int pixelCount = 60;    // number of pixels

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRBW + NEO_KHZ800);

RTCZero rtc;
int hours = 0;
int minutes = 0;
int seconds = 0;
int lastSecond = 0;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);
  strip.begin();
  strip.clear();
  strip.show();
}

void loop() {
  // listen for serial input to set the time:
  readTimeString();
  // get current second
  int thisSecond = rtc.getSeconds();

  // if the second has changed, change the corresponding pixel:
  if (thisSecond != lastSecond) {
    strip.setPixelColor(thisSecond, 0x98341200);  // a warm-ish white
    strip.setPixelColor(lastSecond, 0);           // turn off previous second's pixel
    lastSecond = thisSecond;
    Serial.println(thisSecond);
  }

  // loop over all the pixels, setting the hue using the current second:T
  for (int p = 0; p < pixelCount; p++) {
    // set hue according to color wheel and seconds
    unsigned int hue = map(thisSecond, 0, 60, 0, 65535);
    // get RGB from HSV:
    unsigned long color = strip.ColorHSV(hue, 255, 127);
    // do a gamma correction:
    unsigned long correctedColor = strip.gamma32(color);
    // the current second should be white, so don't set it:
    if (p != thisSecond) {
      strip.setPixelColor(p, correctedColor);   // set the color for this pixel
    }

  }
  // update the strip:
  strip.show();
}

// looks for a numeric string like this:  hh:mm:ss
// uses hh to set hours, mm to set minutes, and ss to set seconds

void readTimeString() {
  // if there is any incoming serial data:
  if (Serial.available() > 0) {
    // listen for hh:mm:ss:
    hours = Serial.parseInt();
    minutes = Serial.parseInt();
    seconds = Serial.parseInt();
    // set the time from the serial input string:
    rtc.setTime(hours, minutes, seconds);
    // print it:
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.println(seconds);
    Serial.print(":");
  }

}
