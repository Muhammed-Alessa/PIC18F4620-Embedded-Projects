/*
 * Project: EEPROM Read to LEDs
 * Source concept:
 *   Dogan Ibrahim, Advanced PIC Microcontroller Projects in C
 *   Section 4.3.1 EEPROM Library, Example 4.11
 *
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 * Clock: 8 MHz
 *
 * The book example reads EEPROM addresses 0x00 through 0x2F
 * and sends each byte to an output port.
 *
 * In this PIC18F4620 adaptation, PORTD is used for the LEDs.
 * This avoids placing the LED bank on the ICSP pins RB6/RB7.
 *
 * The EEPROM must already contain data for the displayed sequence
 * to be meaningful. Project 2 demonstrates writing and reading a
 * known EEPROM value.
 */

void main()
{
    unsigned int address;
    unsigned char value;

    ADCON1 = 0x0F;       // Configure analog-capable pins as digital
    CMCON = 0x07;        // Disable comparators

    TRISD = 0x00;        // Eight LEDs on PORTD
    LATD = 0x00;

    while(1)
    {
        for(address = 0x0000; address <= 0x002F; address++)
        {
            value = EEPROM_Read(address);
            LATD = value;

            /*
             * mikroC documentation specifies at least 20 ms
             * between successive EEPROM library operations.
             * A longer delay is used here so each byte can also
             * be seen clearly on the LEDs.
             */
            Delay_ms(250);
        }

        LATD = 0x00;
        Delay_ms(1000);
    }
}
