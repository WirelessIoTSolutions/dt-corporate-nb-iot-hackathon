
#include "temperature.h"

// #define MAX_BUFFER_SZ   64
// unsigned char buffer[MAX_BUFFER_SZ];                // buffer array for data receive over serial port
int count=0;                                        // counter for buffer array
int topicId_Temp = MQTTSN_TOPIC_INVALID_ID;



/*Temperature sensor constants*/
#define TEMPERATURE_SAMPLING    (3)

int tempSensorPin = A0;


/*
float exampleTemp = 25.4;
float exampleVolt = 24.0;
String tmpDirection = "up";
int tmpCounter = 0;
*/



float readTemp() {
  const int B = 4275;                                           // B value of the thermistor
  int sensorRaw = (float)analogRead(tempSensorPin);
  float R = 1023.0 / ((float)sensorRaw) - 1.0;
  float temperature = 1.0 / (log(R) / B + 1 / 298.15) - 273.15; //convert to temperature via datasheet ;

  return temperature;
}




bool registerTemperature(DTCoT::CoTCloud &cloud) {
  bool successfullyRegistered = false;

  /* Registering topic for temperature */
  Serial.println("connected, registering topic for temperature...");
  topicId_Temp = cloud.Mqttsn_RegisterTopic(MQTTSN_TOPIC_MEASUREMENT, MQTTSN_MEAS_TYPE_TEMPERATURE);
  if(topicId_Temp == MQTTSN_TOPIC_INVALID_ID){
    /*TODO topic reg failed, disconnect / restart connect*/
    Serial.println("INVALID MQTTSN_TOPIC_ID");
  }
  else {
    Serial.println("topic registered");
    Serial.print("topicId_Temp: ");
    Serial.println(topicId_Temp);
    successfullyRegistered = true;
  }

  return successfullyRegistered;
}




float sendTemperature(DTCoT::CoTCloud &cloud){

	float current_temperature = 0.0f;
	char examplTempStr[10];

	current_temperature = readTemp();
	dtostrf(current_temperature, 2, 1, examplTempStr);
	Serial.print("### Sending Temperature: ");
	Serial.println(examplTempStr);

	if ( !cloud.publish(topicId_Temp, examplTempStr) ) { // @todo, send integers/reals
		/* TODO: process error here */
	}

	return current_temperature;
}



void checkTemperature() {
  /*ak: left empty for debugging*/
}



#if 0
void checkTemperature() {

      static float temp_temperature = readTemp();
      static int temperature_counts = 0;
      static int firstTempCheck = 0;
      static float lastTempVal = temp_temperature;
      static const float diffThresholdTemp = 5.0f;
      
      // update temperature
      // we sample and make an average of the temperature - since in this demo we use a NTC sensor that fluctuates
      temp_temperature += readTemp();
      DEBUG_PRINT("readTemp(): %2.2f\n", readTemp());
      temperature_counts++;
    
      if ( temperature_counts >= TEMPERATURE_SAMPLING ) {
        current_temperature = temp_temperature / TEMPERATURE_SAMPLING;
        temperature_counts = 0;
        temp_temperature = 0;
    
        dtostrf(current_temperature, 2, 1, examplTempStr);
         //Serial.print("### Updating Temperature on OLED: ");
         //Serial.println(examplTempStr);
        //char tmpStr[10];
        //sprintf(tmpStr, "%i", currLight);
        updateValuesOLED(OLED_LIST_TEMP, examplTempStr);
         //SeeedOled.setTextXY(4, 6);
         //SeeedOled.putString(examplTempStr);

         if(firstTempCheck == 0) {
            sendTemperature();
            firstTempCheck = 1;
         }

         /* check if the change is greater than diffThreshold, if yes send update immediattely */
        if((current_temperature > lastTempVal) && ((current_temperature - lastTempVal) > diffThresholdTemp)) {
      
          sendTemperature();
          
        }
        else if((current_temperature < lastTempVal) && ((lastTempVal- current_temperature) > diffThresholdTemp)) {
          sendTemperature();
        }
        
        lastTempVal = current_temperature;

         
  
  }
}
#endif /*0*/



#if 0
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
#endif /*0*/


