/**
   @file tuino_demo_distance.ino
   @description Demo to show the usage of a ultrasonic ranger with TUINO.
   @author julia heydecke
   @copyright (C) 2017 mm1 Technology GmbH - all rights reserved.
   @licence MIT licence

   Find out more about mm1 Technology:
   Company: http://mm1-technology.de/
   GitHub:  https://github.com/mm1technology/

   Code pieces partially based on seeed example project(s):
   hhttp://wiki.seeed.cc/Grove-Ultrasonic_Ranger/
*/

#include "Ultrasonic.h"

Ultrasonic ultrasonic(4);
void setup()
{
    Serial.begin(9600);
}
void loop()
{
    long RangeInInches;
    long RangeInCentimeters;

    Serial.println("The distance to obstacles in front is: ");
    RangeInInches = ultrasonic.MeasureInInches();
    Serial.print(RangeInInches);//0~157 inches
    Serial.println(" inch");
    delay(1000);

    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
    Serial.print(RangeInCentimeters);//0~400cm
    Serial.println(" cm");
    delay(1000);
}
