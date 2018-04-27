#ifndef __MULTYTHREADING_CPP_
#define __MULTYTHREADING_CPP_

#include "MultyThreading.h"

namespace GLOBAL
{
  namespace MultyThreading
  {
    volatile unsigned short counterValue = 0;

#if (GLOBALTIMERS_COUNT > 0)
      unsigned short Timers[GLOBALTIMERS_COUNT];
#endif

#if (GLOBALCLOCKS_COUNT > 0)
      unsigned short Clocks[GLOBALCLOCKS_COUNT];
#endif

    __monitor void tick()
    {
      counterValue += timerDiscreteness;
    }

    __monitor unsigned short getIdleTime()
    {
      unsigned short curIdleTime = counterValue;
      if (GLOBAL::DeviceProfile::DeviceTransmitterConfig.transmitterMode == GLOBAL::DeviceProfile::DeviceTransmitterMode_NoDetetion)
      {
        curIdleTime *= NODETECTION_PRESCALER_LEVEL;
      }

      counterValue = 0;

      return curIdleTime;
    }

    __monitor void clearTicks()
    {
      counterValue = 0;
    }

    void processIdleTime()
    {
      unsigned short curIdleTime = getIdleTime();

      if (!curIdleTime)
      {
        return;
      }

#if (GLOBALTIMERS_COUNT > 0)
      for (unsigned char i = 0; i < GLOBALTIMERS_COUNT; i++)
      {
        Timers[i] = (Timers[i] > curIdleTime) ? Timers[i] - curIdleTime : 0;
      }
#endif

#if (GLOBALCLOCKS_COUNT > 0)
      for (unsigned char i = 0; i < GLOBALCLOCKS_COUNT; i++)
      {
        Clocks[i] += curIdleTime;
      }
#endif
    }

    bool canBeDisabled()
    {
#if (GLOBALCLOCKS_COUNT > 0)
      return false;
#else
      for (unsigned char i = 0; i < GLOBALTIMERS_COUNT; i++)
      {
        if (Timers[i] > 0)
        {
          return false;
        }
      }

      return true;
#endif
    }

#if (GLOBALTIMERS_COUNT > 0)
    unsigned short getTimer(unsigned char _timerNum)
    {
      return Timers[_timerNum];
    }

    void setTimer(unsigned char _timerNum, unsigned short _value)
    {
      Timers[_timerNum] = _value;
    }
#endif

#if (GLOBALCLOCKS_COUNT > 0)
    unsigned short getClock(unsigned char _clockNum)
    {
      return Clocks[_clockNum];
    }

    unsigned short getClockIdleTime(unsigned char _clockNum)
    {
      unsigned short idleTime = Clocks[_clockNum];
      Clocks[_clockNum] = 0;

      return idleTime;
    }
#endif

    void init()
    {
#if (GLOBALTIMERS_COUNT > 0)
      for (unsigned char i = 0; i < GLOBALTIMERS_COUNT; i++)
      {
        Timers[i] = 0;
      }
#endif

#if (GLOBALCLOCKS_COUNT > 0)
      for (unsigned char i = 0; i < GLOBALCLOCKS_COUNT; i++)
      {
        Clocks[i] = 0;
      }
#endif
    }
  }
}

#endif

