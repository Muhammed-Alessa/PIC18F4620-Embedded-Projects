/*
 * Project: Two Dice Using Fewer I/O Pins
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RB0 = push button, active LOW
 * RC0..RC3 = first dice groups
 * RC4..RC7 = second dice groups
 */

unsigned int lfsr = 0xACE1;

unsigned char NextDie()
{
    if(lfsr & 0x0001)
    {
        lfsr = (lfsr >> 1) ^ 0xB400;
    }
    else
    {
        lfsr >>= 1;
    }

    return (unsigned char)(lfsr % 6) + 1;
}

void main()
{
    unsigned char first;
    unsigned char second;
    unsigned char low_nibble;
    unsigned char high_nibble;

    const unsigned char dice4[7] =
    {
        0x00, 0x08, 0x01, 0x09, 0x06, 0x0E, 0x07
    };

    ADCON1 = 0x0F;

    TRISB.B0 = 1;
    TRISC = 0x00;
    LATC = 0x00;

    while(1)
    {
        NextDie();

        if(PORTB.B0 == 0)
        {
            Delay_ms(20);

            if(PORTB.B0 == 0)
            {
                first = NextDie();
                second = NextDie();

                low_nibble = dice4[first];
                high_nibble = dice4[second] << 4;

                LATC = high_nibble | low_nibble;

                Delay_ms(3000);
                LATC = 0x00;

                while(PORTB.B0 == 0)
                {
                    // Wait for button release
                }

                Delay_ms(20);
            }
        }
    }
}
