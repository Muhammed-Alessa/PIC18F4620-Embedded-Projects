# Frequency Counter with LCD

## Description

This project measures the frequency of an external digital signal. Timer0 counts pulses arriving at RA4/T0CKI while Timer1 creates a one-second measurement window, after which the pulse count is displayed in hertz on a 16x2 LCD.

## Hardware

- PIC18F4620
- PICkit 3
- 16x2 HD44780-compatible LCD
- External digital signal source
- 10 kohm potentiometer for LCD contrast
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
