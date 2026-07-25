/*
 * Project: Complex Flashing LED
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * Set the project clock to 8 MHz.
 */

void main()
{
    unsigned char i;

    TRISC.B0 = 0;      // RC0 as output
    LATC.B0 = 0;       // LED initially OFF

    while(1)
    {
        for(i = 0; i < 3; i++)
        {
            LATC.B0 = 1;
            Delay_ms(200);

            LATC.B0 = 0;
            Delay_ms(200);
        }

        Delay_ms(2000);
    }
}
