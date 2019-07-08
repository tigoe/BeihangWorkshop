/*
  Sends an ASCII-numeric string out the serial port when you type it
 in the canvas.
 Use with the WS281xSerial example.
 */

import processing.serial.*;

Serial myPort;  // Create object from Serial class
String outString = "";

void setup() 
{
  size(640, 480);
  printArray(Serial.list());
  // open the first serial port in the list:
  String portName = Serial.list()[0];
  // make an instance of the serial library with this port:
  myPort = new Serial(this, portName, 9600);
  textSize(36);
}

void draw() {
  background(0);
  fill(#00FFEE);
  text(outString, width/2, height/2);
}

void keyPressed() {
  // if the key you pressed is between 0 and 9,
  // add it to the output string:
  if (key >= '0' && key <= '9') {
    outString += key;
  }
  // if the user pressed enter, send the output string
  // out the serial port, then clear the string for use
  // next time:
  if (key == ENTER) {
    myPort.write(outString);
    outString = "";
  }
}
