#ifndef __TIMER0HANDLER_CPP_
#define __TIMER0HANDLER_CPP_

#include "Timer0Handler.h"
#include "MultyThreading.h"

namespace Timer0Handler
{
  #pragma vector=TIMER0_COMPA_vect
  __interrupt void irqTimer0()
  {
    unsigned char portOn = PORTC | (1<<IR_GENERATOR_BIT);
    unsigned char portOff = portOn ^ (1<<IR_GENERATOR_BIT);

    PORTC = portOn;
    PORTC = portOff;
    __no_operation();
    __no_operation();
    PORTC = portOn;
    PORTC = portOff;
    __no_operation();
    __no_operation();
    PORTC = portOn;
    PORTC = portOff;
    __no_operation();
    __no_operation();
    PORTC = portOn;
    PORTC = portOff;
    __no_operation();
    __no_operation();
    PORTC = portOn;
    PORTC = portOff;
    __no_operation();
    __no_operation();
    PORTC = portOn;
    PORTC = portOff;

    GLOBAL::MultyThreading::tick();
  }

  __monitor void disable()
  {
    TIMSK0 = 0x00;
  }

  __monitor void enable()
  {
    unsigned char curTimerDiscreteness = timerDiscreteness;
    if (GLOBAL::DeviceProfile::DeviceTransmitterConfig.transmitterMode == GLOBAL::DeviceProfile::DeviceTransmitterMode_NoDetetion)
    {
      curTimerDiscreteness *= NODETECTION_PRESCALER_LEVEL;
    }

    TCCR0A = (1<<WGM01);  // CTC mode
    TCCR0B = (1<<CS01);   // div 8
    OCR0A = (((clockFrequency/8) * curTimerDiscreteness)/1000) - 1;
    OCR0B = 0x00;
    TCNT0 = 0x00;

    TIMSK0 = (1<<OCIE0A);
  }

  __monitor void init()
  {
    disable();

    INDICATOR_LED_DIR = 1;
    INDICATOR_LED_PORT = 0;

    enable();
  }
}

#endif

