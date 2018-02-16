# tuino_demo_button
Tuino application that demonstrates the usage of a button.

## Setup
* Connect the button with the digital I/O port D4.
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Open menu Tools->Serial Monitor of the Arduino IDE.
* Compile and upload the project to the Tuino.

## Feature(s)
You should see a message of example program in the serial monitor whenever the button is pressed or released. The example program triggers a response to each state change of the button (button released -> pressed and vice versa). The related response is highlighted in the sources for easier adaption of the system's behaviour.

Also the demo shows two different approaches how to deal with button state monitoring:
* Blocking: The program flow stops inside a button read function until the button assumes the desired state. This behaviour is not recommended since it also prevents the execution of other parts of the software system. The blocking example can be found in function setup() and will be executed only once at startup.
* Non-blocking: The button state is being read, then the function will be left immediately. This behaviour is recommended since other parts of the software system can still be executed while monitoring the button state. The non-blocking example can be found in function loop() and will be executed in normal operation.
