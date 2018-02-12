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
#include "gps_data.h"
#include "byteorder.h"

SoftwareSerial SoftSerial(4, 5); // Digital port D4 (also occupies D5, so leave it unused)
gps_coord_t coord;

void setup()
{
  SoftSerial.begin(9600);                         // the SoftSerial baud rate
  Serial.begin(9600);                             // the Serial port of Arduino baud rate.
  Serial.println("*** GPS Demo ***");
}


void loop () 
{
   char payload[8];
   char hex[3];
   coord = readGPS();

   if ((coord.longitude.fl || coord.latitude.fl) != 0.0) {
    gps_to_mqtt(coord, payload);
    Serial.print("MQTT-SN payload: ");
    byte_to_hex(payload[0], hex);
    Serial.print( hex );
    for( int i = 1; i < 8; i++) {
      byte_to_hex(payload[i], hex);
      Serial.print(", ");
      Serial.print( hex );
    }   
    Serial.println();
   }
}


 

