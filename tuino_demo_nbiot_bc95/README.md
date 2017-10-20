# tuino_demo_nbiot_bc95
Tuino application that demonstrates the basic NB-IoT communication with QUECTEL BC95.

## NB-IoT
**Narrowband Internet of Things** is a low cost approach to use cellular networks for mobile data communication with low datarates. 

## Quectel BC95
The Quectel BC95 is a NB-IoT module that provides an IP stack on top of NB-IoT. Data communication functions of the module to send and receive data are accessible via a set of AT commands. Only UDP is supported as transport protocol. An apropriate SIM card is required to access a carrier's NB-IoT services.

## Setup
* Connect the button with the digital I/O port D4.
* Plug in the NB-IoT module onto the apropriate pin row.
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Open menu Tools->Serial Monitor of the Arduino IDE.
* Compile and upload the project to the Tuino.

## Features
The demo shows how to send and receive data to/from a remote UDP/IPv4 host using NB-IoT.

## Notes
