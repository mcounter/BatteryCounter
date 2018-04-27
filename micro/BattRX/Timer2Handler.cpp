#ifndef __TIMER2HANDLER_CPP_
#define __TIMER2HANDLER_CPP_

#include "Timer2Handler.h"
#include "GlobalRTC.h"

namespace Timer2Handler
{
  #pragma vector=TIMER2_OVF_vect
  __interrupt void irqTimer2()
  {
    GLOBAL::RTC::tick();
  }

  __monitor void init()
  {
    TIMSK2 = 0x00;
    ASSR = (1<<AS2);

    TCCR2A = 0x00; // Normal mode
    TCCR2B = (1<<CS20) | (1<<CS22); //div = 128
    OCR2A = 0xFF;
    OCR2B = 0xFF;
    TCNT2 = 0x00;

    while (ASSR & ((1<<TCN2UB) | (1<<OCR2AUB) | (1<<OCR2BUB) | (1<<TCR2AUB) | (1<<TCR2BUB)));

    TIMSK2 = (1<<TOIE2);
  }
}

#endif

