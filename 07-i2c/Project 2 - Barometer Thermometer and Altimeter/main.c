/*
 * Project: Barometer, Thermometer and Altimeter
 * Source basis:
 *   Doğan Ibrahim, PIC Microcontroller Projects in C: Basic to Advanced
 *   Project 7.11 - Barometer, Thermometer and Altimeter Display on a GLCD
 *
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * Sensor: LPS331AP
 * Interface: hardware I2C, 100 kHz
 *
 * LPS331AP:
 *   SA0 = HIGH -> write address 0xBA, read address 0xBB
 *   CS  = HIGH -> I2C mode
 *
 * PIC18F4620 MSSP pins:
 *   RC3 = SCL
 *   RC4 = SDA
 *
 * GLCD:
 *   PORTD = D0..D7
 *   RB0   = CS1
 *   RB1   = CS2
 *   RB2   = RS
 *   RB3   = R/W
 *   RB4   = EN
 *   RB5   = RST
 *
 * The original Ibrahim project uses an 8 MHz crystal with the PLL
 * enabled, giving a 32 MHz CPU clock. Configure the mikroC project
 * clock and oscillator mode to match the hardware.
 *
 * Required mikroC libraries:
 *   - I2C
 *   - GLCD
 *   - Conversions
 *   - Math
 */

// GLCD connections
char GLCD_DataPort at PORTD;

sbit GLCD_CS1 at LATB0_bit;
sbit GLCD_CS2 at LATB1_bit;
sbit GLCD_RS  at LATB2_bit;
sbit GLCD_RW  at LATB3_bit;
sbit GLCD_EN  at LATB4_bit;
sbit GLCD_RST at LATB5_bit;

sbit GLCD_CS1_Direction at TRISB0_bit;
sbit GLCD_CS2_Direction at TRISB1_bit;
sbit GLCD_RS_Direction  at TRISB2_bit;
sbit GLCD_RW_Direction  at TRISB3_bit;
sbit GLCD_EN_Direction  at TRISB4_bit;
sbit GLCD_RST_Direction at TRISB5_bit;
// End GLCD connections

// LPS331AP register map used by Ibrahim's project
#define WHO_AM_I            0x0F
#define RES_CONF            0x10
#define CTRL_REG1           0x20
#define CTRL_REG2           0x21
#define STATUS_REG          0x27
#define PRESS_OUT_XL        0x28
#define PRESS_OUT_L         0x29
#define PRESS_OUT_H         0x2A
#define TEMP_OUT_L          0x2B
#define TEMP_OUT_H          0x2C

#define LPS_WRITE_ADDRESS   0xBA
#define LPS_READ_ADDRESS    0xBB

#define STATUS_T_DA         0x01
#define STATUS_P_DA         0x02

/*
 * Return a pointer to the first non-space character.
 * This avoids depending on an additional string-trimming routine.
 */
char *SkipLeadingSpaces(char *text)
{
    while(*text == ' ')
    {
        text++;
    }

    return text;
}

/*
 * Keep one digit after the decimal point in FloatToStr output.
 */
void KeepOneDecimal(char *text)
{
    unsigned char i = 0;

    while(text[i] != 0)
    {
        if(text[i] == '.')
        {
            if(text[i + 1] != 0)
            {
                text[i + 2] = 0;
            }

            return;
        }

        i++;
    }
}

/*
 * Write one byte to a sensor register.
 * Returns 0 when all transmitted bytes were acknowledged.
 */
unsigned char LPS_WriteRegister(unsigned char reg_address,
                                unsigned char value)
{
    unsigned char status = 0;

    I2C1_Start();

    status |= I2C1_Wr(LPS_WRITE_ADDRESS);
    status |= I2C1_Wr(reg_address);
    status |= I2C1_Wr(value);

    I2C1_Stop();

    return status;
}

/*
 * Read one byte from a sensor register.
 */
unsigned char LPS_ReadRegister(unsigned char reg_address,
                               unsigned char *value)
{
    unsigned char status = 0;

    I2C1_Start();

    status |= I2C1_Wr(LPS_WRITE_ADDRESS);
    status |= I2C1_Wr(reg_address);

    I2C1_Repeated_Start();

    status |= I2C1_Wr(LPS_READ_ADDRESS);

    *value = I2C1_Rd(0);       // Last byte, send NACK

    I2C1_Stop();

    return status;
}

/*
 * Initialize the LPS331AP using the configuration sequence
 * used in Ibrahim's project.
 */
unsigned char LPS_Init()
{
    unsigned char status = 0;
    unsigned char device_id = 0;

    // Recommended pressure/temperature averaging configuration
    status |= LPS_WriteRegister(RES_CONF, 0x78);

    // One-shot configuration
    status |= LPS_WriteRegister(CTRL_REG1, 0x04);

    // Active mode, one-shot operation
    status |= LPS_WriteRegister(CTRL_REG1, 0x84);

    status |= LPS_ReadRegister(WHO_AM_I, &device_id);

    if((status != 0) || (device_id != 0xBB))
    {
        return 1;
    }

    return 0;
}

/*
 * Poll STATUS_REG until the requested data-ready flag is set.
 *
 * Ibrahim's original code waits indefinitely. This adaptation uses
 * a bounded wait so a missing or failed sensor cannot lock the
 * application forever.
 */
