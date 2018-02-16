/**
 * @file tuino_batStatus.ino
 * @description Demo to show TUINO battery state of charge and voltage function.
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
**/

#include "MAX17048.h"
#include "Wire.h"


MAX17048 batteryMonitor;

float cellVoltage;
float stateOfCharge;

void setup() {
  
  Wire.begin(); 
  Serial.begin(9600);
  Serial.println("MAX17048 Example: reading voltage and SoC");
  Serial.println();
  
  batteryMonitor.reset();
  batteryMonitor.quickStart();
 
  delay(1000);

}



void loop() {   

  cellVoltage = batteryMonitor.getVCell();
  Serial.print("Voltage:\t\t");
  Serial.print(cellVoltage, 4);
  Serial.println("V");

  stateOfCharge = batteryMonitor.getSoC();
  Serial.print("State of charge:\t");
  Serial.print(stateOfCharge);
  Serial.println("%");
   
  delay(10000);
  
}

