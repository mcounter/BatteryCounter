#ifndef __TIMER0HANDLER_CPP_
#define __TIMER0HANDLER_CPP_

#include "Timer0Handler.h"
#include "MultyThreading.h"
#include "PhotoSensor.h"

namespace Timer0Handler
{
  bool isEnabled = false;

  #pragma vector=TIMER0_COMPA_vect
  __interrupt void irqTimer0()
  {
    GLOBAL::MultyThreading::tick();
    PhotoSensor::processIdleTime();
  }

  __monitor void disable()
  {
    isEnabled = false;
    TIMSK0 = 0x00;
  }

  __monitor void enable()
  {
    if (isEnabled)
    {
      return;
    }

    TCNT0 = 0x00;
    TIMSK0 = (1<<OCIE0A);

    isEnabled = true;
  }

  bool enabled()
  {
    return isEnabled;
  }

  __monitor void init()
  {
    disable();

    TCCR0A = (1<<WGM01);  // CTC mode
    TCCR0B = (1<<CS01);   // div 8
    OCR0A = (((clockFrequency/8) * timerDiscreteness)/1000) - 1;
    OCR0B = 0x00;
    TCNT0 = 0x00;
  }
}

#endif

