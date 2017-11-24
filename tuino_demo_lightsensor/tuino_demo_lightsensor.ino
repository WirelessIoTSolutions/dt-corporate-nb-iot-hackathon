
/**
 * @file tuino_demo_lightsensor.ino
 * @description Demo to show light sensor setup and function.
 * @author heydecke
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

/*Light Sensor is connect to A0 of Arduino*/
#define LIGHT_SENSOR A0
float Rsensor;


void setup()
{
  /*serial debug output*/
  Serial.begin(9600);
  Serial.println("Light Sensor Demo");
}



/**
 * @brief Main code here, to run repeatedly. Avoid blocking code sequences!
 * 
 * The function will collect light intensity values every 1000 milliseconds and 
 * prints to the serial monitor. Make sure the light sensor is connected to A0.
 */
void loop()
{
    int sensorValue = analogRead(LIGHT_SENSOR); 
    Rsensor = (float)(1023-sensorValue)*10/sensorValue;
    
    Serial.println("the analog read data is: " + String(sensorValue));
    Serial.println("the sensor resistance is. " + String(Rsensor));
    
    delay(1000);
}
