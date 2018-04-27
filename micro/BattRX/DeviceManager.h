#ifndef __DEVICEMANAGER_H_
#define __DEVICEMANAGER_H_

#include "GlobalSpace.h"

namespace DeviceManager
{
  void init();
  void run();

  void saveDeviceStatus();
  void saveTotalsInOut(unsigned long _totalInCnt, unsigned long _totalOutCnt);
  void saveDeviceCounterConfig();
  void saveDeviceAdvancedSetup();
  void saveUserInterfaceSetup();

  void incPwdFails();
  bool checkPasswordMaster(unsigned char* _password);
  bool checkPasswordReports(unsigned char* _password);
  void setPasswordMaster(unsigned char* _password);
  void setPasswordReports(unsigned char* _password);

  void resetCounters();
  void resetToFactoryDefaults();
  void resetData();
  void resetFull();

  unsigned long getTotalRestarts();
  unsigned long getTotalDataReset();
  unsigned long getTotalFactoryReset();
  unsigned long getTotalPwdFails();
}

#endif

