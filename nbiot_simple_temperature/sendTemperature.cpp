#include "temperature.h"

extern float current_temperature;
extern char examplTempStr[];
extern int topicId_Temp;

using namespace DTCoT;

extern CoTCloud cloud;

void sendTemperature() {
    
         if(REGISTER_TEMPERATURE == 1) {

            dtostrf(current_temperature, 2, 1, examplTempStr);
            Serial.print("### Sending Temperature: ");
            Serial.println(examplTempStr);
    
            if ( !cloud.process() ) {
    
            if ( !cloud.publish(topicId_Temp, examplTempStr) ) { // @todo, send integers/reals
                /* TODO: process error here */
                }
               }
          
         }
  
}
/* namespace DTCoT */


