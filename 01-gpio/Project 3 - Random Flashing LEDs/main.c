/*
 * Project: Random Flashing LEDs
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * Set the project clock to 8 MHz.
 */

unsigned int lfsr = 0xACE1;

unsigned char NextRandomByte()
{
    unsigned char i;

    for(i = 0; i < 8; i++)
    {
        if(lfsr & 0x0001)
        {
            lfsr = (lfsr >> 1) ^ 0xB400;
        }
        else
        {
            lfsr >>= 1;
        }
    }

    return (unsigned char)lfsr;
}

void main()
{
    TRISC = 0x00;      // PORTC as output
    LATC = 0x00;       // All LEDs initially OFF

    while(1)
    {
        LATC = NextRandomByte();
        Delay_ms(1000);
    }
}
