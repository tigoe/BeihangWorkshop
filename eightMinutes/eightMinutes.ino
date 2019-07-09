int current, previous;
int nextLight = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if (current < 60) {
    current++;
  } else {
    current = 0;
  }
  // put your main code here, to run repeatedly:
  if (current > previous) {
    if (current - previous >= 8) {
      // take action
      Serial.println("eight minutes");
      // turn on three lights
      if (nextLight == 58) {
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

void changeLights(int   changed = true;) {
  //  strip.clear();
  Serial.print("StartingLight = ");
  Serial.println(startingLight);
  for (int p = startingLight;  // stating value of P
       p < startingLight + 3;  // do it until this is false
       p++) {                  // do this every time through the loop
    Serial.print("    p = ");
    Serial.println(p);
    //    strip.setPixelColor(p, onColor);
  }
}
