/*
 * Project: Timer0 Square Wave Generator
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RC2 = square-wave output
 * Clock = 8 MHz
 *
 * Timer0 tick with 1:2 prescaler = 1 us
 * 500 timer counts = 500 us
 * Preload = 65536 - 500 = 65036 = 0xFE0C
 * Output toggles every 500 us -> about 1 kHz square wave
 */

void interrupt()
{
    if(INTCON.TMR0IF)
    {
        TMR0H = 0xFE;
        TMR0L = 0x0C;

        INTCON.TMR0IF = 0;
        LATC.B2 = !LATC.B2;
    }
}

void main()
{
    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRISC.B2 = 0;
    LATC.B2 = 0;

    RCON.IPEN = 0;

    T0CON = 0x80;       // ON, 16-bit, internal clock, prescaler 1:2
    TMR0H = 0xFE;
    TMR0L = 0x0C;

    INTCON.TMR0IF = 0;
    INTCON.TMR0IE = 1;
    INTCON.GIE = 1;

    while(1)
    {
    }
}
