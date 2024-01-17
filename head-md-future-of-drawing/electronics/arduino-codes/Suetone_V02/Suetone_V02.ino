#include <Adafruit_NeoPixel.h>
#include <Arduino_LSM9DS1.h>

#define NEOPIXEL_PIN   9  // Pin where the NeoPixel is connected
#define BUTTON_PIN     3  // Pin where the button is connected
#define NUMPIXELS      24 // Number of pixels in your NeoPixel Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

float x, y, z;
int degreesX = 0;
int degreesY = 0;
bool tiltingEnabled = false;
unsigned long lastButtonPressTime = 0;  // Variable to store the last button press time
unsigned long lastMovementTime = 0;  // Variable to store the last movement time
const unsigned long debounceDelay = 50;  // Debounce delay to prevent button bounce

void setup() {
  pixels.begin(); // Initialize the NeoPixel library

  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Assuming the button is connected to pin 3 with a pull-up resistor

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
}

void loop() {
  // Check if the button is pressed and debounced
  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastButtonPressTime > debounceDelay) {
    // Update the last button press time
    lastButtonPressTime = millis();

    // Toggle tiltingEnabled state
    tiltingEnabled = !tiltingEnabled;

    // If tilting is disabled, turn off LEDs and skip the rest of the loop
    if (!tiltingEnabled) {
      pixels.clear();
      pixels.show();
      delay(1000);
      return;
    }
  }

  // Check if tilting is enabled
  if (tiltingEnabled && IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Check for movement and display white color
    if (abs(x) > 0.1 || abs(y) > 0.1) {
      colorWipe(pixels.Color(255, 255, 255), 50); // Display white color
      lastMovementTime = millis();  // Update the last movement time
    } else {
      // If no movement, turn off the LEDs after 3 seconds
      if (millis() - lastMovementTime > 3000) {
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
