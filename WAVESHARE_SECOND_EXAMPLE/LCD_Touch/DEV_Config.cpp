/******************************************************************************
**************************Hardware interface layer*****************************
* | file          :   DEV_Config.c
* | version     :   V1.0
* | date        :   2017-12-11
* | function    :
    Provide the hardware underlying interface
******************************************************************************/
#include "Arduino.h"
#include "DEV_Config.h"
#include <SPI.h>

/********************************************************************************
  function:    System Init and exit
  note:
    Initialize the communication method
********************************************************************************/
uint8_t System_Init(void)
{
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_DC, OUTPUT);
  pinMode(TP_CS, OUTPUT);
  pinMode(TP_IRQ, INPUT);
  digitalWrite(TP_IRQ, HIGH);

  Serial.begin(115200);
  
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

  return 0;
}

void PWM_SetValue(uint16_t value)
{
    pinMode(LCD_BL, OUTPUT);
    analogWrite(LCD_BL, value);
}

  //  TO-DO - is this specific enough?  Pins below are for Wemos D1 R32, but that
  //  doesn't seem to have its own board.

/********************************************************************************
  function:    Delay function
  note:
    Driver_Delay_ms(xms) : Delay x ms
    Driver_Delay_us(xus) : Delay x us
********************************************************************************/
void Driver_Delay_ms(unsigned long xms)
{
  delay(xms);
}

void Driver_Delay_us(int xus)
{
  for (int j = xus; j > 0; j--);
}