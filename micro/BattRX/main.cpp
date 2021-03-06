#ifndef _MAIN_CPP_
#define _MAIN_CPP_

#include "GlobalSpace.h"
#include "DeviceManager.h"

void Initialization()
{
  __disable_interrupt();

  //Swith off analog comparator
  ACSR=(1<<ACD);  //Analog Comparator: Off

  //__watchdog_reset();
  //WDTCSR = (1<<WDCE) | (1<<WDE);
  //WDTCSR = (1<<WDP3) | (1<<WDE);

  //Enable pullup on all ports

  DDRB = 0x00;
  PORTB = 0xFF ^ ((1<<MEM_SS_BIT) | (1<<SPI_MOSI_BIT) | (1<<SPI_MISO_BIT) | (1<<SPI_SCK_BIT) | (1<<LCD_BACKLIGHT_BIT));
  DDRB = ((1<<MEM_SS_BIT) | (1<<SPI_MOSI_BIT) | (1<<SPI_MISO_BIT) | (1<<SPI_SCK_BIT) | (1<<LCD_BACKLIGHT_BIT));

  DDRC = 0x00;
  PORTC = 0xFF ^ ((1<<LCD_VDD_BIT) | (1<<INDICATOR_LED_BIT) | (1<<LCD_SDA_BIT) | (1<<LCD_SCL_BIT) | (1<<PHOTO1_VDD_BIT) | (1<<PHOTO2_VDD_BIT));
  DDRC = ((1<<LCD_VDD_BIT) | (1<<INDICATOR_LED_BIT) | (1<<LCD_SDA_BIT) | (1<<LCD_SCL_BIT) | (1<<PHOTO1_VDD_BIT) | (1<<PHOTO2_VDD_BIT));

  DDRD = 0x00;
  PORTD = 0xFF ^ ((1<<PHOTO1_IN_BIT) | (1<<PHOTO2_IN_BIT));
  DDRD = ((1<<PHOTO1_IN_BIT) | (1<<PHOTO2_IN_BIT));

  //Disable all external interrupts
  EIMSK = 0x00;

  //Disable all timer interrupts
  TIMSK0 = 0x00;
  TIMSK1 = 0x00;
  TIMSK2 = 0x00;

  //Disable unused modules
  PRR = (1<<PRTWI) | /*(1<<PRTIM0) |*/ (1<<PRTIM1) |                    //Disable TWI, Timer0, Timer1,
        /*(1<<PRTIM2) |*/ (1<<PRSPI) | (1<<PRUSART0) | (1<<PRADC);  //Timer2, SPI, USART0, ADC

  SMCR = 0x00; //Sleep Mode = Idle

  DeviceManager::init();

  __enable_interrupt();
}

int main()
{
  Initialization();

  DeviceManager::run();
}

#endif
