#ifndef __INDICATORDRIVER_CPP_
#define __INDICATORDRIVER_CPP_

#include "IndicatorDriver.h"
#include "GlobalSpace.h"
#include "MultyThreading.h"

#define INDICATOR_BLINK_DISCRETENESS_MS       (50)

namespace IndicatorDriver
{
  unsigned char blinkNum = 0;
  unsigned char blinkLightLng = 0;
  unsigned char blinkPauseLng = 0;

  bool blinkStatusOn = false;

  __monitor void init()
  {
    INDICATOR_LED_DIR = 1;
    INDICATOR_LED_PORT = 0;

    blinkNum = 0;
    blinkStatusOn = 0;
  }

  void switchOn()
  {
    INDICATOR_LED_DIR = 1;
    INDICATOR_LED_PORT = 1;

    blinkStatusOn = true;

    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_INDICATOR_WAITINGTIMER, blinkLightLng * INDICATOR_BLINK_DISCRETENESS_MS);
  }

  void switchOff()
  {
    INDICATOR_LED_DIR = 1;
    INDICATOR_LED_PORT = 0;

    blinkStatusOn = false;

    if (blinkNum > 1)
    {
      blinkNum--;
      GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_INDICATOR_WAITINGTIMER, blinkPauseLng * INDICATOR_BLINK_DISCRETENESS_MS);
    }
    else
    {
      blinkNum = 0;
    }
  }

  void schedule(unsigned char _blinkNum, unsigned short _blinkLightLng, unsigned short _blinkPauseLng)
  {
    blinkNum = _blinkNum;
    blinkLightLng = _blinkLightLng / INDICATOR_BLINK_DISCRETENESS_MS;
    blinkPauseLng = _blinkPauseLng / INDICATOR_BLINK_DISCRETENESS_MS;

    switchOn();
  }

  bool ready()
  {
    return (blinkNum <= 0);
  }

  void run()
  {
    if (blinkNum <= 0)
    {
      return;
    }

    if (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_INDICATOR_WAITINGTIMER))
    {
      if (blinkStatusOn)
      {
        switchOff();
      }
      else
      {
        switchOn();
      }
    }
  }
}

#endif
