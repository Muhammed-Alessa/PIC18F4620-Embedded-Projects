/*
 * Project: INT0 External Interrupt LED Toggle
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RB0 / INT0 = interrupt input
 * RD0        = LED output
 * Set the project clock to 8 MHz.
 */

void interrupt()
{
    if(INTCON.INT0IF)
    {
        LATD.B0 = !LATD.B0;      // Toggle LED
        INTCON.INT0IF = 0;        // Clear INT0 interrupt flag
    }
}

void main()
{
    ADCON1 = 0x0F;               // Configure analog-capable pins as digital
    CMCON  = 0x07;               // Disable comparators

    TRISB.B0 = 1;                // RB0 / INT0 as input
    TRISD.B0 = 0;                // RD0 as output
    LATD.B0 = 0;                 // LED initially OFF

    RCON.IPEN = 0;               // Disable interrupt priority levels

    INTCON2.INTEDG0 = 1;         // INT0 interrupt on rising edge
    INTCON.INT0IF = 0;           // Clear interrupt flag
    INTCON.INT0IE = 1;           // Enable INT0 interrupt
    INTCON.GIE = 1;              // Enable global interrupts

    while(1)
    {
        // Main program is free for other work.
    }
}
