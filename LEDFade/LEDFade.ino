/*
  LED continual fade with millis() delay method

*/
int intensity = 0;    // intensity of the LED
int lastFadeTime = 0; // last time the LED faded
int change = 1;       // amount of change for the LED

void setup() {
  // make the LED an output:
  pinMode(4, OUTPUT);
}

void loop() {
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
