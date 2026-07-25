/*
 * Project: Chasing LEDs
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * Set the project clock to 8 MHz.
 */

void main()
{
    unsigned char pattern = 0x01;

    TRISC = 0x00;      // PORTC as output
    LATC = 0x00;       // All LEDs initially OFF

    while(1)
    {
        LATC = pattern;
        Delay_ms(1000);

        pattern <<= 1;

        if(pattern == 0)
        {
            pattern = 0x01;
        }
    }
}
