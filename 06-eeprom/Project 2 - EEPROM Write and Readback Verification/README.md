# EEPROM Write and Readback Verification

## Description

This project demonstrates both writing to and reading from the PIC18F4620 internal EEPROM. The value 0x05 is stored at address 0x002F, read back, and displayed on eight LEDs connected to PORTD. Before writing, the program checks the existing value so unnecessary EEPROM write cycles are avoided.

## Hardware

- PIC18F4620
- PICkit 3
- 8 LEDs
- 8 x 330 ohm resistors
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
