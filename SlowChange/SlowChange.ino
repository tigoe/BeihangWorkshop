long lastChange = 0;
int intensity = 0;
int interval = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor = analogRead(A0) / 4;
  if (millis() - lastChange > interval) {
    // if the intensity is greater than the sensor,
    // move it one point down:
    if (intensity > sensor) {
      intensity--;
    }
    // if the intensity is less than the sensor,
    // move it one point up:
    if (intensity < sensor) {
      intensity++;
    }
    lastChange = millis();
  }
  Serial.print(sensor);
  Serial.print("\t");
  Serial.println(intensity);
  analogWrite(5, intensity);
}
