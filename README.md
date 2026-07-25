# \# PIC18F4620 Embedded Projects

# 

# A collection of embedded systems experiments and practical projects built around the \*\*Microchip PIC18F4620\*\* microcontroller.

# 

# The purpose of this repository is to document my progress with PIC18 microcontrollers and demonstrate practical understanding of:

# 

# \* GPIO

# \* External interrupts

# \* Interrupt priorities

# \* Timers

# \* ADC

# \* PWM / CCP

# \* EEPROM

# \* I2C

# \* SPI

# \* LCD interfacing

# \* RTC devices

# \* SD cards

# \* Embedded system design

# 

# The projects are developed primarily using \*\*mikroC PRO for PIC\*\*, with selected examples implemented directly through PIC18 hardware registers to demonstrate an understanding of the underlying microcontroller peripherals.

# 

# \---

# 

# \## Development Hardware

# 

# | Component            | Device     |

# | -------------------- | ---------- |

# | Microcontroller      | PIC18F4620 |

# | Programmer           | PICkit 3   |

# | Development platform | Breadboard |

# | Logic voltage        | 5 V        |

# | Language             | C          |

# 

# Depending on the experiment, additional components such as LCDs, sensors, potentiometers, EEPROMs, RTC modules, MOSFETs, motors, and SD cards are used.

# 

# \---

# 

# \## Development Software

# 

# \* mikroC PRO for PIC 7.6.0

# \* Microchip PICkit 3

# \* MPLAB IPE when required for programming/debugging

# \* Git and GitHub for version control and documentation

# 

# \---

# 

# \## Repository Structure

# 

# ```text

# PIC18F4620-Embedded-Projects/

# │

# ├── README.md

# ├── LICENSE

# ├── docs/

# │

# ├── 01-gpio/

# ├── 02-interrupts/

# ├── 03-timers/

# ├── 04-adc/

# ├── 05-pwm/

# ├── 06-eeprom/

# ├── 07-i2c/

# ├── 08-spi/

# ├── 09-lcd/

# ├── 10-rtc/

# ├── 11-sd-card/

# │

# ├── bare-metal/

# │

# └── projects/

# ```

# 

# The repository is divided into three main areas:

# 

# \### Peripheral Experiments

# 

# Small experiments focused on understanding individual PIC18 peripherals.

# 

# Examples include GPIO, timers, interrupts, ADC, PWM, EEPROM, I2C, and SPI.

# 

# \### Bare-Metal Experiments

# 

# Selected peripherals are configured directly through PIC18 registers rather than relying entirely on high-level library functions.

# 

# These examples demonstrate familiarity with the PIC18F4620 datasheet, register configuration, flags, peripheral control bits, and hardware operation.

# 

# \### Complete Projects

# 

# Larger projects combine several peripherals into complete embedded systems.

# 

# \---

# 

# \# Peripheral Experiments

# 

# \## 01 — GPIO

# 

# Topics:

# 

# \* Digital outputs

# \* Digital inputs

# \* `TRISx`

# \* `PORTx`

# \* `LATx`

# \* Push buttons

# \* LEDs

# 

# Projects:

# 

# \* LED blink

# \* Button input

# \* Multiple outputs

# \* Register-level GPIO

# 

# \---

# 

# \## 02 — Interrupts

# 

# Topics:

# 

# \* External interrupts

# \* INT0

# \* INT1

# \* Interrupt flags

# \* Interrupt enable bits

# \* Global interrupt enable

# \* Rising/falling edge selection

# \* High/low priority interrupts

# 

# Projects:

# 

# \* INT0 button interrupt

# \* INT1 external interrupt

# \* High-priority interrupt

# \* High/low priority example

# 

# \---

# 

# \## 03 — Timers

# 

# Topics:

# 

# \* Timer0

# \* Timer1

# \* Prescalers

# \* Timer preload

# \* Overflow

# \* Timer interrupts

# \* Time calculations

# 

# Projects:

# 

# \* Timer-based LED blink

# \* Timer interrupt

# \* Hardware counter

# \* Periodic event generation

# 

# \---

# 

# \## 04 — ADC

# 

# Topics:

# 

# \* Analog inputs

# \* ADC channels

# \* ADC resolution

# \* Reference voltage

# \* Analog/digital pin configuration

# \* ADC result conversion

# 

# Projects:

# 

# \* Potentiometer reader

# \* Voltage measurement

# \* ADC with LCD output

# 

# \---

# 

# \## 05 — PWM / CCP

# 

# Topics:

# 

# \* CCP modules

# \* PWM frequency

# \* Duty cycle

# \* Timer2

# \* Output control

# 

# Projects:

# 

# \* LED dimmer

# \* Potentiometer-controlled PWM

# \* DC motor speed controller

# 

# \---

# 

# \## 06 — EEPROM

# 

# Topics:

# 

# \* Internal EEPROM

# \* Reading data

# \* Writing data

# \* Persistent settings

# 

# Projects:

# 

# \* Save configuration

# \* Store user settings

# \* Restore values after power loss

# 

# \---

# 

# \## 07 — I2C

# 

# Topics:

# 

# \* I2C master operation

# \* Device addressing

# \* Reading

# \* Writing

# \* External peripherals

# 

# Possible projects:

# 

# \* External EEPROM

# \* RTC

# \* I2C sensor

