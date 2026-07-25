# External Interrupt Event Counter

## Description

This project counts external events using INT0 on RB0 and shows the count on a four-digit 7-segment display. The event count is updated by the external interrupt while Timer0 interrupts refresh the multiplexed display independently.

## Hardware

- PIC18F4620
- PICkit 3
- 4-digit common-cathode 7-segment display
- 7 x 330 ohm segment resistors
- 4 NPN transistors for digit switching
- 4 transistor base resistors
- Digital pulse source for INT0
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
