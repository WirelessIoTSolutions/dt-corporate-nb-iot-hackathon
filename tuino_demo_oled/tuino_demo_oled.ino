/**
 * @file tuino_demo_oled.ino
 * @description Demo to show TUINO OLED display setup and function.
 * @author akrause
 * @copyright (C) 2017 mm1 Technology GmbH - all rights reserved. 
 * @licence MIT licence
 * 
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 * 
 * Code pieces partially based on GIMASI TUINO example project(s):
 * Company: http://www.tuino.io/
 * GitHub:  https://github.com/gimasi
 */

#include <Wire.h>
#include "SeeedOLED.h"




/**
 * @brief Initialisation, called once during system startup.
 * 
 * Make sure the OLED display is connected to I2C to see 
 * the output.
 */
void setup() {
  /*init I2C (to access OLED display)*/
  Wire.begin();
  
  /*now init OLED*/
  SeeedOled.init();               //initialze SEEED OLED display
  SeeedOled.clearDisplay();       //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();   //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setHorizontalMode();  //Set addressing mode to Page Mode

  /*put the text on the display that never change:*/
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putString("OLED Demo");
  SeeedOled.setTextXY(2, 0);
  SeeedOled.putString("Counter: ");
  SeeedOled.setTextXY(4, 0);
  SeeedOled.putString("Uptime: ");
}



/**
 * @brief Converts a continuous counter into a time string and prints it to OLED.
 *
 * The time string format is HH:MM:SS.
 */
void printUptime(long counter) {
  long tmp = counter;
  long secs;
  long mins;
  long hours;
  char tmpstr[16];

  secs = tmp % 60;
  tmp /= 60;
  mins = tmp % 60;
  hours = tmp / 60;

  /* NOTE on workaround: 
   * buggy sprintf accepts only 1 variable parameter in format string...
   */
  sprintf(tmpstr, "%4d", hours);
  SeeedOled.putString(tmpstr);
  sprintf(tmpstr, ":%02d", mins);
  SeeedOled.putString(tmpstr);
  sprintf(tmpstr, ":%02d", secs);
  SeeedOled.putString(tmpstr);
}



/**
 * @brief Main code here, to run repeatedly. Avoid blocking code sequences!
 * 
 * The function will be called once every second and prints the current uptime 
 * to the OLED display. Make sure the OLED display is connected to I2C to see 
 * the output.
 */
void loop() {
  static long seconds = 0;
  char tmpstr[16];

  /*displayed numbers that change for each loop call*/

  /*counter for uptime seconds*/
  SeeedOled.setTextXY(2, 8);
  //doesn't format numbers well: SeeedOled.putNumber(seconds);
  sprintf(tmpstr, "%8ld", seconds);
  SeeedOled.putString(tmpstr);

  /*uptime clock*/
  SeeedOled.setTextXY(4, 6);
  printUptime(seconds);
  
  seconds++;
  delay(1000);
}