# 

# \---

# 

# \## 08 — SPI

# 

# Topics:

# 

# \* SPI master operation

# \* Clock generation

# \* Data transmission

# \* Device selection

# \* Peripheral communication

# 

# Possible projects:

# 

# \* SPI sensor

# \* External memory

# \* SD card interface

# 

# \---

# 

# \## 09 — LCD

# 

# Topics:

# 

# \* 16×2 character LCD

# \* Commands

# \* Character output

# \* Numeric values

# \* Display formatting

# 

# Projects:

# 

# \* Hello-world display

# \* ADC display

# \* Measurement interface

# 

# \---

# 

# \## 10 — RTC

# 

# Topics:

# 

# \* Real-time clocks

# \* I2C communication

# \* BCD conversion

# \* Date/time handling

# 

# Possible devices:

# 

# \* DS1307

# \* DS3231

# 

# \---

# 

# \## 11 — SD Card

# 

# Topics:

# 

# \* SPI communication

# \* Data storage

# \* File handling

# \* Data logging

# 

# Possible project:

# 

# \* Sensor data logger

# 

# \---

# 

# \# Bare-Metal PIC18 Experiments

# 

# The `bare-metal/` directory contains examples where peripherals are configured directly using PIC18F4620 registers.

# 

# Examples:

# 

# ```text

# bare-metal/

# ├── gpio-registers/

# ├── interrupt-registers/

# ├── timer0-registers/

# ├── adc-registers/

# └── pwm-registers/

# ```

# 

# These examples focus on registers such as:

# 

# ```text

# TRISA / TRISB / TRISC / TRISD

# PORTx

# LATx

# INTCON

# INTCON2

# INTCON3

# T0CON

# T1CON

# ADCON0

# ADCON1

# ADCON2

# CCP1CON

# CCPR1L

# T2CON

# ```

# 

# The goal is not to avoid libraries completely.

# 

# Libraries are useful for application development, but understanding the registers underneath them is important when debugging hardware, reading datasheets, implementing unsupported functionality, or optimizing a design.

# 

# \---

# 

# \# Complete Projects

# 

# The `projects/` directory contains larger applications combining multiple PIC18 peripherals.

# 

# Planned and completed projects may include:

# 

# | Project                    | Main Features                 |

# | -------------------------- | ----------------------------- |

# | Digital Voltmeter          | ADC + LCD                     |

# | PWM Motor Controller       | ADC + PWM + MOSFET            |

# | Temperature Controller     | ADC + PWM + LCD               |

# | RTC Clock                  | I2C + RTC + LCD               |

# | Data Logger                | ADC + SPI + SD Card           |

# | Embedded Monitoring System | ADC + LCD + RTC + EEPROM + SD |

# 

# \---

# 

# \# Example Hardware Flow

# 

# A typical project may look like:

# 

# ```text

# Sensor

# &#x20;  │

# &#x20;  ▼

# &#x20;ADC

# &#x20;  │

# &#x20;  ▼

# PIC18F4620

# &#x20;  │

# &#x20;  ├──── PWM ────> MOSFET / Motor / Fan

# &#x20;  │

# &#x20;  ├──── I2C ────> RTC / Sensor

# &#x20;  │

# &#x20;  ├──── SPI ────> SD Card

# &#x20;  │

# &#x20;  └─────────────> LCD

# ```

# 

# \---

# 

# \# Coding Approach

# 

# Two approaches are intentionally used throughout this repository.

# 

# \## mikroC Libraries

# 

# mikroC peripheral libraries are used when they provide a clean and reliable implementation suitable for the application.

# 

# Example:

# 

# ```c

# ADC\_Init();

# 

# adc\_value = ADC\_Read(0);

# ```

# 

# \## Direct Register Configuration

# 

# Other experiments configure the hardware directly.

# 

# Example:

# 

# ```c

# TRISBbits.TRISB0 = 1;

# 

# INTCON2bits.INTEDG0 = 1;

# 

# INTCONbits.INT0IF = 0;

# INTCONbits.INT0IE = 1;

# INTCONbits.GIE = 1;

# ```

# 

# This allows the repository to demonstrate both practical application development and low-level understanding of PIC18 hardware.

# 

# \---

# 

# \# Documentation

# 

# Every experiment contains its own `README.md` describing:

# 

# \* Objective

# \* Hardware used

# \* Circuit connections

# \* Peripheral configuration

# \* Important registers

# \* How the code works

# \* Build/programming information

# \* Test procedure

# \* Results

# \* Photos or diagrams

# \* Notes and lessons learned

# 

# \---

# 

# \# Hardware Verification

# 

# Whenever possible, projects are tested on real hardware rather than existing only as simulations.

# 

# Project directories may therefore include:

# 

# ```text

# photos/

# schematics/

# results/

# ```

# 

# These provide evidence that the circuits were physically constructed and tested.

# 

# \---

# 

# \# References

# 

# Primary technical references include:

# 

# \* Microchip PIC18F4620 Datasheet

# \* mikroC PRO for PIC documentation

# \* Microchip PIC18 documentation

# 

# \---

# 

# \## Status

# 

# This repository is continuously expanded as I study and build projects using the PIC18F4620.

# 

# The emphasis is on understanding the hardware, building real circuits, reading the datasheet, and applying PIC18 peripherals in practical embedded systems.

