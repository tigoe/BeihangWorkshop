#include <Encoder.h>
#include <ColorConverter.h>
int status = 0;
int intensity = 100;
int hue = 0;
int saturation = 0;
// make an instance of the Color converter library
ColorConverter converter;

bool colorStrip = false;
bool timeStrip = false;
Encoder knob(0, 1);
int lastKnobState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  ///////////////////////////////////////////
  // input section

  // read the knob for change
  int knobDirection = readEncoderChange();

  // read the button for change

  //////////////////////////////////////////////////
  ///  Decision section (make decisions based on input)

  // button has 4 possible states

  if (status == 0) {
    // the color strip should be on, so set colorStrip to true:
    colorStrip = true;
    // change the intensity of the non-addressable strip
    intensity = intensity + knobDirection;
    // rollover intensity if it reaches 100:
    intensity = intensity % 100;
  }

  if (status == 1) {
    colorStrip = true;
    timeStrip = true;
    // change the hue of the non-addressable strip

    // apply your logic to set hue and saturation you want based on the knobDirection

  }

  if (status == 2) {
    // non-addressable strip turns off
    colorStrip = false;
  }

  if (status == 3) {
    // both strips off
    colorStrip = false;
    timeStrip = false;
  }

  //////////////////////////////////////////////
  // output section (make changes based on your decisions)

  // time happens no matter what. Put in the code that changes the LEDs based on time here:


  // update your outputs no matter what else you do:
  if (colorStrip == true) {
    // given hue, saturation, intensity, get R, G, B, W
    RGBColor color = converter.HSItoRGBW(hue, saturation, intensity);

    // update all four channels:
    // update the color strip
    analogWrite(2, color.white);
    analogWrite(3, color.red);
    analogWrite(4, color.green);
    analogWrite(5, color.blue);
  } else {
    // turn off all four channels:
    analogWrite(2, 0);
    analogWrite(3, 0);
    analogWrite(4, 0);
    analogWrite(5, 0);
  }

  if (timeStrip == true) {
    // update time strip
  } else {
    // set all the addressable LEDs to 0:
    // strip.clear();
    // updates the strip:
  }
  //strip.show();
}


int readEncoderChange() {
  // returns 0 for no change, -1 for one direction, 1 for the other:
  int result = 0;
  // read the encoder:
  int knobState = knob.read();

  //get the change in the encoder:
  int knobChange = knobState - lastKnobState;

  // if it's changed by 4 or more pulses:
  if (abs(knobChange) >= 1) {
    // You just want direction of change, not value, so
    // divide value by abs. value to get 1 or -1:
    result = knobChange / abs(knobChange);
  }
  // save the current state for comparison next time:
  lastKnobState = knobState;
  return result;
}
