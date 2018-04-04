# tuino_demo_heat_monitor

Tuino application that demonstrates the usage of a OLED display to monitor the temperature measured with a temperature sensor and the status of a window (simulated by a button)

## Setup
* Connect the temperature sensor with the analog port A0 of the Tuino.
* Connect the button with the digital I/O port D4 of the Tuino.
* Connect the OLED display with the I2C interface of the Tuino.
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Open menu Tools->Serial Monitor of the Arduino IDE.
* Compile and upload the project to the Tuino.
* Press the button to set a window status to "closed".

## Feature(s)

* You should see a current temperature in the serial monitor.
* At the OLED display, you should see the output such as:
```
HEAT MONITOR
temp.:      warm
window:   opened
currently:    21
```

 * The temperature is graded with "cold" if it is lower than 17 degrees (Celsius), otherwise  "temp.:   warm" is shown at the display
 * A pressed/unpressed button simulates a closed/opened window.