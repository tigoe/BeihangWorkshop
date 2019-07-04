
/*
   State change detection
*/
#include <Encoder.h>      // include the encoder library
Encoder myEncoder(0, 1);  // set the pin numbers for the encoder
int lastKnobState = 0;    // set the last knob state

int lastButtonState = 0;  // set the last pushbutton state
int whichProperty = 0;    // this variable tells us which property we are changing

// these are our three properties that will change:
int hue, saturation, intensity;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, INPUT);    // set button input
  Serial.begin(9600);   // initialize serial communication
}

void loop() {
  readButtonChange();
  /////////////////////////////////////////////////////////////////////

  // read the encoder:
  int encoderChange = readEncoderChange();

  /////////////////////////////////////////////////////////////////////////////////
  // change what property the knob controls based on the button:
  if (whichProperty == 0) {
    // change the hue
    hue = hue + encoderChange;
  }

  if (whichProperty == 1) {
    // change the saturation
    saturation = saturation + encoderChange;
  }
  if (whichProperty == 2) {
    // change the intensity
    intensity = intensity + encoderChange;
  }
  Serial.print("hue: ");
  Serial.print(hue);
  Serial.print("\tsaturation: ");
  Serial.print(saturation);
  Serial.print("\tintensity: ");
  Serial.println(intensity);
}

void readButtonChange() {
  // put your main code here, to run repeatedly:
  // read tbe button
  int buttonState = digitalRead(6);
  // if buttonState changes from 0 to 1, blink the LED
  if (buttonState != lastButtonState) {
    delay(5);  // debounce delay 5 ms
    if (buttonState == HIGH) {  // if the button is pressed:
      Serial.println("pressed");
      whichProperty++;
      // if it reaches 3, reset to 0:
      if (whichProperty == 3) {
        whichProperty = 0;
      }
      Serial.println(whichProperty);
    } else {      // if the button is released:
      Serial.println("released");
    }
  }
  // save the button state for comparison next time:
  lastButtonState = buttonState;
}

int readEncoderChange() {
  // returns 0 for no change, -1 for one direction, 1 for the other:
  int result = 0;
  // read the encoder:
  int knobState = myEncoder.read();
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
