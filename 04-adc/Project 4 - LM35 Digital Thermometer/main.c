/*
 * Project: LM35 Digital Thermometer
 * Source concept: Dogan Ibrahim, PIC Microcontroller Projects in C
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * LM35DZ output = 10 mV / degree C
 * AN0 / RA0     = LM35 output
 *
 * This version keeps the conversion integer-only.
 * Since 1 mV from the LM35 represents 0.1 degree C,
 * the measured millivolts can be displayed directly as tenths of a degree.
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
    unsigned long millivolts;
    unsigned int temp_whole;
    unsigned char temp_tenths;
    char text[7];
    char *value_text;

    CMCON = 0x07;

    TRISA.B0 = 1;

    ADC_Init();
    ADCON1 = 0x0E;        // AN0 analog only, Vref = VDD/VSS

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    while(1)
    {
        adc_value = ADC_Get_Sample(0);

        millivolts = ((unsigned long)adc_value * 5000UL) / 1024UL;

        // LM35: 10 mV = 1 degree C
        temp_whole = (unsigned int)(millivolts / 10UL);
        temp_tenths = (unsigned char)(millivolts % 10UL);

        WordToStr(temp_whole, text);
        value_text = Ltrim(text);

        Lcd_Out(1, 1, "Temperature");
        Lcd_Out(2, 1, "                ");

        Lcd_Out(2, 1, value_text);
        Lcd_Chr_Cp('.');
        Lcd_Chr_Cp(temp_tenths + '0');
        Lcd_Chr_Cp(223);             // Degree symbol on HD44780-compatible LCD
        Lcd_Chr_Cp('C');

        Delay_ms(1000);
    }
}
