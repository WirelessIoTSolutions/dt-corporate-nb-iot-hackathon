# tuino_demo_led_relay
Tuino application that demonstrates the usage of a digital output, e.g. LEDs or 
relay.

## Setup
* Connect the LED (or the relay) with the digital I/O port D5.
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Open menu Tools->Serial Monitor of the Arduino IDE.
* Compile and upload the project to the Tuino.
* You should now see the LED blink in a 1 second interval.

## Feature(s)
This project provides an example of:
* how to write on a digital output.
* a very basic state machine with 2 internal states which are both indicated by the LED. A state change is triggered at each call of the function poll().

## Note
The example uses long term blocking delays which are generally discouraged, since they potentially also prevent other parts of the software system from execution. However, blocking functions are used here in favour of a clear and simple example.
