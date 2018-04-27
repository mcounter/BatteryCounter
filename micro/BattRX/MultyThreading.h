#ifndef __MULTYTHREADING_H_
#define __MULTYTHREADING_H_

#include "GlobalSpace.h"

namespace GLOBAL
{
  namespace MultyThreading
  {
    void init();
    void tick();
    void processIdleTime();

    unsigned short getTimer(unsigned char _timerNum);
    void setTimer(unsigned char _timerNum, unsigned short _value);
    unsigned short getClock(unsigned char _clockNum);
    unsigned short getClockIdleTime(unsigned char _clockNum);
    bool canBeDisabled();
  }
}

#endif

