/**
 * @file nbito_simple_temperature.ino
 * @description Demo to show TUINO button setup and function.
 * @author julia heydecke
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
**/


#include "secrets.h"
#include "temperature.h"



const unsigned char ON_BOARD_LED = 13;
const char* CLOUD_COUNTER_VAR_NAME = "cloud-counter";
const unsigned char COUNTER_THRESHOLD = 0xFF;
const unsigned short CLOUD_SERVER_PORT = 1883;


char examplTempStr[10];
bool successfulRegistered = false;
int tempSensorPin = A0;
float current_temperature = 0.0f;

/*Temperature sensor constants*/
#define TEMPERATURE_SAMPLING    (10)

using namespace DTCoT;

CoTConfigDeviceGimasi devConfig 
  = CoTConfigDeviceGimasi(NB_IOT_SERVER_IP
    , NB_IOT_SERVER_PORT, NB_IOT_IMSI, NB_IOT_COT_PWD, Serial1, GMX_RESET);

CoTDeviceGimasi device = CoTDeviceGimasi(devConfig);

CoTConfigCommunicationMQTTSN mqttsnConfig(NB_IOT_SERVER_IP
    , NB_IOT_SERVER_PORT
    , NB_IOT_IMSI
    , NB_IOT_COT_PWD
    );

CoTCloud cloud( 
  /* Configure communcation settings of your DT Cloud-enabled device */
    device // @todo - why do these need to be instantiated individually? Is it creating them on the stack?
  
  /* Setup the cloud communication method */ 
  , mqttsnConfig
);



float readTemp() {
  const int B = 4275;                                           // B value of the thermistor
  int sensorRaw = (float)analogRead(tempSensorPin);
  float R = 1023.0 / ((float)sensorRaw) - 1.0;
  float temperature = 1.0 / (log(R) / B + 1 / 298.15) - 273.15; //convert to temperature via datasheet ;

  return temperature;
}


void setup() {
  /*serial debug output*/
  Serial.begin(9600);
  Serial.println("Temperature Sensor Demo");
  // Init Temperature
  current_temperature = readTemp();

  registerTemperature();

  if(successfulRegistered == 1) {
    Serial.println("Connected      ");
  }
  else {
    Serial.println("Error          ");
  }
}



void loop() {
  static float temp_temperature = 0.0f;
  static int temperature_counts = 0;

  temp_temperature += readTemp();
  temperature_counts++;

  if ( temperature_counts >= TEMPERATURE_SAMPLING ) {
    current_temperature = temp_temperature / TEMPERATURE_SAMPLING;
    temperature_counts = 0;
    temp_temperature = 0;
  }
    
  // CoT-Version
  Serial.println("Sending information to Cloud of Things...");
  Serial.println(current_temperature);
  sendTemperature();
   
  delay(1000);
}

