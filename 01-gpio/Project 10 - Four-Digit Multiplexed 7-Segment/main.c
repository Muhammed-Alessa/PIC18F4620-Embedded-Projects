/*
 * Project: Four-Digit Multiplexed 7-Segment
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * PORTD = segments a..g
 * RA0..RA3 = digit enables
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
    LATA.B2 = 0;
    LATA.B3 = 0;
}

void ShowDigit(unsigned char value, unsigned char digit)
{
    AllDigitsOff();
    LATD = segment[value];

    switch(digit)
    {
        case 0:
            LATA.B0 = 1;
            break;

        case 1:
            LATA.B1 = 1;
            break;

        case 2:
            LATA.B2 = 1;
            break;

        case 3:
            LATA.B3 = 1;
            break;
    }

    Delay_ms(5);
}

void main()
{
    unsigned int number = 1234;
    unsigned char d0;
    unsigned char d1;
    unsigned char d2;
    unsigned char d3;

    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRISA.B0 = 0;
    TRISA.B1 = 0;
    TRISA.B2 = 0;
    TRISA.B3 = 0;
    TRISD = 0x00;

    LATA = 0x00;
    LATD = 0x00;

    d0 = number % 10;
    d1 = (number / 10) % 10;
    d2 = (number / 100) % 10;
    d3 = (number / 1000) % 10;

    while(1)
    {
        ShowDigit(d0, 0);
        ShowDigit(d1, 1);
        ShowDigit(d2, 2);
        ShowDigit(d3, 3);
    }
}
