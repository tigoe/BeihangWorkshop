// The serviceUuid must match the serviceUuid of the device 
// to which you would like to connect

// based on write-one-char example https://itpnyu.github.io/p5ble-website/docs/write-one-char-callback by p5ble.

const serviceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
let redCharacteristic = 0;
let greenCharacteristic = 0;
let blueCharacteristic = 0;
let whiteCharacteristic = 0;
let myBLE;

function setup() {
  myBLE = new p5ble();

  // Create a 'Connect' button
  const connectButton = createButton('Connect')
  connectButton.mousePressed(connectToBle);
  connectButton.position(15, 65);

  // Create a text input
  redSlider = createSlider();
  redSlider.position(15, 100);
  greenSlider = createSlider();
  greenSlider.position(15, 150);
  blueSlider = createSlider();
  blueSlider.position(15, 200);
  whiteSlider = createSlider();
  whiteSlider.position(15, 250);

  // Create a 'Write' button
  const writeButton = createButton('Write');
  writeButton.position(redSlider.x + redSlider.width + 15, 175);
  writeButton.mousePressed(writeToBle);
}

function connectToBle() {
  // Connect to a device by passing the service UUID
  myBLE.connect(serviceUuid, gotCharacteristics);
}

function gotCharacteristics(error, characteristics) {
  if (error) console.log('error: ', error);
  console.log('characteristics: ', characteristics);
  // Set the first characteristic as myCharacteristic
  redCharacteristic = characteristics[0];
  greenCharacteristic = characteristics[1];
  blueCharacteristic = characteristics[2];
  whiteCharacteristic = characteristics[3];
  
}

function writeToBle() {
   const redValue = redSlider.value();
   const greenValue = greenSlider.value();
   const blueValue = blueSlider.value();
   const whiteValue = whiteSlider.value();
  // Write the value of the input to the myCharacteristic
  myBLE.write(redCharacteristic, redValue);
  myBLE.write(greenCharacteristic, greenValue);
  myBLE.write(blueCharacteristic, blueValue);
  myBLE.write(whiteCharacteristic, whiteValue);
}
