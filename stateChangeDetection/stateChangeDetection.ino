int lastButtonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, INPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // read tbe button
  int buttonState = digitalRead(5);

  // if buttonState changes from 0 to 1, blink the LED
  if (buttonState != lastButtonState) {
    delay(5);  // debounce delay 5 ms
    if (buttonState == HIGH) {  // if the button is pressed:
      Serial.println("pressed");
      blinky(3);  // blink the LED 3 times
    } else {      // if the button is released:
      Serial.println("released");
    }
  }
  // save the button state for comparison next time:
  lastButtonState = buttonState;
}

// blink the LED function:
void blinky (int times) {
  // loop multiple times:
  for (int x = 0; x < times; x++) {
    digitalWrite(4, HIGH);  // turn the LED on
    delay(250);             // wait
    digitalWrite(4, LOW);   // turn the LED off
    delay(250);             // wait
  }
}
