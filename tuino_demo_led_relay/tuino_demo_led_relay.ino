/**
 * @file tuino_demo_led_relay.ino
 * @description Demo to show TUINO digital output setup and function.
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
 
/*connect a LED to D5!*/
 int outPin = D5;

/**
 * @brief Initialisation, called once during system startup.
 */
void setup() {
  /*serial debug output*/
  Serial.begin(9600);
  Serial.println("DigOutput Demo");
  
  /*configure as output*/
  pinMode(outPin, OUTPUT);
}



/**
 * @brief Main code here, to run repeatedly. Avoid blocking code sequences!
 * 
 * The function shows how to toggle a digital output pin every second. (You might 
 * want to connect an LED or relay to D5 to notice an effect.)
 */
void loop() {
  /*Put your main code here, to run repeatedly. Avoid blocking code sequences!*/
  static bool ledState = false;

  /*toggle dig out*/
  ledState = !ledState;
  digitalWrite(outPin, ledState);
  /*wait 1 second*/
  delay(1000);
}

