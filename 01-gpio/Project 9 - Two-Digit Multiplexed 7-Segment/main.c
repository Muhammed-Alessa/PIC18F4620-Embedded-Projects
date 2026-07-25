/*
 * Project: Two-Digit Multiplexed 7-Segment
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * PORTD = segments a..g
 * RA0   = right digit enable
 * RA1   = left digit enable
 *
 * Common-cathode display with active-HIGH digit drivers.
 */

const unsigned char segment[10] =
{
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void AllDigitsOff()
{
    LATA.B0 = 0;
    LATA.B1 = 0;
}

void main()
{
    unsigned char number = 25;
    unsigned char tens;
    unsigned char ones;

    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRISA.B0 = 0;
    TRISA.B1 = 0;
    TRISD = 0x00;

    LATA.B0 = 0;
    LATA.B1 = 0;
    LATD = 0x00;

    tens = number / 10;
    ones = number % 10;

    while(1)
    {
        // Left digit
        AllDigitsOff();
        LATD = segment[tens];
        LATA.B1 = 1;
        Delay_ms(5);

        // Right digit
        AllDigitsOff();
        LATD = segment[ones];
        LATA.B0 = 1;
        Delay_ms(5);
    }
}
