
/*
 * Test project for I2C functions
 * Used Hardware:
 * STM32L476RG
 * Bosch BMP280
 *
 */

#include <stm32l4xx.h>
#include <system_stm32l4xx.h>


#include "LCDFunctions.h"
#include "I2C.h"
#include "BMP280.h"

#define I2C_SCL_Pin 8
#define I2C_SCL_Port GPIOB

#define I2C_SDA_Pin 9
#define I2C_SDA_Port GPIOB

#define BMP280_DEVICE_ADR  (0x77)

uint32_t valuePress;
int32_t valueTemp;

uint8_t testData[5];


int main(void)
{

  LCDSetup();

 InitI2C(I2C_SCL_Port, I2C_SCL_Pin, I2C_SDA_Port, I2C_SDA_Pin);

  InitBMP280(BMP280_DEVICE_ADR);

  GetSensorCalibrationData(BMP280_DEVICE_ADR);



  while (1)
  {



    GetSensorValues(BMP280_DEVICE_ADR, &valuePress, &valueTemp);


    LCDSetCursorLocation(0, 0);
    LCDSendInteger(valueTemp / 100);
    LCDSendString(".");
    LCDSendInteger((valueTemp / 10) % 10);
    LCDSendString(" C");
    LCDSetCursorLocation(0, 1);

    LCDSendInteger(valuePress/ 100);
    LCDSendString(".");
    LCDSendInteger((valuePress / 10) % 10);
    LCDSendString(" hPa");



  }

}
