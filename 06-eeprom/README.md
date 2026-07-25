# 06 - EEPROM

PIC18F4620 projects focused on the microcontroller's internal nonvolatile data EEPROM.

## Projects

1. EEPROM Read to LEDs
2. EEPROM Write and Readback Verification

## Source Basis

This folder is intentionally kept small because the two Doğan Ibrahim books used for this repository do not contain a large set of standalone internal-EEPROM application projects.

- **EEPROM Read to LEDs** is based directly on Example 4.11 in Section 4.3.1, *Advanced PIC Microcontroller Projects in C*. Ibrahim's example reads addresses 0x00 through 0x2F and sends each byte to an output port.
- **EEPROM Write and Readback Verification** is a self-contained hardware test built directly from the same section's documented `EEPROM_Read` and `EEPROM_Write` examples, including the book's example of writing `0x05` to address `0x2F`.

No unrelated "settings manager", counter, password storage, or other invented EEPROM applications were added simply to increase the number of projects.

## PIC18F4620 Note

The PIC18F4620 contains 1024 bytes of internal data EEPROM. These examples use only addresses 0x0000 through 0x002F.

Circuit diagrams and real breadboard photographs can be added later to each project README.
