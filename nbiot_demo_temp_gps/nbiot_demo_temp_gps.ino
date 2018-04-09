/** NB-IoT-test-lm1

   Objective:
   This project demonstrates how simple it is to build a DTCoT application

   This example also shows that DTCoT does not depend on device type,
   network and protocol libraies, and can be easily extended by adding more
   devices and underlaying protocols (as soon as the cloud starts supporting them).

   Application description:
   A variety of sensors are connected to the DT CoT and values will be pushed regulary 
   or if severe value changes are detected to the DT CoT
 */

#include "secrets.h"
#include "DTCoT.h"
#include <Wire.h>
#include "SeeedOLED.h"
#include "gps.h"
#include "temperature.h"
#include "MAX17048.h"

/*
#define REGISTER_TEMPERATURE    1
#define REGISTER_GPS            1
 */


#define OLED_LIST_TEMP		0
#define OLED_LIST_LIGHT		1 
#define OLED_LIST_DISTANCE	2
#define OLED_LIST_GPS		3
#define OLED_LIST_VOLTAGE	4
#define OLED_LIST_MAX		5
#define OLED_LIST_MAX_CHAR	15

MAX17048 batteryMonitor;

/* Application-specific settings */
const unsigned char onBoardLed = 13;
const char* cloudCounterVarName = "cloud-counter";
const unsigned char counterThreshold = 0xFF;
static int sleepTime = 10000; /* in milliseconds */ 



char examplVoltStr[10];
char examplLightStr[10];
char examplDistanceStr[10];
float cellVoltage;
float stateOfCharge;
bool successfullyRegistered = true;



enum MeasurementTypeId {
	TempMeasurement = 0,
	GPSMeasurement,
	NoMeasurement,
	MaxMeasurementId,
};



using namespace DTCoT;

CoTConfigDeviceGimasi devConfig 
= CoTConfigDeviceGimasi(
		NB_IOT_SERVER_IP, 
		NB_IOT_SERVER_PORT, 
		NB_IOT_IMSI, 
		NB_IOT_COT_PWD, 
		Serial1, 
		GMX_RESET
);

CoTDeviceGimasi device = CoTDeviceGimasi(devConfig);

CoTConfigCommunicationMQTTSN mqttsnConfig(
		NB_IOT_SERVER_IP, 
		NB_IOT_SERVER_PORT, 
		NB_IOT_IMSI, 
		NB_IOT_COT_PWD
);

CoTCloud cloud( 
		/* Configure communcation settings of your DT Cloud-enabled device */
		device, // @todo - why do these need to be instantiated individually? Is it creating them on the stack?

		/* Setup the cloud communication method */ 
		mqttsnConfig
);



void onCounterValueChanged( void* newCounterValue) {
	/* TODO: parameter NULL check
     TODO: casting outcome check
     TODO: provide helper-macro for easy app-specific casting
     TODO: figure out how to avoid casting for different payload types
	 */
	unsigned long counterValue = *(static_cast< unsigned long*>(newCounterValue) );

	if ( counterValue >= counterThreshold) {
		digitalWrite( onBoardLed, HIGH);
	}
	else {
		digitalWrite( onBoardLed, LOW);
	}
}




/*********************************************/
/*************   SETUP     *******************/
/*********************************************/
void setup() {
	delay(100);
	Serial.begin(115200);
	delay(100);

	/*init I2C (to access OLED display)*/
	Wire.begin();

	/*now init OLED*/
	SeeedOled.init();               //initialze SEEED OLED display
	SeeedOled.clearDisplay();       //clear the screen and set start position to top left corner
	SeeedOled.setNormalDisplay();   //Set display to normal mode (i.e non-inverse mode)
	SeeedOled.setHorizontalMode();  //Set addressing mode to Page Mode

	/*put the text on the display that never change:*/
	SeeedOled.setTextXY(0, 0);
	SeeedOled.putString("mm1T NB-IoT Demo");
	SeeedOled.setTextXY(2, 0);
	SeeedOled.putString("Offline");
	SeeedOled.setTextXY(4, 0);
	SeeedOled.putString("Temp: ");
	DEBUG_PRINT("Setup...");

	//batteryMonitor init
	batteryMonitor.reset();
	batteryMonitor.quickStart();

	delay(1000);

	// @todo - why is device const? Can't call it ffrom with CoTCloud
	device.init();

	DEBUG_PRINT("Setup...");
	SeeedOled.setTextXY(2, 0);
	SeeedOled.putString("Connecting...");
	cloud.init();


	/* Subscribe to the change of a cloud variable of interest */
	cloud.subscribe( cloudCounterVarName, onCounterValueChanged); // @todo implement

	SeeedOled.setTextXY(2, 0);
	SeeedOled.putString("Registering...");

	successfullyRegistered = successfullyRegistered && registerTemperature(cloud);
	successfullyRegistered = successfullyRegistered && registerGPS(cloud);

	if(successfullyRegistered) 
	{
		SeeedOled.setTextXY(2, 0);
		SeeedOled.putString("Connected      ");
	}
	else 
	{
		SeeedOled.setTextXY(2, 0);
		SeeedOled.putString("Error          ");
	}

	//send values one time after setup
	/*
	sendGPS();
	sendLight();
	sendVoltage();
	sendDistance(ultrasonic.MeasureInCentimeters());
	*/
}




/*********************************************/
/*************    LOOP     *******************/
/*********************************************/
void loop() 
{
	static MeasurementTypeId nextMeasurementId = TempMeasurement;
	float myTemperature = 0.0f;
	char tmpstr[16];

	
	DEBUG_PRINT_INFO("Loop");
	
	/**************************/
	switch (nextMeasurementId)
	{
	case TempMeasurement:
		Serial.println("Sending information to Cloud of Things...");

		/* sending temperature / updating display*/
		checkTemperature();
		SeeedOled.setTextXY(2, 0);
		SeeedOled.putString("Sending Temp   ");
		myTemperature = sendTemperature(cloud);
		// updateValuesOLED(OLED_LIST_TEMP, tmpstr);
		dtostrf(myTemperature, 2, 1, tmpstr);
		SeeedOled.setTextXY(4, 6);
		SeeedOled.putString(tmpstr);

		nextMeasurementId = GPSMeasurement;
		break;
		
	case GPSMeasurement:
		Serial.println("Sending information to Cloud of Things...");

		/* sending GPS coords / updating display*/
		checkGPS();
		SeeedOled.setTextXY(2, 0);
		SeeedOled.putString("Sending GPS    ");
		if(sendGPS(cloud))
		{
			updateValuesOLED(OLED_LIST_GPS, "valid");
		}
		else
		{
			updateValuesOLED(OLED_LIST_GPS, " not valid");	
		}

		nextMeasurementId = NoMeasurement;
		break;
		
	default:
		Serial.println("wait cycle");
		/*sleep a while after all measurements were sent*/
		SeeedOled.setTextXY(2, 0);
		SeeedOled.putString("Connected       ");
		delay(sleepTime);
		nextMeasurementId = TempMeasurement;
		return;
	}
}

