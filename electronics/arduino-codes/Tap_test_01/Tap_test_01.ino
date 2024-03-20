#include <Adafruit_NeoPixel.h>
#include <Arduino_LSM9DS1.h>

#define NEOPIXEL_PIN 9  // Pin where the NeoPixel is connected
#define NUMPIXELS 24    // Number of pixels in your NeoPixel Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

float x, y, z;
bool tiltingEnabled = false;
unsigned long lastTapTime = 0;               // Variable to store the last tap time
unsigned long lastTiltTime = 0;              // Variable to store the last tilt time
const unsigned long debounceDelay = 50;      // Debounce delay to prevent multiple taps
const float tapThreshold = 2.0;              // Adjust this threshold based on your testing
const unsigned long noMotionTimeout = 3000;  // 3 seconds timeout for turning off LED

// Function to detect tap based on accelerometer data
bool tapDetected() {
  IMU.readAcceleration(x, y, z);
  float totalAcceleration = sqrt(x * x + y * y + z * z);

  return totalAcceleration > tapThreshold;
}

void setup() {
  pixels.begin();  // Initialize the NeoPixel library

  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
}

void loop() {
  // Check for tap detection
  bool isTapDetected = tapDetected();
  if (isTapDetected) {
    unsigned long currentMillis = millis();

    // Check if it's a new tap and not a multiple tap within the debounce delay
    if (currentMillis - lastTapTime > debounceDelay) {
      lastTapTime = currentMillis;

      // Toggle tiltingEnabled state
      tiltingEnabled = !tiltingEnabled;

      if (tiltingEnabled) {
        Serial.println("Tilting enabled!");
        // Additional code to execute when tilting is enabled
        colorWipe(pixels.Color(255, 255, 255), 50);  // Display white color
        lastTiltTime = currentMillis;                // Reset the tilt timer
      } else {
        Serial.println("Tilting disabled!");
        // Additional code to execute when tilting is disabled
        pixels.clear();
        pixels.show();
        delay(1000);
      }
    }
  }

  // Check if tilting is enabled
  if (tiltingEnabled && IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Print tilt data to Serial Monitor
    Serial.print("Tilt X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Z: ");
    Serial.println(z);
  }

  // Check for no motion timeout
  if (tiltingEnabled && (millis() - lastTiltTime > noMotionTimeout)) {
    Serial.println("No tilt detected. Turning off LED.");
    tiltingEnabled = false;
    pixels.clear();
    pixels.show();
    delay(1000);
  }

  // Remove the delay to make the detection responsive
  // delay(1000);
}

// Function to perform a color wipe effect
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(wait);
  }
}