unsigned char LPS_WaitReady(unsigned char mask)
{
    unsigned int attempts;
    unsigned char status_reg;

    for(attempts = 0; attempts < 1000; attempts++)
    {
        if(LPS_ReadRegister(STATUS_REG, &status_reg) != 0)
        {
            return 1;
        }

        if(status_reg & mask)
        {
            return 0;
        }

        Delay_ms(1);
    }

    return 1;
}

/*
 * Start a one-shot measurement and return pressure in millibars.
 *
 * The LPS331AP pressure output is 24 bits. Ibrahim converts the
 * raw reading to millibars by dividing by 4096, equivalent to
 * shifting right by 12 bits.
 */
unsigned char LPS_ReadPressure(long *pressure_mbar)
{
    unsigned char high_byte;
    unsigned char middle_byte;
    unsigned char low_byte;
    unsigned long raw_pressure;

    if(LPS_WriteRegister(CTRL_REG2, 0x01) != 0)
    {
        return 1;
    }

    if(LPS_WaitReady(STATUS_P_DA) != 0)
    {
        return 1;
    }

    if(LPS_ReadRegister(PRESS_OUT_H, &high_byte) != 0)
    {
        return 1;
    }

    if(LPS_ReadRegister(PRESS_OUT_L, &middle_byte) != 0)
    {
        return 1;
    }

    if(LPS_ReadRegister(PRESS_OUT_XL, &low_byte) != 0)
    {
        return 1;
    }

    raw_pressure  = (unsigned long)high_byte << 16;
    raw_pressure |= (unsigned long)middle_byte << 8;
    raw_pressure |= (unsigned long)low_byte;

    *pressure_mbar = (long)(raw_pressure >> 12);

    return 0;
}

/*
 * Return temperature in degrees Celsius.
 *
 * Ibrahim's project uses:
 *
 *   temperature = (raw / 480.0) + 42.5
 */
unsigned char LPS_ReadTemperature(float *temperature_c)
{
    unsigned char high_byte;
    unsigned char low_byte;
    signed int raw_temperature;

    if(LPS_WaitReady(STATUS_T_DA) != 0)
    {
        return 1;
    }

    if(LPS_ReadRegister(TEMP_OUT_H, &high_byte) != 0)
    {
        return 1;
    }

    if(LPS_ReadRegister(TEMP_OUT_L, &low_byte) != 0)
    {
        return 1;
    }

    raw_temperature =
        (signed int)(((unsigned int)high_byte << 8) | low_byte);

    *temperature_c = ((float)raw_temperature / 480.0) + 42.5;

    return 0;
}

/*
 * Ibrahim's project calculates altitude in feet from pressure using:
 *
 *   altitude = (1 - (pressure / 1013.25)^0.190284) * 145366.45
 *
 * This is an approximate pressure-altitude calculation.
 */
float CalculateAltitude(long pressure_mbar)
{
    float ratio;

    ratio = (float)pressure_mbar / 1013.25;
    ratio = pow(ratio, 0.190284);

    return (1.0 - ratio) * 145366.45;
}

void DisplayMeasurements(long pressure_mbar,
                         float temperature_c,
                         float altitude_ft)
{
    char text[16];
    char *number;

    Glcd_Rectangle(5, 5, 120, 55, 1);

    Glcd_Write_Text("P(mb):", 7, 1, 1);
    Glcd_Write_Text("T(C) :", 7, 3, 1);
    Glcd_Write_Text("A(ft):", 7, 5, 1);

    // Pressure
    LongToStr(pressure_mbar, text);
    number = SkipLeadingSpaces(text);
    Glcd_Write_Text(number, 50, 1, 1);

    // Temperature
    FloatToStr(temperature_c, text);
    number = SkipLeadingSpaces(text);
    KeepOneDecimal(number);
    Glcd_Write_Text(number, 50, 3, 1);

    // Altitude
    FloatToStr(altitude_ft, text);
    number = SkipLeadingSpaces(text);
    KeepOneDecimal(number);
    Glcd_Write_Text(number, 50, 5, 1);
}

void DisplayError()
{
    Glcd_Fill(0x00);
    Glcd_Write_Text("LPS331AP ERROR", 10, 3, 1);

    while(1)
    {
        // Stop here because the sensor did not initialize correctly.
    }
}

void main()
{
    long pressure_mbar;
    float temperature_c;
    float altitude_ft;

    ADCON1 = 0x0F;
    CMCON = 0x07;

    Glcd_Init();
    Glcd_Fill(0x00);

    /*
     * Initialize the PIC18F4620 hardware MSSP module as
     * a 100 kHz I2C master.
     */
    I2C1_Init(100000);
    Delay_ms(10);

    if(LPS_Init() != 0)
    {
        DisplayError();
    }

    while(1)
    {
        if(LPS_ReadPressure(&pressure_mbar) != 0)
        {
            DisplayError();
        }

        if(LPS_ReadTemperature(&temperature_c) != 0)
        {
            DisplayError();
        }

        altitude_ft = CalculateAltitude(pressure_mbar);

        Glcd_Fill(0x00);

        DisplayMeasurements(pressure_mbar,
                            temperature_c,
                            altitude_ft);

        Delay_ms(5000);
    }
}
