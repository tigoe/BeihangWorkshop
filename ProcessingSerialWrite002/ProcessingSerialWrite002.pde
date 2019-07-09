/*
  works with WS281xSerial Arduino sketch
 */

import processing.serial.*;

Serial myPort;          // an instance of the serial port library
String outString = "";  // a string to send out the port

void setup() {
  // set the size of the window:
  size(640, 480);
  // set the size of the font:
  textSize(36);
  // print the list of all available serial ports:
  printArray(Serial.list());
  // open the first port in the list:
  myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  // black background, light blue foreground:
  background(0);
  fill(#A387FF);
  // text the output string to the middle of the window:
  text(outString, width/2, height/2);
  // if there is incoming serial data, read it as a string:
  if (myPort.available() > 0) {
    println(myPort.readString());
  }
}

// if a key between 0 and 9 is pressed, add it to the string.
// if enter is pressed, send the string:
void keyPressed() {
  if (key >= '0' && key <= '9') {
    outString = outString + key;
  }

  if (key == ENTER) {
    myPort.write(outString);
    outString = "";
  }
}
// map the mouseY to a range from 0 to 24 and send it as a string:
void mousePressed() {
  println(mouseY / 20);
  outString = "" + mouseY /20;
  myPort.write(outString);
  outString = "";
}
