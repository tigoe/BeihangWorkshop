/*
  LED continual fade with millis() delay method
  pushbutton on pin 5 turns fading on or off:

*/
int intensity = 0;    // intensity of the LED
int lastFadeTime = 0; // last time the LED faded
int change = 1;       // amount of change for the LED
int lastButtonState = 0;  // previous state of the pushbutton
bool fading = true;   // whether or not the LED should be fading

void setup() {
  // make the LED an output:
  pinMode(4, OUTPUT);
  // make the button an input:
  pinMode(5, INPUT);
}

void loop() {
  // read the pushbutton:
  int buttonState = digitalRead(5);
  // if the button state has changed:
  if (buttonState != lastButtonState) {
    // debounce delay:
    delay(3);
    // if the button is pressed:
    if (buttonState == HIGH) {
      // change fading flag to its opposite:
      fading = !fading;
    }
  }
  // save button state for comparison next time:
  lastButtonState = buttonState;

  // if fading is false:
  if (fading == false) {
    // turn off LED:
    analogWrite(4, 0);
  } else {
    // if fading is true, make the fade happen:
    // if 10 milliseconds have elapsed:
    if (millis() - lastFadeTime > 10) {
      // add the change to the intensity:
      intensity = intensity + change;
      // if the intensity is at a limit, reverse the
      // direction of the change:
      if (intensity == 0 || intensity == 255) {
        change = -change;
      }
      // output current intensity to the LED:
      analogWrite(4, intensity);
      // save the current time for comparison next loop:
      lastFadeTime = millis();
    }
  }
}
