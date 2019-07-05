/*
   Reads a pushbutton to change between four fade curves for an LED.
   Then changes to one of the curves depending on the number of button pushes.

*/
int lastButtonState = 0;    // set the last pushbutton state
int whichTable = 0;         // this variable tells us which property we are changing

int currentLevel = 1;       // current light level
int change = 1;             // change each time you fade
byte cie1931[256];          // pre-calculated PWM levels for CIE1931 curve
byte sineTable[256];        // pre-calculated PWM levels for sine curve
byte exponentialTable[256]; // pre-calculated PWM levels for exponential curve
byte squaredTable[256];     // pre-calculated PWM levels for x squared curve


void setup() {
  // put your setup code here, to run once:
  pinMode(6, INPUT);    // set button input
  pinMode(5, OUTPUT);
  Serial.begin(9600);   // initialize serial communication
  // fill all the curve tables:
  fillCIETable();
  fillExponentialTable();
  fillSineTable();
  fillSquaredTable();
}

void loop() {
  // read the button for any change:
  readButtonChange();
  /////////////////////////////////////////////////////////////////////////////////
  // change what curve is fading based on the button:

  if (whichTable == 0) {
    //PWM output the result:
    analogWrite(5, cie1931[currentLevel]);
    delay(10);
    Serial.println(cie1931[currentLevel]);
  }

  if (whichTable == 1) {
    //PWM output the result:
    analogWrite(5, sineTable[currentLevel]);
    delay(10);
    Serial.println(sineTable[currentLevel]);
  }
  if (whichTable == 2) {
    //PWM output the result:
    analogWrite(5, exponentialTable[currentLevel]);
    delay(10);
    Serial.println(exponentialTable[currentLevel]);
  }
  if (whichTable == 3) {
    //PWM output the result:
    analogWrite(5, squaredTable[currentLevel]);
    delay(10);
    Serial.println(squaredTable[currentLevel]);
  }
  // decrease or increase by 1 point each time
  // if at the bottom or top, change the direction:
  if (currentLevel <= 0 || currentLevel >= 255) {
    change = -change;
  }
  currentLevel += change;
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
      whichTable++;
      // if it reaches 4, reset to 0:
      if (whichTable == 4) {
        whichTable = 0;
      }
      Serial.println(whichTable);
    } else {      // if the button is released:
      Serial.println("released");
    }
  }
  // save the button state for comparison next time:
  lastButtonState = buttonState;
}


void fillCIETable() {
  /*
    For CIE, the following formulas have  Y as luminance, and
    Yn is the luminance of a white reference (basically, max luminance).
    This assumes a perceived lightness value L* between 0 and 100,
    and  a luminance value Y of 0-1.0.
    if L* > 8:  Y = ((L* + 16) / 116)^3 * Yn
    if L* <= 8: Y = L* *903.3 * Yn
  */
  // set the range of values:
  float maxValue = 255;
  // scaling factor to convert from 0-100 to 0-maxValue:
  float scalingFactor = 100 / maxValue;
  // luminance value:
  float Y = 0.0;

  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {
    // you need to scale L from a 0-255 range to a 0-100 range:
    float lScaled = float(l) * scalingFactor;
    if ( lScaled <= 8 ) {
      Y = (lScaled / 903.3);
    } else {
      float foo = (lScaled + 16) / 116.0;
      Y = pow(foo, 3);
    }
    // multiply to get 0-maxValue, and fill in the table:
    cie1931[l] = Y * maxValue;
  }
}


void fillExponentialTable() {
  // Formula and explanation from
  // https://diarmuid.ie/blog/pwm-exponential-led-fading-on-arduino-or-other-platforms

  // set the range of values:
  float maxValue = 255;
  // Calculate the scaling factor based on the
  // number of PWM steps you want:
  float scalingFactor = (maxValue * log10(2)) / (log10(255));

  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {
    int lightLevel = pow(2, (l / scalingFactor)) - 1;
    exponentialTable[l] = lightLevel;
  }
}


void fillSineTable() {
  // set the range of values:
  float maxValue = 255;

  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {

    // map input to a 0-179 range:
    float angle = map(l, 0, maxValue, 0, 179);
    /* here's the explanation of the calulation:
      // convert to radians:
      float result = angle * PI/180;
      // now add PI/2 to offset by 90 degrees:
      result = result + PI/2;
      // get the sine of that:
      result = sin(result);
      // now you have -1 to 1. Add 1 to get 0 to 2:
      result = result + 1;
      // multiply to get 0-255:
      result = result * 127.5;
    */
    //here it all is in one line:
    float lightLevel = (sin((angle * PI / 180) + PI / 2) + 1) * 127.5;
    sineTable[l] = lightLevel;
  }
}


void fillSquaredTable() {
  // set the range of values:
  float maxValue = 255;

  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {
    // square the current value:
    float lightLevel = pow(l, 2);
    // map the result back to a 0-255 range:
    lightLevel = map(lightLevel, 0, 65535, 0, 255);
    squaredTable[l] = lightLevel;
  }
}
