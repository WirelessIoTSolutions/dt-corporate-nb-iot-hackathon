# tuino_demo_gps
Tuino application that demonstrates the usage of the GPS module.

## Setup
* Connect the GPS module with the digital I/O port D4.
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Open menu Tools->Serial Monitor of the Arduino IDE.
* Compile and upload the project to the Tuino.
* You should now see the output of the GPS module on the serial monitor every second.
* You should also be able able to issue commands to the GPS module via the serial monitor.

## Feature(s)
This project provides an example of:
* how to configure the Tuino to connect a GPS module 
* basic I/O functions to communicate with the GPS module using a software emulated serial interface.

## Note
Usually the Grove GPS module doesn't provide valid GPS data during the first few minutes. For this time you get the message "Invalid GPS data:...". After that the output includes raw GPS data, the coordinates of your position (latitude, longitude), and the coordinates encoded to a MQTT-SN payload.

