#include <Scheduler.h>

int status = 0;   // which state we are in
int buttonState;
void setup() {
  Scheduler.startLoop(orangeLight);
  Scheduler.startLoop(whiteLight);
}

void loop() {

  // if they have changed, change status

}

void orangeLight() {
  if (status == 1) {
    
  }
  yield();
}

void whiteLight() {
  if (status == 2) {

  }
  yield();
}
