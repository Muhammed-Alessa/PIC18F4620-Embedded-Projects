/*
 * Project: High and Low Priority Interrupts
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RB1 / INT1 = high priority -> toggles RD0
 * RB2 / INT2 = low priority  -> toggles RD1
 */

void interrupt()
{
    if(INTCON3.INT1IF)
    {
        LATD.B0 = !LATD.B0;
        INTCON3.INT1IF = 0;
    }
}

void interrupt_low()
{
    if(INTCON3.INT2IF)
    {
        LATD.B1 = !LATD.B1;
        INTCON3.INT2IF = 0;
    }
}

void main()
{
    ADCON1 = 0x0F;
    CMCON  = 0x07;

    TRISB.B1 = 1;                // INT1 input
    TRISB.B2 = 1;                // INT2 input

    TRISD.B0 = 0;
    TRISD.B1 = 0;
    LATD.B0 = 0;
    LATD.B1 = 0;

    RCON.IPEN = 1;               // Enable high/low priority system

    INTCON2.INTEDG1 = 1;         // INT1 rising edge
    INTCON2.INTEDG2 = 1;         // INT2 rising edge

    INTCON3.INT1IF = 0;
    INTCON3.INT1IP = 1;          // INT1 high priority
    INTCON3.INT1IE = 1;

    INTCON3.INT2IF = 0;
    INTCON3.INT2IP = 0;          // INT2 low priority
    INTCON3.INT2IE = 1;

    INTCON.GIEL = 1;
    INTCON.GIEH = 1;

    while(1)
    {
    }
}
