#ifndef __PHOTOSENSOR_H_
#define __PHOTOSENSOR_H_

#include "GlobalSpace.h"

namespace PhotoSensor
{
  void init();
  void processIdleTime();

  void disable();
  void enable();
  bool enabled();

  unsigned char getCounterQualityPct1();
  unsigned char getCounterQualityPct2();
};

#endif

