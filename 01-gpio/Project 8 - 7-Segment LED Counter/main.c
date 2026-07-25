/*
 * Project: 7-Segment LED Counter
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * Common-anode display:
 * RC0=a, RC1=b, RC2=c, RC3=d, RC4=e, RC5=f, RC6=g
 */

void main()
{
    unsigned char count = 0;

    const unsigned char segment[10] =
    {
        0x3F, 0x06, 0x5B, 0x4F, 0x66,
        0x6D, 0x7D, 0x07, 0x7F, 0x6F
    };

    TRISC = 0x00;
    LATC = 0xFF;       // All segments OFF for common-anode display

    while(1)
    {
        LATC = ~segment[count];

        Delay_ms(1000);

        count++;

        if(count >= 10)
        {
            count = 0;
        }
    }
}
