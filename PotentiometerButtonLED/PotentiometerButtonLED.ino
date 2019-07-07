/*
  Turns on an LED to a level set by a potentiometer
  when a pushbutton is pressed. On alternate presses,
  it turns the LED off.
 */
int lastButtonState = 0;
bool lightOn = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
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
      // change the status of the light:
      lightOn = !lightOn;
    }
  }
  // save the button's state so we can compare it to the next button read:
  lastButtonState = buttonState;

  //////////////////////////////////////////////////////////////////////

  // read the potentiometer knob attached to pin A0:
  int knobValue = analogRead(A0);
  // divide by 4 to get 0-255 range:
  int intensity = knobValue / 4;
  
  //////////////////////////////////////////////////////////////////////
  // if the light should be on, turn it on;
  // if not, turn it off:
  if (lightOn) {
    analogWrite(4, intensity);
  } else {
    analogWrite(4, 0);
  }
}
