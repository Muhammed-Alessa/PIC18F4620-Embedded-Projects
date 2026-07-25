# Four-Digit Multiplexed 7-Segment

## Description

This project expands multiplexing to four common-cathode 7-segment digits. PORTD carries the segment data and RA0 through RA3 select the digits one at a time, so the value 1234 appears as a steady four-digit number.

## Hardware

- PIC18F4620
- PICkit 3
- 4-digit common-cathode 7-segment display
- 7 x 330 ohm resistors
- 4 NPN transistors for digit switching
- 4 transistor base resistors
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
gf