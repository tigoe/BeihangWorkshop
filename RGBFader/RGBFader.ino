/*
  This example controls four separate channnels of an RGBW 
  LED strip, one channel at a time. Each channel will fade up, 
  then fade out, then the next channel will start. 
  
 */

int intensity = 0;      // the intensity of the light channel
int change = 1;         // the amount of change in intensity
long lastFadeTime = 0;  // the last time you made a fade step
int color = 0;          // the color of the light channel you are changing

void setup() {
  // put your setup code here, to run once:
  // initialize pins 2 through 5 as outputs:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // if 10 milliseconds have passed since the last change:
  if (millis() - lastFadeTime > 10) {
    // change the intensity:
    intensity = intensity + change;
    // if the intensity is at full or at 0:
    if (intensity == 0 || intensity == 255) {
      // reverse the direction of the change:
      change = -change;
    }
    // if the intensity is at 0, switch to the next channel:
    if (intensity == 0) {
      // if you are on pin 5, go back to 2:
      if (color == 5) {
        color = 2;
        // otherwise, add one to the channel number
      } else {
        color++;
      }
    }
    // update the channel and print the current intensity:
    analogWrite(color, intensity);
    Serial.println(intensity);
    // save the current time for comparison next time:
    lastFadeTime = millis();
  }
}
