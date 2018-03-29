# tuino_demo_nbiot_simple_temperature

Tuino application that demonstrates the usage of a temperature sensor and monitoring of the measured data in the Deutsche Telekom Cloud of Things


## Configuration
* Open “secrets.h” in this project and enter the IMSI of your SIM (line 17) and your password for the MQTT-SN connector (line 18). 
* Download the Arduino Library from [https://github.com/cloud-of-things/dt-arduino-iot-agent] and unpack it to “C:\Users\<username>\Documents\Arduino\libraries”.
* Copy “DTCoTSetup.h” from “C:\Users\<username>\Documents\Arduino\libraries\ dtarduino-iot-agentmaster\examples\test-tuino1-cot-nbiot” to “..\..\src”.

## Setup
* Connect your temperature sensor to the A0 pin of the Tuino  
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Open menu Tools->Serial Monitor of the Arduino IDE.
* Compile and upload the project to the Tuino.

## Connecting to the Deutsche Telekom Cloud of Things (DT CoT)
* Log into your DT CoT account to monitor the data.
* If you need to adjust the language settings, click onto your profile picture in the upper right corner, then onto “Benutzereinstellungen” and select “Deutsch” or “English” under “SPRACHE”.
* Click onto "Device Management“, then navigate to “DEVICES → All devices” on the left side.
* Chose the device with the IMSI corresponding to your SIM card.
* In the “Device Profile” click onto “Measurements”.

## Feature(s)
The application sends the measured temperature data to the DT CoT. You can monitor the trend of the temperature data in the DT CoT and observe the sending procedure also in the serial monitor of the Arduino IDE.