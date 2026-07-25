/*
 * Project: INT1 High-Priority Interrupt
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RB1 / INT1 = high-priority interrupt input
 * RD0        = LED output
 */

void interrupt()
{
    if(INTCON3.INT1IF)
    {
        LATD.B0 = !LATD.B0;
        INTCON3.INT1IF = 0;
    }
}

void main()
{
    ADCON1 = 0x0F;
    CMCON  = 0x07;

    TRISB.B1 = 1;                // RB1 / INT1 as input
    TRISD.B0 = 0;                // RD0 as output
    LATD.B0 = 0;

    RCON.IPEN = 1;               // Enable priority levels

    INTCON2.INTEDG1 = 1;         // INT1 interrupt on rising edge
    INTCON3.INT1IF = 0;          // Clear INT1 flag
    INTCON3.INT1IP = 1;          // INT1 = high priority
    INTCON3.INT1IE = 1;          // Enable INT1

    INTCON.GIEH = 1;             // Enable high-priority interrupts

    while(1)
    {
    }
}
