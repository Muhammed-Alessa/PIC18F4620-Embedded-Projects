# LM35 Digital Thermometer

## Description

This project uses an LM35DZ analog temperature sensor connected to AN0. The PIC18F4620 converts the sensor voltage with its ADC and displays the measured temperature on a 16x2 LCD, using the LM35 scale factor of 10 mV per degree Celsius.

## Hardware

- PIC18F4620
- PICkit 3
- LM35DZ temperature sensor
- 16x2 HD44780-compatible LCD
- 10 kohm potentiometer for LCD contrast
- 8 MHz crystal
- 2 x 22 pF capacitors
- 5 V power supply

## Code

See [main.c](main.c).

## Circuit

<!-- Add your circuit diagram and real breadboard photo here. -->
