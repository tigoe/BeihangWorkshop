/*
  output test
  Lets you test any pin as an output. Type a number in the serial monitor
  and this sketch will turn on the corresponding pin, from 0 to 21. Pins
  A0 - A6 are 15 - 21.
*/

int lastPin = 21;  // the last pin turned on, so you can turn it off

void setup() {
  // initialize serial and set a 10 ms timeout for parsing strings:
  Serial.begin(9600);
  Serial.setTimeout(10);

  // set pins 0 through 21 as outputs:
  for (int p = 0; p < 22; p++) {
    pinMode(p, OUTPUT);
  }
}

void loop() {
  // if there is any incoming serial data:
  if (Serial.available() > 0)  {
    // parse it, looking for a number:
    int pin = Serial.parseInt();
    // print what you got:
    Serial.println(pin);
    // if it's a legitimate pin number:
    if (pin < 22) {
      // turn it on:
      digitalWrite(pin, HIGH);
      // and turn the last one off:
      digitalWrite(lastPin, LOW);
      // save the current as last for next time through:
      lastPin = pin;
    }
  }
}
