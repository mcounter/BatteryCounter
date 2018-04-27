#ifndef __INDICATORDRIVER_H_
#define __INDICATORDRIVER_H_

namespace IndicatorDriver
{
  void init();
  void run();
  bool ready();

  void schedule(unsigned char _blinkNum, unsigned short _blinkLightLng, unsigned short _blinkPauseLng);
}

#endif
