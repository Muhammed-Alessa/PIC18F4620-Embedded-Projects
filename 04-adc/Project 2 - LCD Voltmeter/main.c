/*
 * Project: LCD Voltmeter
 * Source concept: Dogan Ibrahim, PIC Microcontroller Projects in C
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * AN0 / RA0 = voltage input, 0 to 5 V
 *
 * LCD:
 * RB0 = D4
 * RB1 = D5
 * RB2 = D6
 * RB3 = D7
 * RB4 = RS
 * RB5 = E
 *
 * Set the project clock to 8 MHz.
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
    char text[12];
    char *value_text;

    CMCON = 0x07;

    TRISA.B0 = 1;

    ADC_Init();
    ADCON1 = 0x0E;        // AN0 analog only, Vref = VDD/VSS

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    Lcd_Out(1, 1, "VOLTMETER");
    Delay_ms(2000);
    Lcd_Cmd(_LCD_CLEAR);

    while(1)
    {
        adc_value = ADC_Get_Sample(0);
        millivolts = ((unsigned long)adc_value * 5000UL) / 1024UL;

        LongToStr(millivolts, text);
        value_text = Ltrim(text);

        Lcd_Out(1, 1, "Voltage:");
        Lcd_Out(2, 1, "                ");
        Lcd_Out(2, 1, value_text);
        Lcd_Out_Cp(" mV");

        Delay_ms(1000);
    }
}
