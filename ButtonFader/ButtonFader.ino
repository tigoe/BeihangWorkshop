/*
  fades an LED up while you hold a button down.
*/
int intensity = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
}

void loop() {
  // button controls whether it's blinking
  int buttonState = digitalRead(5);
  if (buttonState == HIGH) {
    // increase the intensity:
    intensity++;
    // if it reaches 255, rollover to 0:
    intensity = intensity % 255;
    // delay so the user can see the change:
    delay(30);
    }

  //////////////////////////////////////////////////////////////////////
  // set the LED state:
  analogWrite(4, intensity);

}
