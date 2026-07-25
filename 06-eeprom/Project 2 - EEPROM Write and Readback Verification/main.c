/*
 * Project: EEPROM Write and Readback Verification
 * Source concept:
 *   Dogan Ibrahim, Advanced PIC Microcontroller Projects in C
 *   Section 4.3.1 EEPROM Library
 *
 * The book demonstrates:
 *
 *   EEPROM_Read(0x1F);
 *   EEPROM_Write(0x2F, 0x05);
 *
 * This project combines those documented operations into a
 * self-contained hardware test for the PIC18F4620.
 *
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 * Clock: 8 MHz
 *
 * EEPROM address: 0x002F
 * Test value:     0x05
 * PORTD:          binary readback display
 */

#define EEPROM_ADDRESS  0x002F
#define TEST_VALUE      0x05

void main()
{
    unsigned char stored_value;

    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRISD = 0x00;
    LATD = 0x00;

    /*
     * Read the existing byte first.
     * Avoid rewriting the EEPROM when the correct value is
     * already stored, which reduces unnecessary write cycles.
     */
    stored_value = EEPROM_Read(EEPROM_ADDRESS);
    Delay_ms(20);

    if(stored_value != TEST_VALUE)
    {
        EEPROM_Write(EEPROM_ADDRESS, TEST_VALUE);
        Delay_ms(20);

        stored_value = EEPROM_Read(EEPROM_ADDRESS);
        Delay_ms(20);
    }

    /*
     * Expected LED pattern for 0x05:
     *
     * RD7 ... RD0
     *  0       1 0 1
     *
     * In other words, bits 0 and 2 are HIGH.
     */
    LATD = stored_value;

    while(1)
    {
        // Keep the verified EEPROM value displayed.
    }
}
