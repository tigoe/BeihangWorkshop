#include <Adafruit_NeoPixel.h>

const int neoPixelPin = 4;  // control pin
const int pixelCount = 20;    // number of pixels

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRBW + NEO_KHZ800);


int intensity;      // the level of the light
int lastSensor;     // the last sensor reading
int interval = 20;  // the delay between changes to intensity
long lastFade = 0;  // the last time you changed the intensity
int threshold = 40; // the minimum level of the sensor that you care about

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // refresh strip
}

void loop() {
  // read the sensor, /4 to fit a byte:
  int sensor = analogRead(A0) / 4;
  // if the sensor is greater than the intensity:
  if (sensor > intensity && sensor > threshold) {
    intensity = sensor;
    // if sensor  is not greater than intensity, fade the intensity down
  } else {
    // fade one point for every interval:
    if (millis() - lastFade > interval) {
      intensity--;
      if (intensity <= 0) {
        intensity = 0;
      }
      lastFade = millis();
    }
  }
  for (int pixel = 0; pixel < pixelCount; pixel++) {
    strip.setPixelColor(pixel, intensity, intensity, intensity, intensity); // set the color for this pixel

  }

  strip.show();    // refresh the strip

  Serial.print(sensor);
  Serial.print(",");
  Serial.println(intensity);
  lastSensor = sensor;
}
