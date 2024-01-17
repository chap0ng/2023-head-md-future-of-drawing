#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 9
#define PIXELS_NUM 24

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS_NUM, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Set the RGB brightness of the first 8 LEDs
  for (int i = 0; i < 8; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0));
  }
  strip.show();
  Serial.println("color 1");
  delay(1000);

  // Set the RGB brightness of the next 8 LEDs
  for (int i = 8; i < 16; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
  strip.show();
  Serial.println("color 2");
  delay(1000);

  // Set the RGB brightness of the last 8 LEDs
  for (int i = 16; i < 24; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
  strip.show();
  Serial.println("color 3");
  delay(1000);

  // Set all LEDs to 'off'
  for (int i = 0; i < PIXELS_NUM; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
  Serial.println("all off");
  delay(1000);
}

