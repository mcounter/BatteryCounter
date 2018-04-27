#ifndef __GLOBALDEVICEPROFILE_CPP_
#define __GLOBALDEVICEPROFILE_CPP_

#include "GlobalDeviceProfile.h"

namespace GLOBAL
{
  namespace DeviceProfile
  {
    TApplicationVersion ApplicationVersion;
    TDeviceSerialNumber DeviceSerialNumber;
    TDeviceCounterConfig DeviceCounterConfig;
    TDeviceAdvancedSetup DeviceAdvancedSetup;
    TUserInterfaceSetup UserInterfaceSetup;

    TDeviceStatusCode DeviceStatusCode;

    unsigned char MemorySecureTemplate[EXT_MEMORY_SEGMENTSIZE];
  }
}

#endif

