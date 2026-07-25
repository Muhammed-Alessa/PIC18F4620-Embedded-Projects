/*
 * Project: LED Dice
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RB0 = push button, active LOW
 * PORTC = seven dice LEDs
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
    unsigned char number;
    const unsigned char dice[7] =
    {
        0x00, 0x08, 0x22, 0x2A, 0x55, 0x5D, 0x77
    };

    ADCON1 = 0x0F;     // Configure analog-capable pins as digital

    TRISB.B0 = 1;      // RB0 as input
    TRISC = 0x00;      // PORTC as output
    LATC = 0x00;

    while(1)
    {
        // Keep changing the generator while waiting for a button press.
        NextDie();

        if(PORTB.B0 == 0)
        {
            Delay_ms(20);             // Simple debounce

            if(PORTB.B0 == 0)
            {
                number = NextDie();
                LATC = dice[number];

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
