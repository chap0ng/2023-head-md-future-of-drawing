#include <Adafruit_NeoPixel.h>
#include <Arduino_LSM9DS1.h>

#define PIN            3  // Set the pin number to which the Data-In of the Neopixel Ring is connected
#define NUMPIXELS      24 // Set the number of pixels in your Neopixel Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float x, y, z;
int degreesX = 0;
int degreesY = 0;
unsigned long lastMovementTime = 0;

// Set tilt sensitivity threshold
float tiltThreshold = 0.1;

void setup() {
  pixels.begin(); // Initialize the Neopixel library

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
}

void loop() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Check for movement and display white color
    if (abs(x) > tiltThreshold || abs(y) > tiltThreshold) {
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

  if (abs(x) > tiltThreshold) {
    x = 100 * x;
    degreesX = map(x, 0, (x > 0) ? 97 : -100, 0, 90);
    Serial.print("Tilting ");
    Serial.print((x > 0) ? "up " : "down ");
    Serial.print(degreesX);
    Serial.println(" degrees");
  }

  if (abs(y) > tiltThreshold) {
    y = 100 * y;
    degreesY = map(y, 0, (y > 0) ? 97 : -100, 0, 90);
    Serial.print("Tilting ");
    Serial.print((y > 0) ? "left " : "right ");
    Serial.print(degreesY);
    Serial.println(" degrees");
  }

  delay(3000);
}

// Function to perform a color wipe effect
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
  delay(wait);
}
