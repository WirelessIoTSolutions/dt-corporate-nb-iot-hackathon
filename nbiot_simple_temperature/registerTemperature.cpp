#include "temperature.h"
#include "DTCoT.h"
using namespace DTCoT;

extern CoTCloud cloud;
extern bool successfulRegistered;

int topicId_Temp = MQTTSN_TOPIC_INVALID_ID;

void registerTemperature() {

    if (REGISTER_TEMPERATURE == 1) {

        delay(1000);
      
        /* Registering topic for temperature */
        Serial.println("connected, registering topic for temperature...");
        topicId_Temp = cloud.Mqttsn_RegisterTopic(MQTTSN_TOPIC_MEASUREMENT, MQTTSN_MEAS_TYPE_TEMPERATURE);
        if(topicId_Temp == MQTTSN_TOPIC_INVALID_ID)
        {
          /*TODO topic reg failed, disconnect / restart connect*/
          Serial.println("INVALID MQTTSN_TOPIC_ID");
          successfulRegistered = 0;
          
        }
        else {
          Serial.println("topic registered");
          Serial.print("topicId_Temp: ");
          Serial.println(topicId_Temp);
          successfulRegistered = 1;
        
        }

  
    }

  
}
  /* namespace DTCoT */



