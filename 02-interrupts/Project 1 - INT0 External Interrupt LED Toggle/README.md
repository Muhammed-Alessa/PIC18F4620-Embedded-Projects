# INT0 External Interrupt LED Toggle

## Description

This project uses the PIC18F4620 INT0 external interrupt input on RB0. A rising edge on INT0 immediately triggers an interrupt service routine, which toggles an LED connected to RD0.

## Hardware

- PIC18F4620
- PICkit 3
- Push button or digital pulse source
- 10 kohm resistor
- LED
- 330 ohm resistor
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
