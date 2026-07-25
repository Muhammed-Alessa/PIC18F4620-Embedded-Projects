# EEPROM Read to LEDs

## Description

This project reads the PIC18F4620 internal data EEPROM from address 0x0000 through 0x002F. Each stored byte is displayed in binary on eight LEDs connected to PORTD, allowing the EEPROM contents to be observed directly on the hardware.

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
