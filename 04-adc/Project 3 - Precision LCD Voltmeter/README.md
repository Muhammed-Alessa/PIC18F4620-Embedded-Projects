# Precision LCD Voltmeter

## Description

This project is the higher-resolution version of the LCD voltmeter. Instead of discarding the fractional part during integer division, the ADC result is scaled with fixed-point arithmetic so the LCD can show millivolts with two decimal places without using floating-point calculations.

## Hardware

- PIC18F4620
- PICkit 3
- 16x2 HD44780-compatible LCD
- 10 kohm potentiometer for LCD contrast
- 10 kohm potentiometer or 0-5 V analog source
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
