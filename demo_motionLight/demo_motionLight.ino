/**
 * @file demo_motionLight.ino
 * @description Tuino application that demonstrates the usage of a motion sensor.
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

/*macro definitions of PIR motion sensor pin and LED pin*/
#define PIR_MOTION_SENSOR 4//Use D4 to receive the signal from the module
#define LED 5//the Grove - LED is connected to D5 of Arduino


void setup()
{
    pinMode(PIR_MOTION_SENSOR, INPUT);
    pinMode(LED,OUTPUT);
}

void loop()
{
    if(isPeopleDetected())//if it detects the moving people?
        digitalWrite(LED, HIGH);
    else
        digitalWrite(LED, LOW);
}


/***************************************************************/
/*Function: Detect whether anyone moves in it's detecting range*/
/*Return:-boolean, true is someone detected.*/
boolean isPeopleDetected()
{
    int sensorValue = digitalRead(PIR_MOTION_SENSOR);
    if(sensorValue == HIGH)//if the sensor value is HIGH?
    {
        return true;//yes,return true
    }
    else
    {
        return false;//no,return false
    }
}
