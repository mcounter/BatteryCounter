#ifndef __MAINTHREAD_CPP_
#define __MAINTHREAD_CPP_

#include "MainThread.h"
#include "GlobalSpace.h"
#include "KeyBoardDriver.h"
#include "IndicatorDriver.h"
#include "BacklightDriver.h"
#include "UserInterface.h"
#include "PhotoSensor.h"
#include "GlobalRTC.h"
#include "MemAT25Driver.h"
#include "MultyThreading.h"
#include "Timer0Handler.h"
#include "LCDDriver.h"

using namespace GLOBAL::DeviceProfile;

namespace MainThread
{
  bool isDeviceActiveByScheduleCalc = false;

  __monitor void init()
  {
  }

  bool isShiftActive(
    unsigned short _curTime,
    unsigned short _shiftStart,
    unsigned short _shiftEnd,
    bool _allowEqual)
  {
    if (_allowEqual && (_shiftStart == _shiftEnd))
    {
      return true;
    }

    return ((_shiftStart < _shiftEnd) &&
            (_curTime >= _shiftStart) &&
            (_curTime < _shiftEnd)) ||
           ((_shiftStart > _shiftEnd) &&
            ((_curTime >= _shiftStart) ||
             (_curTime < _shiftEnd)));
  }

  __flash unsigned char weekDayMask[7] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40};
  void calcIsDeviceActiveBySchedule()
  {
    if (!((GLOBAL::DeviceProfile::DeviceAdvancedSetup.workWeekMask & 0x80) ||
          (GLOBAL::DeviceProfile::DeviceAdvancedSetup.workWeekMask & weekDayMask[GLOBAL::RTC::RTCDateTime.weekDay])))
    {
      isDeviceActiveByScheduleCalc = false;
      return;
    }

    if (GLOBAL::DeviceProfile::DeviceAdvancedSetup.workDayStruct == WorkDayShiftStructure_WholeDay)
    {
      isDeviceActiveByScheduleCalc = true;
      return;
    }

    unsigned short curTime = (GLOBAL::RTC::RTCDateTime.hour * 60) + GLOBAL::RTC::RTCDateTime.minute;
    bool isShift1 = isShiftActive(curTime,
                                  GLOBAL::DeviceProfile::DeviceAdvancedSetup.shiftStart1,
                                  GLOBAL::DeviceProfile::DeviceAdvancedSetup.shiftEnd1,
                                  true);

    if (isShift1)
    {
      switch (GLOBAL::DeviceProfile::DeviceAdvancedSetup.workDayStruct)
      {
        case WorkDayShiftStructure_Shift1:
        case WorkDayShiftStructure_Shift2:
          isDeviceActiveByScheduleCalc = true;
          return;
      }
    }
    else
    {
      switch (GLOBAL::DeviceProfile::DeviceAdvancedSetup.workDayStruct)
      {
        case WorkDayShiftStructure_Shift1:
        case WorkDayShiftStructure_Shift1Lunch:
          isDeviceActiveByScheduleCalc = false;
          return;
      }
    }

    bool isShift2 = isShiftActive(curTime,
                                  GLOBAL::DeviceProfile::DeviceAdvancedSetup.shiftStart2,
                                  GLOBAL::DeviceProfile::DeviceAdvancedSetup.shiftEnd2,
                                  GLOBAL::DeviceProfile::DeviceAdvancedSetup.workDayStruct == WorkDayShiftStructure_Shift2);

    if (GLOBAL::DeviceProfile::DeviceAdvancedSetup.workDayStruct == WorkDayShiftStructure_Shift1Lunch)
    {
      isDeviceActiveByScheduleCalc = isShift1 && (!isShift2);
    }
    else
    {
      isDeviceActiveByScheduleCalc = isShift1 || isShift2;
    }
  }

  bool isDeviceActiveBySchedule()
  {
    return isDeviceActiveByScheduleCalc;
  }

  void enablePhoto()
  {
    if (!PhotoSensor::enabled())
    {
      PhotoSensor::enable();
    }
  }

  void disablePhoto()
  {
    if (PhotoSensor::enabled())
    {
      PhotoSensor::disable();
    }
  }

  void enablePhotoBySchedule()
  {
    if (isDeviceActiveByScheduleCalc)
    {
      enablePhoto();
    }
    else
    {
      disablePhoto();
    }
  }

  void checkBacklight()
  {
    if (GLOBAL::DeviceProfile::DeviceAdvancedSetup.backlight &&
        UserInterface::enabled() &&
        UserInterface::menuActive())
    {
      if (!BacklightDriver::isBacklightOn())
      {
        BacklightDriver::setBacklight(true);
      }
    }
    else
    {
      if (BacklightDriver::isBacklightOn())
      {
        BacklightDriver::setBacklight(false);
      }
    }
  }

  void checkPhotoSensor()
  {
    if (UserInterface::enabled() && UserInterface::menuActive())
    {
      if (UserInterface::photoActive())
      {
        enablePhoto();
      }
      else if (GLOBAL::DeviceProfile::DeviceAdvancedSetup.batterySaveMode & DeviceBatterySaveMode_NoCount)
      {
        disablePhoto();
      }
      else
      {
        enablePhotoBySchedule();
      }
    }
    else
    {
      enablePhotoBySchedule();
    }
  }

  void updateDeviceMode()
  {
    bool uiRequest = KeyBoardDriver::getUIRequest();

    if (!UserInterface::enabled())
    {
      UserInterface::leaveInterface();
    }

    if (uiRequest && (!UserInterface::enabled()))
    {
      UserInterface::enable(true);
    }

    checkPhotoSensor();
    checkBacklight();
  }

  void run()
  {
    if (DeviceStatusCode == DeviceStatusCode_Initialization)
    {
      IndicatorDriver::schedule(2, 250, 500);

      DeviceStatusCode = DeviceStatusCode_NormalMode;
      calcIsDeviceActiveBySchedule();
    }

    updateDeviceMode();

    if ((!isDeviceActiveByScheduleCalc) &&
        (!UserInterface::enabled()) &&
        (!PhotoSensor::enabled()) &&
        (!(MemAT25Driver::enabled() && (!MemAT25Driver::ready()))) &&
        (IndicatorDriver::ready()))
    {
      if (Timer0Handler::enabled() && GLOBAL::MultyThreading::canBeDisabled())
      {
        Timer0Handler::disable();
      }

      if (!Timer0Handler::enabled())
      {
        MCUCR |= (1<<SE); //Enable go to sleep mode
        __sleep();        //Go to sleep mode

        __no_operation();
        __no_operation();
        __no_operation();
        __no_operation();
        __no_operation();
      }
    }
  }
}

#endif
