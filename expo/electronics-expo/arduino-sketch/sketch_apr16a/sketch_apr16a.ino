#include <Adafruit_NeoPixel.h>
#include <Arduino_LSM9DS1.h>


#define PIN            3  // Set the pin number to which the Data-In of the Neopixel Ring is connected
#define NUMPIXELS      24 // Set the number of pixels in your Neopixel Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // Initialize the Neopixel library
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned int r = (int)random(255);
  unsigned int g = (int)random(255);
  unsigned int b = (int)random(255);

  colorWipe(pixels.Color(r, g, b)); // Display white color    

  Serial.print(r);
  Serial.print("\t");
  Serial.print(g);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\n");   

  delay(3000);

}



// Function to perform a color wipe effect
void colorWipe(uint32_t color) {
  for(int i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}
