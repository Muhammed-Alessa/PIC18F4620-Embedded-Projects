/*
 * Project: Precision LCD Voltmeter
 * Source concept: Dogan Ibrahim, Advanced PIC Microcontroller Projects in C
 *
 * This implementation follows the book's fixed-point scaling idea:
 *     5000 / 1024 = 4.8828125 mV per ADC count
 *
 * The ADC result is multiplied by 488, then split into an integer
 * and a two-digit fractional part. This avoids floating-point math.
 *
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 */

// LCD module connections
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
// End LCD module connections


void main()
{
    unsigned int adc_value;
    unsigned long scaled;
    unsigned long whole_mv;
    unsigned char fraction;
    char text[12];
    char *value_text;

    CMCON = 0x07;

    TRISA.B0 = 1;

    ADC_Init();
    ADCON1 = 0x0E;        // AN0 analog only, Vref = VDD/VSS

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    Lcd_Out(1, 1, "PRECISION ADC");
    Delay_ms(2000);
    Lcd_Cmd(_LCD_CLEAR);

    while(1)
    {
        adc_value = ADC_Get_Sample(0);

        /*
         * Fixed-point approximation:
         * adc_value * 4.88 mV
         *
         * scaled is in hundredths of a millivolt.
         */
        scaled = (unsigned long)adc_value * 488UL;

        whole_mv = scaled / 100UL;
        fraction = (unsigned char)(scaled % 100UL);

        LongToStr(whole_mv, text);
        value_text = Ltrim(text);

        Lcd_Out(1, 1, "Voltage:");
        Lcd_Out(2, 1, "                ");

        Lcd_Out(2, 1, value_text);
        Lcd_Chr_Cp('.');
        Lcd_Chr_Cp((fraction / 10) + '0');
        Lcd_Chr_Cp((fraction % 10) + '0');
        Lcd_Out_Cp(" mV");

        Delay_ms(1000);
    }
}
