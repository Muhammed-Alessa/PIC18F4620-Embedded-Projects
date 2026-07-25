# LPS331AP I2C Device Identification

## Description

This project performs a focused I2C bring-up test with the LPS331AP pressure sensor. The PIC18F4620 initializes the sensor through the hardware MSSP I2C interface, reads the WHO_AM_I register, and indicates whether the expected device ID was received. The test is taken directly from the initialization sequence used in Doğan Ibrahim's LPS331AP project.

## Hardware

- PIC18F4620
- PICkit 3
- LPS331AP pressure sensor or breakout module
- 2 LEDs
- 2 x 330 ohm resistors
- I2C pull-up resistors to 3.3 V (10 kohm in Ibrahim's circuit)
- 3.3 V supply for the LPS331AP
- 5 V supply for the PIC18F4620
- 8 MHz crystal
- 2 x 22 pF capacitors

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
