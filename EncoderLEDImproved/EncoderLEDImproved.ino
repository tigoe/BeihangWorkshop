/* Encoder LED dimmer
    based on Paul Stoffregen's Encoder Basic example
    Improved version: updates the encoder's value so that
    it remains in the 0-255 range.
*/

#include <Encoder.h>

// initialize the encoder on pins 0 and 1:
Encoder myEncoder(0, 1);
// set the last position at -1:
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
    // write the new value back to the encoder, so that
    // the reading never goes out of range:
    myEncoder.write(encoderPos);
    // use the encoder position to set the state of an LED:
    analogWrite(4, encoderPos);
    // print the value to the serial monitor:
    Serial.print(lastPosition);
    Serial.print("   ");
    Serial.println(encoderPos);
    // save the current position for comparison next time:
    lastPosition = encoderPos;
  }
}
