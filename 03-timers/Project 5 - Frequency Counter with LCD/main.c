/*
 * Project: Frequency Counter with LCD
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * RA4 / T0CKI = frequency input
 * Timer0       = 16-bit external pulse counter
 * Timer1       = 250 ms timing interrupt
 * Four Timer1 interrupts create a 1 second measurement window.
 *
 * This simple version measures up to 65535 Hz.
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

volatile unsigned char quarter_seconds = 0;
volatile unsigned char window_done = 0;

void interrupt()
{
    if(PIR1.TMR1IF)
    {
        PIR1.TMR1IF = 0;

        TMR1H = 0x0B;
        TMR1L = 0xDC;       // 250 ms at 8 MHz, prescaler 1:8

        quarter_seconds++;

        if(quarter_seconds >= 4)
        {
            T0CON.TMR0ON = 0;
            T1CON.TMR1ON = 0;
            window_done = 1;
        }
    }
}

void StartMeasurement()
{
    T0CON.TMR0ON = 0;
    T1CON.TMR1ON = 0;

    TMR0H = 0x00;
    TMR0L = 0x00;

    TMR1H = 0x0B;
    TMR1L = 0xDC;

    quarter_seconds = 0;
    window_done = 0;

    PIR1.TMR1IF = 0;

    T0CON.TMR0ON = 1;
    T1CON.TMR1ON = 1;
}

void main()
{
    unsigned char high_byte;
    unsigned char low_byte;
    unsigned int frequency;
    char text[7];

    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRISA.B4 = 1;       // T0CKI input

    Lcd_Init();
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Cmd(_LCD_CLEAR);

    RCON.IPEN = 0;

    /*
     * Timer0 OFF initially
     * 16-bit external counter
     * Rising edge
     * No prescaler
     */
    T0CON = 0x28;

    /*
     * Timer1 OFF initially
     * Internal clock
     * Prescaler 1:8
     */
    T1CON = 0x30;

    PIR1.TMR1IF = 0;
    PIE1.TMR1IE = 1;
    INTCON.PEIE = 1;
    INTCON.GIE = 1;

    Lcd_Out(1, 1, "Frequency (Hz)");

    while(1)
    {
        StartMeasurement();

        while(window_done == 0)
        {
        }

        low_byte = TMR0L;
        high_byte = TMR0H;

        frequency = ((unsigned int)high_byte << 8) | low_byte;

        WordToStr(frequency, text);

        Lcd_Out(2, 1, "                ");
        Lcd_Out(2, 1, text);

        Delay_ms(500);
    }
}
