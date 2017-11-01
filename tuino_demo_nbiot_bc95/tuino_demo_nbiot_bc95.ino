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
#include "gmx_nbiot.h"


/* UDP remote host */
/*TODO modify remote address and port!*/
// const String udp_remote_addr = "88.99.84.133";
// const String udp_remote_port = "21321";


/* Init for BC95 Module */
void init_BC95() {
  String version;
  byte join_status;
  int join_wait=0;

  Serial.println("Starting");

  // Init NB IoT board
  gmxNB_init("1.1.1.1","9200",NULL);

  gmxNB_getVersion(version);
  Serial.println("GMXNB Version:"+version);

  gmxNB_getIMEI(version);
  Serial.println("GMXNB IMEI:"+version);

  gmxNB_startDT(); 

  while((join_status = gmxNB_isNetworkJoined()) != NB_NETWORK_JOINED) {
    gmxNB_Led2(GMXNB_LED_ON);
    delay(500);
    gmxNB_Led2(GMXNB_LED_OFF);
    Serial.print("Waiting to connect:");
    Serial.println(join_wait);
    join_wait++;
    
    delay(2500);  
  }
  
  Serial.println("Connected!!!");
  gmxNB_Led2(GMXNB_LED_ON);
}




/**
 * @brief Initialisation, called once during system startup.
 */
void setup() {
  /*initialise serial debug monitor*/
  Serial.begin(9600);
  Serial.println("NB-IoT Demo");
  
  /*initialise connection to nbiot module*/
  // device.begin(9600);
  
  /*Button DigIn configuration*/
  // pinMode(buttonPin, INPUT);
  
  /*finally, initialise nbiot module*/
  init_BC95();
  Serial.println("setup finished.");
}



/**
 * @brief Main code here, to run repeatedly. Avoid blocking code sequences!
 * 
 * The function will be polled (i.e. called in short intervalls). Each time 
 * a button pressure has been detected a packet transmission with the 
 * NB-IoT module will be triggered.
 */
void loop() {
  static long int timer_period_to_tx = 20000;
  static long int timer_millis_tx = 0;
  long int delta_tx = millis() - timer_millis_tx;

  if ( delta_tx > timer_period_to_tx) {
    Serial.println("TX DATA");
    gmxNB_TXData("313233");
   
    timer_millis_tx = millis();

    // flash LED
    gmxNB_Led3(GMXNB_LED_ON);
    delay(200);
    gmxNB_Led3(GMXNB_LED_OFF);
    
   }

  
  
#if 0  
  String test = "";

  // Serial.write("x");

  if(Serial.available())
  {
    // Serial.write("x");
    // test = Serial.read();
    test = Serial.readString();
    // delay(50);
    Serial.println(test.c_str());
    device.println(test.c_str());
    
    // device.write(Serial.read());
  }
  if(device.available())
  {
    Serial.print("z");
    test = device.readString();
    // Serial.print(device.read());
    // Serial.println(device.readString());
    Serial.println(test.c_str());
  }
#endif /*0*/
}
