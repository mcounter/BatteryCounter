#ifndef __GLOBALADC_H_
#define __GLOBALADC_H_

#include "GlobalSpace.h"

namespace GLOBAL
{
  namespace ADC
  {
    void init(unsigned short _cutOffVoltage);
    void startConversion();
    bool ready();

    void run();

    void setCutOffVoltage(unsigned short _cutOffVoltage);
    bool isBatteryVoltageDetected();
    unsigned short getBatteryCurrentVoltage();
    bool isLowBatteryVoltage();
  };
}

#endif

