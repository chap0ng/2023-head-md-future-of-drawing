#include <Adafruit_NeoPixel.h>
#include <Arduino_LSM9DS1.h>

#define PIN            3  // Set the pin number to which the Data-In of the Neopixel Ring is connected
#define NUMPIXELS      24 // Set the number of pixels in your Neopixel Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float x, y, z;
int degreesX = 0;
int degreesY = 0;
unsigned long lastMovementTime = 0;

void setup() {
  pixels.begin(); // Initialize the Neopixel library

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
      lastMovementTime = millis(); // Update the last movement time
    } else {
      // If no movement and more than 2 seconds have passed, turn off the LEDs
      if (millis() - lastMovementTime > 3000) {
        pixels.clear();
        pixels.show();
      }
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

// Function to perform a color wipe effect
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
  delay(wait);
}
