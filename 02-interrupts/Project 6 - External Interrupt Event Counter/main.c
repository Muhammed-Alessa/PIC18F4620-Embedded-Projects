/*
 * Project: External Interrupt Event Counter
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RB0 / INT0 = external event input
 * PORTD      = segments a..g
 * RA0..RA3   = digit enables
 *
 * Timer0 refreshes one display digit about every 5 ms.
 * Set the project clock to 8 MHz.
 */

volatile unsigned int event_count = 0;
volatile unsigned char active_digit = 0;

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

void interrupt()
{
    unsigned int value;
    unsigned char digit_value;

    if(INTCON.TMR0IF)
    {
        TMR0L = 100;             // About 5 ms at 8 MHz with 1:64 prescaler
        INTCON.TMR0IF = 0;

        AllDigitsOff();

        value = event_count;

        switch(active_digit)
        {
            case 0:
                digit_value = value % 10;
                LATD = segment[digit_value];
                LATA.B0 = 1;
                break;

            case 1:
                digit_value = (value / 10) % 10;
                LATD = segment[digit_value];
                LATA.B1 = 1;
                break;

            case 2:
                digit_value = (value / 100) % 10;
                LATD = segment[digit_value];
                LATA.B2 = 1;
                break;

            default:
                digit_value = (value / 1000) % 10;
                LATD = segment[digit_value];
                LATA.B3 = 1;
                break;
        }

        active_digit++;

        if(active_digit >= 4)
        {
            active_digit = 0;
        }
    }

    if(INTCON.INT0IF)
    {
        event_count++;

        if(event_count >= 10000)
        {
            event_count = 0;
        }

        INTCON.INT0IF = 0;
    }
}

void main()
{
    ADCON1 = 0x0F;
    CMCON  = 0x07;

    TRISB.B0 = 1;                // INT0 event input

    TRISA.B0 = 0;
    TRISA.B1 = 0;
    TRISA.B2 = 0;
    TRISA.B3 = 0;

    TRISD = 0x00;

    LATA = 0x00;
    LATD = 0x00;

    RCON.IPEN = 0;               // One interrupt priority level

    // Timer0: ON, 8-bit, internal clock, prescaler 1:64
    T0CON = 0xC5;
    TMR0L = 100;

    INTCON2.INTEDG0 = 1;         // INT0 on rising edge

    INTCON.TMR0IF = 0;
    INTCON.TMR0IE = 1;

    INTCON.INT0IF = 0;
    INTCON.INT0IE = 1;

    INTCON.GIE = 1;

    while(1)
    {
        // Event counting and display refresh are interrupt driven.
    }
}
