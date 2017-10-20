/**
 * @file tuino_demo_nbiot_bc95.ino
 * @description Demo to show setup and function of the BC95 NB-IoT 
 * transceiver module.
 * @author akrause
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

#include <string.h>
#include "SoftwareSerial.h"

/*button*/
const int buttonPin = D4;


/*reset pin nbiot module*/
const int resetPin = 7;
/*(software) serial interface that connects to nbiot module*/
SoftwareSerial device(3,2); // rx, tx


/* UDP remote host */
/*TODO modify remote address and port!*/
const String udp_remote_addr = "88.99.84.133";
const String udp_remote_port = "21321";



/* Init for BC95 Module */
void init_BC95() {
  String test = "";
  // Resetting Module
  digitalWrite(resetPin,HIGH);
  Serial.println("RESET MODULE");
  delay(1000);
  digitalWrite(resetPin,LOW);
  delay(5000);

  // Print first AT
  device.println("AT");
  test = device.readString();
  delay(50);
  if (test.indexOf("OK"))
  {
    Serial.println("Device response is: OK");
  }
  else
  {
    while ((test.indexOf("OK") <= 0)) {
      device.println("AT");
      test = device.readString();
      Serial.println("Device response failed... Try again in 1 second");
      delay(1000);
    }
  }
  device.println("AT+CEREG=1");
  Serial.println("AT+CEREG=1");
  delay(1000);
  device.println("AT+CSCON=1");
  Serial.println("AT+CSCON=1");

  Serial.println("Waiting for Network Registration");
  //led_timer.attach(&toggleLed,1);
  //volatile long cnt = 0;
  String str = "";
  device.end();

  while(1) {
    device.begin(9600);
    str = device.readString();
    if(str.length() > 0)
      Serial.println(str);
    int cereg_found = str.indexOf("+CEREG:5");

    if(cereg_found > -1) {
      break;
    }

    if(str.length() > 0)
    {
      str = "";
    }
    device.end();
  }

  Serial.print("Registration Complete\r\n");
  Serial.print("Done\r\n");
  Serial.print("Creating UDP Socket\r\n");
  delay(2000);
  device.print("AT+NSOCR=DGRAM,17," + udp_remote_port + ",1\r\n");
  delay(2000);
  Serial.print("INIT DONE");
  //finishLed = 1;
}



/**
 * @brief This function checks the current state of the button and returns 
 * it immediately. The function does not wait for any specific button state 
 * (non-blocking).
 */
bool isButtonPressed_Nonblocking() {
  return (digitalRead(buttonPin) != 0);
}



/**
 * @brief Initialisation, called once during system startup.
 */
void setup() {
  /*initialise serial debug monitor*/
  Serial.begin(9600);
  Serial.println("NB-IoT Demo");
  
  /*initialise connection to nbiot module*/
  device.begin(9600);
  
  /*Button DigIn configuration*/
  pinMode(buttonPin, INPUT);
  
  /*finally, initialise nbiot module*/
  init_BC95();
}



/**
 * @brief Main code here, to run repeatedly. Avoid blocking code sequences!
 * 
 * The function will be polled (i.e. called in short intervalls). Each time 
 * a button pressure has been detected a packet transmission with the 
 * NB-IoT module will be triggered.
 */
void loop() {
  static bool buttonIsPressed = false;
 
  /*check button function*/
  if(isButtonPressed_Nonblocking() && !buttonIsPressed) {
    /*button press detected (signalised once)*/
    buttonIsPressed = true;
    // Serial.println("Button pressed.");
    
    /*TODO Send something here each time a button has been pressed.*/
    
  }
  else if(!isButtonPressed_Nonblocking() && buttonIsPressed) {
    /*button release detected (signalised once)*/
    buttonIsPressed = false;
    // Serial.println("Button released.");
  }
}
