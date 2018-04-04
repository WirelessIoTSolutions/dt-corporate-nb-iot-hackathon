/**
 * @file tuino_demo_heater.ino
 * @description Demo to show ...
 * @author julia heydecke
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

/*Temperature sensor constants*/
#define TEMPERATURE_SAMPLING    (10)

int button = 4;   //attach a button to D4
int tempSensorPin = A0;
float current_temperature = 0.0f;


float readTemp() {
  const int B = 4275;                                           // B value of the thermistor
  int sensorRaw = (float)analogRead(tempSensorPin);
  float R = 1023.0 / ((float)sensorRaw) - 1.0;
  float temperature = 1.0 / (log(R) / B + 1 / 298.15) - 273.15; //convert to temperature via datasheet ;

  return temperature;
}



/**
 * @brief Initialisation, called once during system startup.
 * 
 * Make sure the temperature sensor is connected to A0. Debugging 
 * output is visible at the serial monitor of Arduino IDE.
 */
void setup() {
  /*serial debug output*/
  pinMode(button, INPUT);  //define button an INPUT device
  Serial.begin(9600);
  Serial.println("Temperature Sensor Demo");
  // Init Temperature
  current_temperature = readTemp();

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
  SeeedOled.putString("Temp: ");
  SeeedOled.setTextXY(4, 0);
  SeeedOled.putString("Fenster: ");
  SeeedOled.setTextXY(6, 0);
  SeeedOled.putString("aktuell: ");
}




/**
 * @brief Main code here, to run repeatedly. Avoid blocking code sequences!
 * 
 * The function will be collects temperature values every 100 milliseconds and 
 * prints the them every second to the serial monitor. Make sure the temperature 
 * sensor is connected to A0.
 */
void loop() {
  static float temp_temperature = 0.0f;
  static int temperature_counts = 0;
  int buttonState = digitalRead(button);  //read the status of the button
    
  // update temperature
  // we sample and make an average of the temperature - since in this demo we use a NTC sensor that fluctuates
  temp_temperature += readTemp();
  temperature_counts++;

  if ( temperature_counts >= TEMPERATURE_SAMPLING ) {
    current_temperature = temp_temperature / TEMPERATURE_SAMPLING;
    temperature_counts = 0;
    temp_temperature = 0;

  if (current_temperature < 17 ) {
    SeeedOled.setTextXY(2, 8);
    SeeedOled.putString("  kalt");
  }
  else {
    SeeedOled.setTextXY(2, 8);
    SeeedOled.putString("  warm"); 
  }

  if(buttonState == 0) {
    SeeedOled.setTextXY(4, 8);
    SeeedOled.putString(" offen");
  }
  else {
    SeeedOled.setTextXY(4, 8);
    SeeedOled.putString("    zu");
  }}
    
  SeeedOled.setTextXY(6, 9);
  SeeedOled.putNumber(current_temperature);
  
  Serial.println(current_temperature);
  //delay(1000);
}


