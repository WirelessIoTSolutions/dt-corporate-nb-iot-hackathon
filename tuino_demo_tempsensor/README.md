# tuino_demo_tempsensor
Tuino application that demonstrates the usage of a temperature sensor.

## Setup
* Connect the temperature sensor with the analog I/O port A0.
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Open menu Tools->Serial Monitor of the Arduino IDE.
* Compile and upload the project to the Tuino.

## Feature(s)
You should see a text output of example program in the serial monitor, i.e. the measured temperature once every second.

## Note
To reduce measuring error the temperature is measured 10 times per second. The average of 10 consecutive measurements is then printed to the serial monitor once every second.
