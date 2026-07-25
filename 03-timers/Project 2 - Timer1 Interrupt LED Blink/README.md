# Timer1 Interrupt LED Blink

## Description

This project uses Timer1 to create a regular time base. Timer1 interrupts every 250 ms, and after two interrupts the program toggles an LED on RD0, producing a visible blink without using Delay_ms in the main loop.

## Hardware

- PIC18F4620
- PICkit 3
- LED
- 330 ohm resistor
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
