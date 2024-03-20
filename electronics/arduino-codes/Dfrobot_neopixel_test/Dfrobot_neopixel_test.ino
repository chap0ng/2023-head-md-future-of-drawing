/*!
 * @file        RGB ring.ino
 * @brief       The colors of the 24 lamp beads are displayed in gradients and change by levels successively around the circle to form a rotating effect as if it's a dynamic rainbow.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author      [qsjhyy](fengying.nie@dfrobot.com)
 * @version     V0.1
 * @date        2021-09-24
 * @get from    https://www.dfrobot.com
 * @url         
 */
#include <DFRobot_NeoPixel.h>
// Create a object
DFRobot_NeoPixel neoPixel_2;


// Main program start
void setup() {
  neoPixel_2.begin(2, 24);
  neoPixel_2.showRainbow(0, 24, 1, 360);
}
void loop() {
  delay(10);
  neoPixel_2.rotate(1);
}