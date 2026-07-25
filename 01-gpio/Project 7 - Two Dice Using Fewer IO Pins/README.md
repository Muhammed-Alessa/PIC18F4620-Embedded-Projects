# Two Dice Using Fewer I/O Pins

## Description

This project displays two dice while reducing the number of GPIO pins required for the LEDs. Each dice is represented by four grouped LED control lines, allowing both dice patterns to be driven from a single 8-bit PORTC.

## Hardware

- PIC18F4620
- PICkit 3
- 14 LEDs arranged as two dice
- Current-limiting resistors for the LED groups
- Push button
- 10 kohm pull-up resistor
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
