# tuino_demo_rfid_reader_wiegand

Tuino application for the use of the 125 kHz rfid_reader in wiegand mode.

# Notes

You have to use Grove 4 pin male/female jumper to Grove 4 pin conversion cable for this project. The tuino has a voltage of 3.3V while the 125kHz RFID reader has 5V. The output format ist Wiegand.

# Setup

 - Connect one wire from TX to D3.
 - Connect another one from RX to D2.
 - Connect one wire from GND to GND and another one from Vcc to 5V.

# Feature(s)
Place the RFID-tag on the frame of the red square reader.  On the serial monitor you should see the output. It is formatted with 26bits including 24bits card info and 2 bits parity.

