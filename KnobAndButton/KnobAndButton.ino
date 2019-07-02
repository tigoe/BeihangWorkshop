#include <Encoder.h>

// make an instance of the Encoder library, tell it what pins to use:
Encoder knob(0, 1);
int lastKnobPos = 0;
int intensity = 0;
int lastButtonState = 0;
bool blinking = false;
long lastBlinkTime = 0;
int lastLevel = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // tell the Arduino that pin 4 is an output:
  pinMode(4, OUTPUT);
  // tell the Arduino that pin 5 is an input:
  pinMode(5, INPUT);
}

void loop() {
  // button controls whether it's blinking
  int buttonState = digitalRead(5);
  if (buttonState != lastButtonState) {
    delay(3);  // debounce delay)
    if (buttonState == HIGH) {
      // take action
      Serial.println("button is pressed");
      // change the status of the blinking:
      blinking = !blinking;
    }
  }
  // save the button's state so we can compare it to the next button read:
  lastButtonState = buttonState;

  //////////////////////////////////////////////////////////////////////

  // knob controls how bright it is
  // read the knob:
  int knobPos = knob.read();
  // if it's changed, do something:
  if (knobPos != lastKnobPos) {
    // constrain the knob value to a range from 0 to 255:
    intensity = constrain(knobPos, 0, 255);
    // update the knob with the constrained value:
    knob.write(intensity);
    // save knob state for comparison next time:
    lastKnobPos = intensity;
  }

  ////////////////////////////////////////////////////////////////////////
  // if you should be blinking:
  if (blinking) {
    // if enough time has passed since you last changed the LED:
    if (millis() - lastBlinkTime > 250) {
      // if you turned the LED on last time, turn it off, and vice versa:
      if (lastLevel == intensity) {
        lastLevel = 0;
      } else {
        lastLevel = intensity;
      }
      // set the LED to the desired level:
      analogWrite(4, lastLevel);

      Serial.print("LED changes here to:  ");
      Serial.println(lastLevel);
      // save the time that you last changed the LED:
      lastBlinkTime = millis();
    }
  }
}
