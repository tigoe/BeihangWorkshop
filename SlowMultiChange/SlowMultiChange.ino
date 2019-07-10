
int sensorCount = 4;            // number of sensors
long lastChange[sensorCount];   // the last time the sensor was changed
int intensity[sensorCount] ;    // the brightness of the light
int interval[sensorCount];      // the time between fades of the light
int sensor[sensorCount];        // the sensor's value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // loop over all the sensors:
  for (int i = 0; i < sensorCount; i++) {
   // read the sensor, map it to make it fit the analogWrite() command
   // sensor goes from 17 to 623, we want 0 to 255:
    sensor[i] = map(analogRead(i, 17, 623, 0, 255);
    
    // if the interval has passed since last intensity change:
    if (millis() - lastChange[i] > interval[i]) {
      // if the intensity is greater than the sensor,
      // move it one point down:
      if (intensity[i] > sensor[i]) {
        intensity[i]--;
      }
      // if the intensity is less than the sensor,
      // move it one point up:
      if (intensity[i] < sensor[i]) {
        intensity[i]++;
      }
      lastChange[i] = millis();
    }
    //output to pins i + 2:
    analogWrite(i + 2, intensity[i]);
  }
}
