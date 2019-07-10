int status = 0; // one of 5 different statuses

void setup() {

}

void loop() {

  // read the pushbutton for change

  // if the button has changed, add one to status
  // if status > 4, reset it to 0

  // if staus = 0, do function 1
  function1();
  // if status = 1, do function 2
  function2();

}

void function1() {
  if (millis() - function1LastTime > function1Interval) {
    // do function 1
  }
}


void function2() {
  if (millis() - function2LastTime > function2Interval) {
    // do function 2
  }
}
