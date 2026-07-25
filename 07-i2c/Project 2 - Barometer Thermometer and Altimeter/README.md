# Barometer, Thermometer and Altimeter

## Description

This project communicates with an LPS331AP MEMS sensor over the PIC18F4620 hardware I2C bus. The program configures the sensor for one-shot measurements, reads its pressure and temperature registers, calculates altitude from the measured pressure, and displays all three values on a 128x64 graphical LCD. The structure and measurement method follow Doğan Ibrahim's Project 7.11.

## Hardware

- PIC18F4620
- PICkit 3
- LPS331AP pressure sensor or breakout module
- 128x64 KS0108-compatible graphical LCD
- 5 kohm potentiometer for GLCD contrast
- I2C pull-up resistors to 3.3 V (10 kohm in Ibrahim's circuit)
- 3.3 V supply for the LPS331AP
- 5 V supply for the PIC18F4620 and GLCD
- 8 MHz crystal
- 2 x 22 pF capacitors

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
