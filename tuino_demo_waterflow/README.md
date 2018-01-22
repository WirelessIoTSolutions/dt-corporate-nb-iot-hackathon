# tuino_demo_waterflow
Tuino application that demonstrates the usage of a water flow sensor.

You will need Seeeduino / Arduino ,Water Flow Sensor,10K resistor,a breadboard and some jumper wires.

## Setup
* Connect the black wire to the Tuino´s ground pin.
* Connect the red wire to the Tuino´s 5V pin.
* Connect the yellow wire to a 10k pull up resistor and then           to pin 2 on the Tuino.
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Open menu Tools->Serial Monitor of the Arduino IDE.
* Compile and upload the project to the Tuino.

## Feature(s)
You should see a text output of example program in the serial monitor, i.e. the water flow rate once every second.
