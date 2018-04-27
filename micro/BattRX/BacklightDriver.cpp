#ifndef __BACKLIGHTDRIVER_CPP_
#define __BACKLIGHTDRIVER_CPP_

#include "BacklightDriver.h"
#include "GlobalSpace.h"

namespace BacklightDriver
{
  bool isSwitchedOn = false;

  __monitor void init()
  {
    LCD_BACKLIGHT_DIR = 1;
    LCD_BACKLIGHT_PORT = 0;

    isSwitchedOn = false;
  }

  bool isBacklightOn()
  {
    return isSwitchedOn;
  }

  void setBacklight(bool _switchOn)
  {
    if (_switchOn)
    {
      LCD_BACKLIGHT_PORT = 1;
      isSwitchedOn = true;
    }
    else
    {
      LCD_BACKLIGHT_PORT = 0;
      isSwitchedOn = false;
    }
  }
}

#endif
