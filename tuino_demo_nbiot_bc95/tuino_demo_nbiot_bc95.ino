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
#include "mqttsn.h"


/* UDP remote host / CoT MQTTSN service*/
const String udp_remote_addr  = "172.25.102.151";
const int udp_remote_port     = 1883;

/*CoT access parameters*/
String myImsi                 = "901405800006245";
String myCotPassword          = "DWKdkVT8";

int myMqttsnTopicId = MQTTSN_TOPIC_INVALID_ID;



/* Init for BC95 Module */
void init_BC95() {
  String version;
  byte join_status;
  int join_wait=0;

  Serial.println("Starting");

  // Init NB IoT board
  gmxNB_init(udp_remote_addr, udp_remote_port, NULL);

  // gmxNB_getVersion(version);
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
  // gmxNB_startDT();
  Serial.println("setup finished.");

  /*attempt connecting to CoT*/
  if (Mqttsn_Connect(myImsi, myCotPassword) == false)
  {
    /*TODO connect failed, restart*/
    return;
  }

  Serial.println("connected, registering topic...");
  myMqttsnTopicId = Mqttsn_RegisterTopic(MQTTSN_TOPIC_MEASUREMENT, MQTTSN_MEAS_TYPE_TEMPERATURE);
  if(myMqttsnTopicId == MQTTSN_TOPIC_INVALID_ID)
  {
    /*TODO topic reg failed, disconnect / restart connect*/
    return;
  }

  Serial.println("topic registered, uploading data...");
  if(Mqttsn_PublishMeasurementData(myMqttsnTopicId, "25.4") == false)
  {
    /*TODO data upload failed, disconnect / restart connect*/
    return;
  }

}




/**
 * @brief Main code here, to run repeatedly. Avoid blocking code sequences!
 * 
 * The function will be polled (i.e. called in short intervalls). Each time 
 * a button pressure has been detected a packet transmission with the 
 * NB-IoT module will be triggered.
 */
void loop() {
  String test = "";

  if(Serial.available())
  {
    test = Serial.readString();
    Serial.println(test.c_str());
    Serial1.println(test.c_str());
  }


  if(Serial1.available())
  {
    test = Serial1.readString();
    Serial.println(test.c_str()); 
  }
}


