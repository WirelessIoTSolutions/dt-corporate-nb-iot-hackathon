/*
 * This demo shows the usage of a RFID reader.
 * 
 * Setup:
 * Connect the Seeed Base Shield to the Tuino1
 * Make sure that the power supply switch of the shield is set to 5V.
 * Connect the RFID reader to the port D4
 * Connect the Tuino1 to your PC
 * Upload this program to the Tuino1
 * Open the serial monitor, configured with 9600 bps 8-N-1
 * 
*/
 
#include <SoftwareSerial.h>
 
/*Connect the RFID reader to D4 on the */
SoftwareSerial SoftSerial(4, 5);
/*buffer array for data receive over serial port*/
unsigned char buffer[64];
/*counter for buffer array*/
int count = 0;
 
void setup()
{
  /*SoftSerial baud rate: 9600*/
  SoftSerial.begin(9600);
  /*Serial port for debugging / result output; baud rate: 9600*/
  Serial.begin(9600);
  Serial.println("tuino_demo_rfid_reader");
}
 
void loop()
{
    /* if date is coming from software serial port ==> data is coming from SoftSerial shield*/
    if (SoftSerial.available())              
    {
        /*read data into char array*/
        while(SoftSerial.available())
        {
            /*writing data into array*/
            buffer[count++] = SoftSerial.read();
            if(count == 64) 
            {
              break;
            }
        }

        /*if no data transmission ends, write buffer to hardware serial port*/
        Serial.write(buffer, count);
        /*call clearBufferArray function to clear the stored data from the array*/
        clearBufferArray();
        /*set counter of while loop to zero*/
        count = 0;
    }

    
    /*if data is available on hardware serial port ==> data is coming from PC or notebook*/
    if (Serial.available())
    {
      /*write it to the SoftSerial shield*/
      SoftSerial.write(Serial.read());
    }
}



void clearBufferArray()                 // function to clear buffer array
{
    // clear all index of array with command NULL
    for (int i=0; i<count; i++)
    {
        buffer[i]=NULL;
    }                  
}


