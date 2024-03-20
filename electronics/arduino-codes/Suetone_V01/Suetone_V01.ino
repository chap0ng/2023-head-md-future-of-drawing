#include <Adafruit_NeoPixel.h>
#include <Arduino_LSM9DS1.h>

#define PIN            9  // Définissez le numéro de broche auquel est connecté le Data-In de la Neopixel Ring
#define NUMPIXELS      24 // Définissez le nombre de pixels dans votre Neopixel Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float x, y, z;
int degreesX = 0;
int degreesY = 0;

void setup() {
  pixels.begin(); // Initialisez la bibliothèque Neopixel

  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
}

void loop() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Check for movement and display white color
    if (abs(x) > 0.1 || abs(y) > 0.1) {
      colorWipe(pixels.Color(255, 255, 255), 50); // Display white color
    } else {
      // If no movement, turn off the LEDs
      pixels.clear();
      pixels.show();
    }
  }

  if (x > 0.1) {
    x = 100 * x;
    degreesX = map(x, 0, 97, 0, 90);
    Serial.print("Tilting up ");
    Serial.print(degreesX);
    Serial.println("  degrees");
  }

  if (x < -0.1) {
    x = 100 * x;
    degreesX = map(x, 0, -100, 0, 90);
    Serial.print("Tilting down ");
    Serial.print(degreesX);
    Serial.println("  degrees");
  }

  if (y > 0.1) {
    y = 100 * y;
    degreesY = map(y, 0, 97, 0, 90);
    Serial.print("Tilting left ");
    Serial.print(degreesY);
    Serial.println("  degrees");
  }

  if (y < -0.1) {
    y = 100 * y;
    degreesY = map(y, 0, -100, 0, 90);
    Serial.print("Tilting right ");
    Serial.print(degreesY);
    Serial.println("  degrees");
  }

  delay(1000);
}

// Fonction pour effectuer un effet de balayage de couleur
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
  delay(wait);
}
