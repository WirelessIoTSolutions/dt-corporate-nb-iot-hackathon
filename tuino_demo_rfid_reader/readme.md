# tuino_demo_rfid_reader

This readme describes the setup and feature of the Grove 125 kHz RFID reader with a RFID tag.

# Notes

You need a 4 pin male/female jumper to Grove 4 pin conversion cable for the setup because the tuino works with a voltage of 3.3V while the Grove 125kHz RFID reader works with a voltage from 4.75 to 5.25V. Set the jumper of the 125kHz RFID reader to 'U' (left two pins). The setting is: 9600bps, N, 8, 1, TTL output. The output format is Uart. 

# Setup

- Connect one wire from TX to D5
- Connect another one from RX to D4
- Connect GND to GND and Vcc to 5V

# Feature

Place the RFID tag into frame the red square reader. Open the Serial Monitor for the output.
