#ifndef __BACKLIGHTDRIVER_H_
#define __BACKLIGHTDRIVER_H_

namespace BacklightDriver
{
  void init();

  bool isBacklightOn();
  void setBacklight(bool _switchOn);
}

#endif
