# Timer0 External Pulse Counter

## Description

This project operates Timer0 as a hardware counter instead of a timer. External pulses applied to RA4/T0CKI increment Timer0, and the lower eight bits of the count are shown in binary on eight LEDs connected to PORTD.

## Hardware

- PIC18F4620
- PICkit 3
- External digital pulse source
- 8 LEDs
- 8 x 330 ohm resistors
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
