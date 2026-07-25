# 07 - I2C

PIC18F4620 projects focused on the hardware MSSP module operating as an I2C master.

## Projects

1. LPS331AP I2C Device Identification
2. Barometer, Thermometer and Altimeter

## Source Basis

This folder is intentionally limited to I2C work that is directly supported by the two Doğan Ibrahim books used for this repository.

The main source is **Project 7.11 - Barometer, Thermometer and Altimeter Display on a GLCD** from *PIC Microcontroller Projects in C: Basic to Advanced*. That project connects an LPS331AP sensor to the PIC through I2C, initializes the bus at 100 kHz, performs register reads and writes, checks the sensor identity, reads pressure and temperature, and calculates altitude.

- **LPS331AP I2C Device Identification** is a focused hardware bring-up exercise extracted from the initialization sequence of Project 7.11. It verifies the I2C link by reading the sensor's `WHO_AM_I` register.
- **Barometer, Thermometer and Altimeter** is the complete I2C sensor application based on Project 7.11.

The PIC18F4620 has one MSSP module. In I2C mode it uses:

- RC3 / SCL
- RC4 / SDA

The source descriptions are paraphrased and the programs are rewritten for the PIC18F4620 and mikroC PRO for PIC.

## Why the RTC Projects Are Not Here

Doğan Ibrahim's PCF8583 real-time-clock and alarm-clock projects also use I2C. They are intentionally reserved for the repository's `10-rtc` folder so the same complete projects are not duplicated in two categories.

No unrelated 24Cxx EEPROM, port-expander, OLED, or generic I2C examples were added because they are not projects from the two Ibrahim books selected for this repository.

Circuit diagrams and real breadboard photographs can be added later to each project README.
