#include <Adafruit_NeoPixel.h>
#include <Arduino_LSM9DS1.h>

#define PIN            9  // Set the pin number to which the Data-In of the Neopixel Ring is connected
#define BUTTON_PIN     3  // Set the pin number to which the push button is connected
#define NUMPIXELS      24 // Set the number of pixels in your Neopixel Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float x, y, z;
int degreesX = 0;
int degreesY = 0;
unsigned long lastMovementTime = 0;
bool ledState = true;  // Initial state of the LEDs

void setup() {
  pixels.begin(); // Initialize the Neopixel library
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set the button pin as input with pull-up resistor

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
  // Check the state of the button
  if (digitalRead(BUTTON_PIN) == LOW) {
    ledState = !ledState;  // Toggle the LED state when the button is pressed
    delay(200);  // Debounce delay
  }

  if (ledState) {
    // Check for movement and display white color
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x, y, z);
      if (abs(x) > 0.1 || abs(y) > 0.1) {
        colorWipe(pixels.Color(255, 255, 255), 50); // Display white color
        lastMovementTime = millis(); // Update the last movement time
      } else {
        // If no movement and more than 1 second has passed, turn off the LEDs
        if (millis() - lastMovementTime > 1000) {
          pixels.clear();
          pixels.show();
        }
      }
    }
  } else {
    pixels.clear();  // Turn off the LEDs if the button is pressed and LED state is off
    pixels.show();
  }

  if (x > 0.1) {
    x = 100 * x;
    degreesX = map(x, 0, 97, 0, 90);
    Serial.print("Tilting up ");
    Serial.print(degreesX);
    Serial.println("  degrees");
    if (ledState) {
      // Dim the LEDs when tilted up
      dimPixels(70);
    }
  }

  if (x < -0.1) {
    x = 100 * x;
    degreesX = map(x, 0, -100, 0, 90);
    Serial.print("Tilting down ");
    Serial.print(degreesX);
    Serial.println("  degrees");
    if (!ledState) {
      pixels.clear();  // Turn off the LEDs immediately when tilted down if LED state is off
      pixels.show();
    }
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

  delay(100);
}

// Function to perform a color wipe effect
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
  delay(wait);
}

// Function to dim the pixels gradually with a specified brightness level
void dimPixels(int brightness) {
  pixels.setBrightness(brightness);
  pixels.show();
}
