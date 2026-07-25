/*
 * Project: Timer1 Interrupt LED Blink
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RD0 = LED
 * Clock = 8 MHz
 *
 * Timer1:
 * Internal clock
 * Prescaler 1:8
 * Preload 0x0BDC -> 250 ms
 */

unsigned char quarter_count = 0;

void interrupt()
{
    if(PIR1.TMR1IF)
    {
        TMR1H = 0x0B;
        TMR1L = 0xDC;
        PIR1.TMR1IF = 0;

        quarter_count++;

        if(quarter_count >= 2)
        {
            quarter_count = 0;
            LATD.B0 = !LATD.B0;
        }
    }
}

void main()
{
    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRISD.B0 = 0;
    LATD.B0 = 0;

    RCON.IPEN = 0;

    T1CON = 0x31;       // Timer1 ON, internal clock, prescaler 1:8
    TMR1H = 0x0B;
    TMR1L = 0xDC;

    PIR1.TMR1IF = 0;
    PIE1.TMR1IE = 1;

    INTCON.PEIE = 1;
    INTCON.GIE = 1;

    while(1)
    {
    }
}
