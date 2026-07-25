/*
 * Project: INT1 Low-Priority Interrupt
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RB1 / INT1 = low-priority interrupt input
 * RD0        = LED output
 */

void interrupt_low()
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

    TRISB.B1 = 1;
    TRISD.B0 = 0;
    LATD.B0 = 0;

    RCON.IPEN = 1;               // Enable interrupt priority levels

    INTCON2.INTEDG1 = 1;         // Rising-edge interrupt
    INTCON3.INT1IF = 0;
    INTCON3.INT1IP = 0;          // INT1 = low priority
    INTCON3.INT1IE = 1;

    INTCON.GIEL = 1;             // Enable low-priority interrupts
    INTCON.GIEH = 1;             // Global/high-priority enable

    while(1)
    {
    }
}
