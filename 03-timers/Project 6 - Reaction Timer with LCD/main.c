/*
 * Project: Reaction Timer with LCD
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RC0 = LED
 * RC7 = push button, active LOW
 *
 * Timer0:
 * 16-bit mode
 * Internal clock
 * Prescaler 1:256
 *
 * At 8 MHz:
 * Instruction clock period = 0.5 us
 * Timer tick = 0.5 us x 256 = 128 us
 */

// LCD connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
// End LCD connections

unsigned int lfsr = 0xACE1;

unsigned char NextDelaySeconds()
{
    if(lfsr & 0x0001)
    {
        lfsr = (lfsr >> 1) ^ 0xB400;
    }
    else
    {
        lfsr >>= 1;
    }

    return (unsigned char)(lfsr % 5) + 1;
}

void main()
{
    unsigned char delay_seconds;
    unsigned char i;
    unsigned char high_byte;
    unsigned char low_byte;

    unsigned int timer_count;
    unsigned long reaction_ms;

    char text[11];

    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRISC.B0 = 0;       // LED output
    TRISC.B7 = 1;       // Push button input
    LATC.B0 = 0;

    Lcd_Init();
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Cmd(_LCD_CLEAR);

    /*
     * Timer0 stopped
     * 16-bit mode
     * Internal clock
     * Prescaler 1:256
     */
    T0CON = 0x07;

    while(1)
    {
        Lcd_Cmd(_LCD_CLEAR);
        Lcd_Out(1, 1, "Get ready...");

        LATC.B0 = 0;

        // Do not begin while the button is already pressed.
        while(PORTC.B7 == 0)
        {
        }

        delay_seconds = NextDelaySeconds();

        for(i = 0; i < delay_seconds; i++)
        {
            Delay_ms(1000);
        }

        TMR0H = 0x00;
        TMR0L = 0x00;
        INTCON.TMR0IF = 0;

        LATC.B0 = 1;
        T0CON.TMR0ON = 1;

        while((PORTC.B7 == 1) && (INTCON.TMR0IF == 0))
        {
        }

        T0CON.TMR0ON = 0;
        LATC.B0 = 0;

        Lcd_Cmd(_LCD_CLEAR);

        if(INTCON.TMR0IF)
        {
            Lcd_Out(1, 1, "Too slow");
            Lcd_Out(2, 1, "Try again");
        }
        else
        {
            low_byte = TMR0L;
            high_byte = TMR0H;

            timer_count = ((unsigned int)high_byte << 8) | low_byte;

            reaction_ms = ((unsigned long)timer_count * 128UL) / 1000UL;

            LongWordToStr(reaction_ms, text);

            Lcd_Out(1, 1, "Reaction (ms)");
            Lcd_Out(2, 1, text);
        }

        Delay_ms(2000);
    }
}
