/*
 * Project: LPS331AP I2C Device Identification
 * Source basis:
 *   Doğan Ibrahim, PIC Microcontroller Projects in C: Basic to Advanced
 *   Project 7.11 - Barometer, Thermometer and Altimeter Display on a GLCD
 *
 * MCU: PIC18F4620
 * Compiler: mikroC PRO for PIC
 *
 * I2C:
 *   RC3 / SCL
 *   RC4 / SDA
 *   100 kHz bus speed
 *
 * LPS331AP configuration follows Ibrahim's project:
 *   SA0 = HIGH  -> write address 0xBA, read address 0xBB
 *   CS  = HIGH  -> I2C mode
 *   WHO_AM_I register should return 0xBB
 *
 * Status LEDs:
 *   RD0 = communication OK
 *   RD1 = communication error
 *
 * Set the mikroC project clock correctly for the oscillator configuration used.
 */

#define LPS_WRITE_ADDRESS  0xBA
#define LPS_READ_ADDRESS   0xBB

#define WHO_AM_I           0x0F
#define RES_CONF           0x10
#define CTRL_REG1          0x20

#define LED_OK             LATD.B0
#define LED_ERROR          LATD.B1

/*
 * Write one byte to an LPS331AP register.
 * Returns 0 when all I2C write operations are acknowledged.
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
 * Read one byte from an LPS331AP register.
 * The sensor register address is first written, followed by
 * a repeated START and the read address.
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

    *value = I2C1_Rd(0);       // Last byte: send NACK
    I2C1_Stop();

    return status;
}

void main()
{
    unsigned char device_id;
    unsigned char status = 0;

    ADCON1 = 0x0F;             // Configure analog-capable pins as digital
    CMCON = 0x07;              // Disable comparators

    TRISD.B0 = 0;
    TRISD.B1 = 0;

    LED_OK = 0;
    LED_ERROR = 0;

    /*
     * mikroC configures the MSSP pins when the hardware
     * I2C library is initialized.
     */
    I2C1_Init(100000);
    Delay_ms(10);

    /*
     * Initialization values are taken from Ibrahim's
     * LPS331AP project.
     */
    status |= LPS_WriteRegister(RES_CONF, 0x78);
    status |= LPS_WriteRegister(CTRL_REG1, 0x04);
    status |= LPS_WriteRegister(CTRL_REG1, 0x84);

    status |= LPS_ReadRegister(WHO_AM_I, &device_id);

    if((status == 0) && (device_id == 0xBB))
    {
        LED_OK = 1;
        LED_ERROR = 0;
    }
    else
    {
        LED_OK = 0;
        LED_ERROR = 1;
    }

    while(1)
    {
        // Keep the test result visible on the LEDs.
    }
}
