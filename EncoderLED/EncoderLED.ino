/* Encoder LED dimmer
    based on Paul Stoffregen's Encoder Basic example
*/

#include <Encoder.h>
Encoder myEncoder(0, 1);
int lastPosition  = -1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the encoder:
  long encoderPos = myEncoder.read();
  // check to see if it has changed:
  if (encoderPos != lastPosition) {
    // constrain the encoder to a 0-255 range:
    encoderPos = constrain(encoderPos, 0, 255);
    // use the encoder position to set the state of an LED:
    analogWrite(4, encoderPos);
    // print the value to the serial monitor:
    Serial.println(encoderPos);
    // save the current position for comparison next time:
    lastPosition = encoderPos;
  }
}
