#ifndef __MAINTHREAD_H_
#define __MAINTHREAD_H_

#include "GlobalSpace.h"

namespace MainThread
{
  void init();
  void run();

  bool isDeviceActiveBySchedule();
  void calcIsDeviceActiveBySchedule();
}

#endif
