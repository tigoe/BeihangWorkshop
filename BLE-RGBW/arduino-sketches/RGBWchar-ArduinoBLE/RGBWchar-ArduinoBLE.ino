/*
  RGBW LED

  This example creates a BLE peripheral with service that contains 
  four characteristics to control an RGBW LED strip.

  The circuit:
  - Arduino MKR WiFi 1010 or Arduino Uno WiFi Rev2 board
  - RGBW LED strip attached to pins 2, 3, 4, 5

*/
#include <ArduinoBLE.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED hue Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic redCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEByteCharacteristic greenCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEByteCharacteristic blueCharacteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEByteCharacteristic whiteCharacteristic("19B10004-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

// pin numbers for LED channels:
const int redPin = 2;
const int greenPin = 3;
const int bluePin = 4;
const int whitePin = 5;
// make variables for red, green, blue, white:
byte red = 0;
byte green = 0;
byte blue = 0;
byte white = 0;

void setup() {
  Serial.begin(9600);
  // do nothing until serial monitor opens:
  while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    // do nothing:
    while (true);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("RGBW_Strip");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(redCharacteristic);
  ledService.addCharacteristic(greenCharacteristic);
  ledService.addCharacteristic(blueCharacteristic);
  ledService.addCharacteristic(whiteCharacteristic);

  // add service
  BLE.addService(ledService);

  // start advertising
  BLE.advertise();

  Serial.println("BLE RGBW LED Peripheral");
  // make all the LED control pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(whitePin, OUTPUT);
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      bool changed = false;
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:

      if (redCharacteristic.written()) {
        red = redCharacteristic.value();
        changed = true;
      }
      if (greenCharacteristic.written()) {
        green = greenCharacteristic.value();
        changed = true;
      }
      if (blueCharacteristic.written()) {
        blue = blueCharacteristic.value();
        changed = true;
      }
      if (whiteCharacteristic.written()) {
        white = whiteCharacteristic.value();
        changed = true;
      }
      if (changed) {
        // update the LEDs:
        analogWrite(redPin, red);
        analogWrite(greenPin, green);
        analogWrite(bluePin, blue);
        analogWrite(whitePin, white);
        Serial.print(red, HEX);
        Serial.print("   ");
        Serial.print(green, HEX);
        Serial.print("   ");
        Serial.print(blue, HEX);
        Serial.print("   ");
        Serial.println(white, HEX);
      }
    }
  
    // when the central disconnects, print it out:
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
