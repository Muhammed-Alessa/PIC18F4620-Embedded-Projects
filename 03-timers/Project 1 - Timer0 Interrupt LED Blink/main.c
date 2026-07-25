/*
 * Project: Timer0 Interrupt LED Blink
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RD0 = LED
 * Clock = 8 MHz
 *
 * Timer0:
 * 16-bit mode
 * Internal clock (Fosc/4)
 * Prescaler 1:256
 * Preload 0xF0BE -> about 500 ms
 */

void interrupt()
{
    if(INTCON.TMR0IF)
    {
        TMR0H = 0xF0;
        TMR0L = 0xBE;

        INTCON.TMR0IF = 0;
        LATD.B0 = !LATD.B0;
    }
}

void main()
{
    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRISD.B0 = 0;
    LATD.B0 = 0;

    RCON.IPEN = 0;

    T0CON = 0x87;       // ON, 16-bit, internal clock, prescaler 1:256
    TMR0H = 0xF0;
    TMR0L = 0xBE;

    INTCON.TMR0IF = 0;
    INTCON.TMR0IE = 1;
    INTCON.GIE = 1;

    while(1)
    {
    }
}
