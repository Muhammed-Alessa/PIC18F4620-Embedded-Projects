/*
 * Project: PORTB Change Interrupt
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RB4 = input that causes PORTB change interrupt
 * RD0 = LED output
 */

void interrupt()
{
    unsigned char portb_snapshot;

    if(INTCON.RBIF)
    {
        portb_snapshot = PORTB;  // Read PORTB to end the mismatch condition
        LATD.B0 = !LATD.B0;

        INTCON.RBIF = 0;         // Clear PORTB change flag
    }
}

void main()
{
    unsigned char initial_read;

    ADCON1 = 0x0F;
    CMCON  = 0x07;

    TRISB.B4 = 1;                // RB4 as input
    TRISD.B0 = 0;                // RD0 as output
    LATD.B0 = 0;

    RCON.IPEN = 0;               // Use single interrupt priority

    initial_read = PORTB;        // Initialize PORTB mismatch condition
    INTCON.RBIF = 0;
    INTCON.RBIE = 1;             // Enable PORTB change interrupt
    INTCON.GIE = 1;

    while(1)
    {
    }
}
