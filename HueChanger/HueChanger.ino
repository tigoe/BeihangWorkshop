/*
  Hue, Saturation, Value fader

   This sketch change the hue of an RGBW LED or strip of LEDS with a rotary encoder

   created 2 July 2019
   by Tom Igoe
*/

#include <ColorConverter.h>
#include <Encoder.h>

ColorConverter converter; // make an instance of the ColorConverter library
Encoder knob(0, 1);       // make an instance of the Encoder library, using pins 0 and 1

const int redPin = 2;
const int greenPin = 3;
const int bluePin = 4;
const int whitePin = 5;

int lastKnobPos = 0;      // last read position of the knob

// make variables for hue, saturation, and intensity:
int hue = 0;
int saturation = 100;
int intensity = 100;

void setup() {
  Serial.begin(9600);       // initialize serial communication
  // make all the LED control pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(whitePin, OUTPUT);
}

void loop() {
  // knob controls the hue
  // read the knob:
  int knobPos = knob.read();
  // if it's changed, do something:
  if (knobPos != lastKnobPos) {
    // constrain the knob value to a range from 0 to 255:
    hue = constrain(knobPos, 0, 360);
    // update the knob with the constrained value:
    knob.write(hue);
    // save knob state for comparison next time:
    lastKnobPos = hue;
  }

  // convert hue, saturation, intensity to red, green, blue, white:
  RGBColor color = converter.HSItoRGBW(hue, saturation, intensity);
  // update the LEDs:
  analogWrite(redPin, color.red);
  analogWrite(greenPin, color.green);
  analogWrite(bluePin, color.blue);
  analogWrite(whitePin, color.white);
}
