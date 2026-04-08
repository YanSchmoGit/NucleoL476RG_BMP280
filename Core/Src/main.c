/*
 * Test project for I2C functions
 * Used Hardware:
 * STM32L476RG
 * Bosch BMP280
 *
 */

#include <stm32l4xx.h>
#include <stdio.h>

#include "Init.h"
#include "LCDFunctions.h"
#include "I2C.h"
#include "BMP280.h"
#include "USART_Terminal.h"
#include "PortExpander.h"

#define I2C_SCL_Pin 8
#define I2C_SCL_Port GPIOB

#define I2C_SDA_Pin 9
#define I2C_SDA_Port GPIOB

#define BMP280_DEVICE_ADR  (0x77)
#define PORTEXPANDER_DEVICE_ADR  (0x20)

#define BAUDRATE (uint32_t) (115200)

uint32_t valuePress;
int32_t valueTemp;


int main(void)
{
    // Init functions;
    // Init SysClock

    InitClock();


    // Init I2C

    InitI2C(I2C_SCL_Port, I2C_SCL_Pin, I2C_SDA_Port, I2C_SDA_Pin);

    // Init BMP280;
    InitBMP280(BMP280_DEVICE_ADR);
    GetSensorCalibrationData(BMP280_DEVICE_ADR);

    // Init USART

    InitUSART(BAUDRATE);

    // Port expander

    InitPortExpander(PORTEXPANDER_DEVICE_ADR);

    PortExpanderSetConfig(PORTEXPANDER_DEVICE_ADR, PORT_A);
    PortExpanderSetConfig(PORTEXPANDER_DEVICE_ADR, PORT_B);



    while (1)
    {
        // BMP280 section
        GetSensorValues(BMP280_DEVICE_ADR, &valuePress, &valueTemp);

        /*
                LCDSetCursorLocation(0, 0);
                LCDSendInteger(valueTemp / 100);
                LCDSendString(".");
                LCDSendInteger((valueTemp / 10) % 10);
                LCDSendString(" C");
                LCDSetCursorLocation(0, 1);

                LCDSendInteger(valuePress / 100);
                LCDSendString(".");
                LCDSendInteger((valuePress / 10) % 10);
                LCDSendString(" hPa");

        */
        //SendAInteger(valueTemp);

        SendAInteger(1234);
        // Test Area
        //uint8_t testData = 0;

        //ReadI2C(0x20,0x01,1,&testData);

       //SendAInteger(testData);

        PortExpanderWriteOutput(PORTEXPANDER_DEVICE_ADR, PORT_A, 0b00000001);
    }
}
