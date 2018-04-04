/**
 * @file tuino_demo_serial_redirect.ino
 * @description Demo to show the usage of a GPS receiver with TUINO.
 * @author akrause
 * @copyright (C) 2017 mm1 Technology GmbH - all rights reserved. 
 * @licence MIT licence
 * 
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 * 
 * Code pieces partially based on seeed example project(s):
 * hhttp://wiki.seeed.cc/Grove-GPS/
 */

#define MAX_BUFFER_SZ   64

#include <SoftwareSerial.h>
SoftwareSerial SoftSerial(4, 5);                    // Digital port D4 (also occupies D5, so leave it unused)
unsigned char buffer[MAX_BUFFER_SZ];                // buffer array for data receive over serial port
int count=0;                                        // counter for buffer array


/**
 * @brief Utility function to clear buffer array.
 */
void clearBufferArray()
{
    for (int i=0; i<count;i++)
    {
        buffer[i]=NULL;
    }                                               // clear all index of array with command NULL
}


/**
 * @brief 
 */
void setup()
{
    SoftSerial.begin(9600);                         // the SoftSerial baud rate
    Serial.begin(9600);                             // the Serial port of Arduino baud rate.
}



/**
 * @brief 
 */
void loop()
{
    /* GPS --> Serial */
    if (SoftSerial.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
    {
        while(SoftSerial.available() && (count < MAX_BUFFER_SZ))
        {
            buffer[count++]=SoftSerial.read();      // reading / writing data into array
        }
        Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
        clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
        count = 0;                                  // set counter of while loop to zero 
    }

    /* Serial --> GPS */
    if (Serial.available())                         // if data is available on hardware serial port ==> data is coming from PC or notebook
    {
      SoftSerial.write(Serial.read());              // write it to the SoftSerial shield
    }
}

