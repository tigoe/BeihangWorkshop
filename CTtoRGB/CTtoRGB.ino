int red, green, blue, white;
const int redPin = 2;
const int greenPin = 3;
const int bluePin = 4;
const int whitePin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // make all the LED control pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(whitePin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int c = 1500; c < 15000; c++) {
    CTtoRGB(c);
    Serial.print(red);
    Serial.print("\t");
    Serial.print(green);
    Serial.print("\t");
    Serial.println(blue);
  }
  // update the LEDs:
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  analogWrite(whitePin, white);

  delay(1);
}

// algorithm from http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
//Untested

void CTtoRGB( float ct) {
  //  Start with a colorTemp, in Kelvin, somewhere between 1000 and 40000.  (Other values may work,
  //     but I can't make any promises about the quality of the algorithm's estimates above 40000 K.)
  //    Note also that the colorTemp and color variables need to be declared as floating-point.

  float colorTemp = ct / 100.0;
  //   Calculate Red:
  if (colorTemp <= 66 ) {
    red = 255;
  } else {
    red = colorTemp - 60;
    red = 329.698727446 * (pow(red, -0.1332047592));
    red = constrain(red, 0, 255);
  }

  //Calculate green:

  if (colorTemp <= 66) {
    green = colorTemp;
    green = 99.4708025861 * log(green) - 161.1195681661;
    green = constrain(green, 0, 255);
  } else {
    green = colorTemp - 60;
    green = 288.1221695283 * (pow(green, -0.0755148492));
    green = constrain(green, 0, 255);
  }
  if ( colorTemp >= 66 ) {
    blue = 255;
  } else {
    if ( colorTemp <= 19 ) {
      blue = 0;
    } else {
      blue = colorTemp - 10;
      blue = 138.5177312231 * log(blue) - 305.0447927307;
      blue = constrain(blue, 0, 255);
    }
  }
}
