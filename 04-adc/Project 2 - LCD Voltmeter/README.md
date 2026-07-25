# LCD Voltmeter

## Description

This project measures a 0 to 5 V analog signal on AN0 using the PIC18F4620 10-bit ADC. The converted value is scaled to millivolts and updated once per second on a 16x2 LCD.

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
