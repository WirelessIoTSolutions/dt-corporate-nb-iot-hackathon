/**
   @file tuino_demo_gps.ino
   @description Demo to show the usage of a GPS receiver with TUINO.
   @author akrause
   @copyright (C) 2017 mm1 Technology GmbH - all rights reserved.
   @licence MIT licence

   Find out more about mm1 Technology:
   Company: http://mm1-technology.de/
   GitHub:  https://github.com/mm1technology/

   Code pieces partially based on seeed example project(s):
   hhttp://wiki.seeed.cc/Grove-GPS/
*/

#include <SoftwareSerial.h>
SoftwareSerial SoftSerial(4, 5); // Digital port D4 (also occupies D5, so leave it unused)


void setup()
{
  SoftSerial.begin(9600);                         // the SoftSerial baud rate
  Serial.begin(9600);                             // the Serial port of Arduino baud rate.
  Serial.println("*** GPS Demo ***");
}


void loop () 
{

   readGPS();
 
}




