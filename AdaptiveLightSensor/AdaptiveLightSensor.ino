/*
  Adaptive light
  Reads a light sensor on pin A0 and dynamically
  determines max and min light levels
  Then PWMs an LED on pin 4 to match the range of input
*/

// variables to store the max and min light levels 
// that the sensor ever reads:
int maxLightLevel = 0;
int minLightLevel = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // read the sensor:
  int lightSensor = analogRead(A0);
  Serial.println(lightSensor);
  // if the current reading is greater than the max,
  // adjust the max:
  if (lightSensor >= maxLightLevel) {
    maxLightLevel = lightSensor;
  }
  // if the current reading is less than the min,
  // adjust the min:
  if (lightSensor <= minLightLevel) {
    minLightLevel = lightSensor;
  }
  // map the intensity based on the max and min levels:
  int intensity = map(lightSensor, maxLightLevel, minLightLevel, 0, 255);
  // output the result:
  analogWrite(4, intensity);
  Serial.println(lightSensor);
}
