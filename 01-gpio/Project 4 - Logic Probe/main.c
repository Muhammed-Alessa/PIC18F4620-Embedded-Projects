/*
 * Project: Logic Probe
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RC0 = probe input
 * RC6 = red LED
 * RC7 = green LED
 */

#define PROBE      PORTC.B0
#define RED_LED    LATC.B6
#define GREEN_LED  LATC.B7

void main()
{
    TRISC.B0 = 1;      // RC0 as input
    TRISC.B6 = 0;      // RC6 as output
    TRISC.B7 = 0;      // RC7 as output

    RED_LED = 0;
    GREEN_LED = 0;

    while(1)
    {
        if(PROBE == 0)
        {
            GREEN_LED = 0;
            RED_LED = 1;
        }
        else
        {
            RED_LED = 0;
            GREEN_LED = 1;
        }
    }
}
