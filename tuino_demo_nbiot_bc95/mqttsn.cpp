/**
 * @file mqttsn.h
 * @description Basic setup and function of the MQTT-SN protocol to interact 
 * with the Deutsche Telekom Cloud of things.
 * @author akrause
 * @copyright (C) 2017 mm1 Technology GmbH - all rights reserved. 
 * @licence MIT licence
 * 
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */

#include "gmx_nbiot.h"
#include "mqttsn.h"
#include <string.h>

String mqttsnAuthImsi = "";
int mqttsnMsgId = 1;
/*FIXME might be multiple topics*/
int mqttsnTopicId = 0;




bool Mqttsn_Connect(String imsi, String cotPassword)
{
  /*                     len   type  flags protId duration*/
  char myPayload[255] = {0x00, 0x04, 0x04, 0x01, 0x03, (char)0x84};
  String remoteIp;
  int myUdpPort;
  int myStrLen;
  byte status;

  Serial.println("Mqttsn_Connect");

  /*reset internal state*/
  mqttsnMsgId = 1;
  mqttsnTopicId = 0;
  mqttsnAuthImsi = imsi;

  //test: gmxNB_ping(udp_remote_addr);
  
  /*protocol header*/
  myStrLen = 6;
  /*IMSI of the SIM card*/
  Serial.println("IMSI: " + imsi);
  myStrLen += sprintf(&(myPayload[myStrLen]), imsi.c_str());
  /*CoT passpword*/
  Serial.println("CoT PW: " + cotPassword);
  myStrLen += sprintf(&(myPayload[myStrLen]), cotPassword.c_str());
  /*FIXME this payload length treatment doesn't work for sizes (>127)!*/
  myPayload[0] = (char)myStrLen;
  
  /*send CONNECT request*/
  gmxNB_TXData(myPayload, myStrLen);
  
  /*wait for CONNACK response*/
  status = gmxNB_RXData(remoteIp, myUdpPort, (byte*)myPayload, myStrLen);
  if( status != GMXNB_OK )
  {
    Serial.println("CoT connection failed.");
  }
  else
  {
    if(myStrLen == 3)
    {
      /*TODO detailled check of content!*/
      Serial.println("CoT connection successful.");
      return true;
    }
    else
    {
      Serial.println("CoT connection failed (bad PW?).");
    }
  }
  return false;
}



int Mqttsn_RegisterTopic(String topic, char valueType)
{
  /*                               len   type  topicId     msgId*/
  char myPayload[255] = {/*FIXME:*/0x00, 0x0A, 0x00, 0x00, (char)(mqttsnMsgId / 256), (char)(mqttsnMsgId % 256)};
  String remoteIp;
  int myUdpPort;
  int myStrLen;
  byte status;

  Serial.println("Mqttsn_RegisterTopic");

  /*protocol header*/
  mqttsnMsgId++;
  myStrLen = 6;
  /*IMSI of the SIM card + topic selection*/
  myStrLen += sprintf(&(myPayload[myStrLen]), ("NBIoT/" + mqttsnAuthImsi + "/" + topic + "/").c_str());
  myPayload[myStrLen] = valueType;
  myStrLen++;
  /*FIXME this payload length treatment doesn't work for sizes (>127)!*/
  myPayload[0] = (char)myStrLen;
  
  /*send REGISTER topic request now*/
  gmxNB_TXData(myPayload, myStrLen);
  
  /*wait for REGACK response*/
  status = gmxNB_RXData(remoteIp, myUdpPort, (byte*)myPayload, myStrLen);
  if( status != GMXNB_OK )
  {
    Serial.println("Err CoT connection failed.");
  }
  else
  {
    if(myStrLen == 7)
    {
      /*TODO detailled check of content!*/
      mqttsnTopicId = myPayload[2] * 256;
      mqttsnTopicId += myPayload[3];
      Serial.println("Got topic id: " + String(mqttsnTopicId));
      return mqttsnTopicId;
    }
    else
    {
      Serial.println("Err unknown topic reg response.");
    }
  }
  return MQTTSN_TOPIC_INVALID_ID;
}



bool Mqttsn_PublishMeasurementData(int topicId, String measuredData)
{
  /*                               len   type  topicId                                        msgId*/
  char myPayload[255] = {/*FIXME:*/0x00, 0x0C, (char)(topicId / 256), (char)(topicId % 256), (char)(mqttsnMsgId / 256), (char)(mqttsnMsgId % 256)};
  String remoteIp;
  int myUdpPort;
  int myStrLen;
  byte status;

  Serial.println("Mqttsn_PublishMeasurementData");

  /*protocol header*/
  mqttsnMsgId++;
  myStrLen = 6;
  /*add measured data*/
  myStrLen += sprintf(&(myPayload[myStrLen]), measuredData.c_str());
  /*FIXME this payload length treatment doesn't work for sizes (>127)!*/
  myPayload[0] = (char)myStrLen;
  
  /*send PUBLISH request now*/
  gmxNB_TXData(myPayload, myStrLen);
  
  /*wait for PUBACK response*/
  status = gmxNB_RXData(remoteIp, myUdpPort, (byte*)myPayload, myStrLen);
  if( status != GMXNB_OK )
  {
    Serial.println("Err CoT connection failed.");
  }
  else
  {
    if(myStrLen == 7)
    {
      /*TODO detailled check of content!*/
      Serial.println("data upload with return code: " + String(myPayload[6]));
      if(myPayload[6] == 0)
      {
        Serial.println("success");
        return true;
      }
    }
    else
    {
      Serial.println("Err invalid PUBACK response.");
    }
  }
  Serial.println("failed.");
  return false;
}




