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

String readSoftSerial() {
  //varibles
  const String lineStartSeq = "$GPRMC";
  char rxChar = '\0';
  String str = "";
  
  int indexStart = -1;
  int indexEnd = -1;

  do {
    if (SoftSerial.available())                     // if data is coming from software serial port ==> data is coming from SoftSerial shield
    {
      /*read character from serial*/
      rxChar = SoftSerial.read();
      str += rxChar;

      /*detect 'start of message'*/
      indexStart = str.indexOf(lineStartSeq);

      if (indexStart != str.lastIndexOf(lineStartSeq)) {
        indexStart = str.lastIndexOf(lineStartSeq);
      }
      if (indexStart > 0) {
        str = str.substring(indexStart, str.length());
        indexStart = str.indexOf(lineStartSeq);
      }
      /*detect 'end of message'*/
      indexEnd = str.indexOf('\r');
    }
  } while ((indexStart < 0) || (indexStart >= indexEnd));
  //Serial.println("Test string-function: " + str);
  return str;

}

bool isValid(String a){
  bool coordValid;
  int commaCount = 0;
  String gps_coords = "";
  String serial = "";

  
  commaCount = 0;
  for (int strPos = 0; a[commaCount + strPos]; a[commaCount + strPos] == ',' ? commaCount++ : strPos++);

  coordValid = (commaCount == 4);
  coordValid = coordValid && ((a[12] == 'N') || (a[12] == 'S'));
  coordValid = coordValid && ((a[25] == 'E') || (a[25] == 'W'));

  if (coordValid)
  {
    gps_coords = a;
    Serial.println("to relay: " + a.substring(2,26));
  }
  else
  {
    Serial.println("invalid GPS data: " + a);
    Serial.println("commaCount:" + String(commaCount) + " a[12]:" + String(a[12]) + " a[25]:" + String(a[25]));
  }
}

void setup()
{
  SoftSerial.begin(9600);                         // the SoftSerial baud rate
  Serial.begin(9600);                             // the Serial port of Arduino baud rate.
}

void loop()
{
  String serial = "";
  String res = "";

  /* GPS --> Serial */
  serial = readSoftSerial();
  Serial.println("from GPS: " + serial + " len: " + serial.length());
  res = serial.substring(serial.indexOf('A') , serial.indexOf('A') + 26);
  isValid(res);

  /* Serial --> GPS */
  if (Serial.available())               // if data is available on hardware serial port ==> data is coming from PC or notebook
  {
    SoftSerial.write(Serial.read());   // write it to the SoftSerial shield
  }
}

