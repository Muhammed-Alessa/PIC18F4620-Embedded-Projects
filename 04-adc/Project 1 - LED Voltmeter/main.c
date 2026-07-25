/*
 * Project: LED Voltmeter
 * Source concept: Dogan Ibrahim, PIC Microcontroller Projects in C
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * AN0 / RA0 = voltage input, 0 to 5 V
 * RD0       = 0 to 1 V
 * RD1       = 1 to 2 V
 * RD2       = 2 to 3 V
 * RD3       = 3 to 4 V
 * RD4       = 4 to 5 V
 *
 * Set the project clock to 8 MHz.
 */

void main()
{
    unsigned int adc_value;
    unsigned long millivolts;

    CMCON = 0x07;          // Disable comparators

    TRISA.B0 = 1;          // AN0 input
    TRISD = 0x00;          // LED outputs
    LATD = 0x00;

    ADC_Init();            // Initialize ADC using mikroC ADC library
    ADCON1 = 0x0E;         // AN0 analog, remaining AN pins digital, Vref = VDD/VSS

    while(1)
    {
        adc_value = ADC_Get_Sample(0);

        // 10-bit ADC: 1024 quantization steps over a 5 V reference
        millivolts = ((unsigned long)adc_value * 5000UL) / 1024UL;

        LATD = 0x00;

        if(millivolts <= 1000UL)
        {
            LATD.B0 = 1;
        }
        else if(millivolts <= 2000UL)
        {
            LATD.B1 = 1;
        }
        else if(millivolts <= 3000UL)
        {
            LATD.B2 = 1;
        }
        else if(millivolts <= 4000UL)
        {
            LATD.B3 = 1;
        }
        else
        {
            LATD.B4 = 1;
        }

        Delay_ms(10);
    }
}
