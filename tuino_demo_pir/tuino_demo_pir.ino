/**
 * @file tuino_demo_pir.ino
 * @description Demo to show TUINO pir setup and function.
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

/*macro definitions of PIR motion sensor pin and LED pin*/
#define PIR_MOTION_SENSOR 4 //Use D4 to receive the signal from the module
#define LED 5 //the Grove - LED is connected to D5 of Tuino


void setup()
{
    pinMode(PIR_MOTION_SENSOR, INPUT);
    pinMode(LED,OUTPUT);
}

void loop()
{
    /*If the motion sensor detects the moving people, the LED turns on*/
    
    if(isPeopleDetected())
    {
        digitalWrite(LED, HIGH);
    }
    else
    {
        digitalWrite(LED, LOW);
    }
}


/***************************************************************/

/*Function: Detect whether anyone moves in it's detecting range*/
/*Return:-boolean, true if someone is detected.*/

boolean isPeopleDetected()
{
    int sensorValue = digitalRead(PIR_MOTION_SENSOR);

    /*if the sensor value is HIGH, the function returns true*/
    /*else it returns false*/
    
    if(sensorValue == HIGH)
    {
        return true;
    }
    else
    {
        return false;
    }
}
