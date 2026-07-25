/*
 * Project: Timer0 External Pulse Counter
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RA4 / T0CKI = external pulse input
 * PORTD       = low 8 bits of the count
 */

void main()
{
    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRISA.B4 = 1;       // T0CKI input
    TRISD = 0x00;       // LEDs as outputs
    LATD = 0x00;

    TMR0H = 0x00;
    TMR0L = 0x00;

    /*
     * Timer0 ON
     * 16-bit mode
     * External clock from T0CKI
     * Increment on low-to-high transition
     * Prescaler not assigned
     */
    T0CON = 0xA8;

    while(1)
    {
        LATD = TMR0L;
    }
}
