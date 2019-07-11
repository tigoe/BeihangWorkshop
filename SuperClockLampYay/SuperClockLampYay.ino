void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // read the knob for change

  // read the button for change

  // button has 4 possible states

  // time happens no matter what

  if (status == 0) {
    // change the intensity of the non-addressable strip
    changeIntensity();
  }

  if (status == 1) {
    // change the hue of the non-addressable strip
    changeHue();
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

  // update your outputs no matter what else you do:
  if (colorStrip == true) {
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
    strip.clear();
    // updates the strip:
  }
  strip.show();
}
