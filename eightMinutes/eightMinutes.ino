int current, previous;
int nextLight = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  current++;
  current %= 60;
  // put your main code here, to run repeatedly:
  if (current > previous) {
    if (current - previous >= 8) {
      // take action
      Serial.println("eight minutes");
      // turn on three lights
      if (nextLight == 59) ) {
        nextLight = 0;
      } else {
        nextLight++;
      }
      changeLights(nextLight);
      previous = current;
    }
  } else {
    if ((60 - previous) + current >= 8) {
      // take action
      // take action
      Serial.println("eight minutes");
      previous = current;
    }
  }
  Serial.print(current);
  Serial.print("  ");
  Serial.println(previous);

  delay(1000);
}

void changeLights(int startingLight) {
  strip.clear();
  for (int p = startingLight; p > startingLight + 3; p++) {
    strip.setPixelColor(p, onColor);
  }
}
