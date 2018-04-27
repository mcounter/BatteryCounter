#ifndef __GLOBALRTC_CPP_
#define __GLOBALRTC_CPP_

#include "GlobalRTC.h"
#include "GlobalSpace.h"
#include "GlobalCounter.h"
#include "DeviceManager.h"
#include "GlobalADC.h"
#include "MainThread.h"
#include "IndicatorDriver.h"

#define LOW_BATTERY_CHECK_PERIOD_MIN        (15)

namespace GLOBAL
{
  namespace RTC
  {
    const unsigned char DaysInMonth[2][13] = {{0,31,28,31,30,31,30,31,31,30,31,30,31},
                                              {0,31,29,31,30,31,30,31,31,30,31,30,31}};

    TRTCConfig RTCConfig;
    TRTCDateTime RTCDateTime;
    volatile unsigned char counterValue = 0;

    unsigned char cycleTimerLowBatteryCheck = LOW_BATTERY_CHECK_PERIOD_MIN;

    bool isLeapYear(unsigned short _year)
    {
      return (((_year % 4) == 0) && ((_year % 100) != 0)) || ((_year % 400) == 0);
    }

    unsigned char weekDay(unsigned short _year, unsigned char _month, unsigned char _day)
    {
      unsigned char a = (14 - _month) / 12;
      unsigned short y = _year - a;
      unsigned short m = _month + (12 * a) - 2;

      return (((unsigned short)_day) - 1 + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    bool isSummerTime(TRTCDateTime* _dateTime, bool _applied = false)
    {
      unsigned char changeDate;

      switch (RTCConfig.summerTimeRule)
      {
        case SummerTimeRule_On:
          return true;

        case SummerTimeRule_Ukraine:
          if ((_dateTime->month > 3) && (_dateTime->month < 10))
          {
            return true;
          }
          else
          if (_dateTime->month == 3)
          {
            changeDate = 31 - ((_dateTime->weekDay + 31 - _dateTime->day + 1) % 7);
            return ((_dateTime->day > changeDate) ||
                    ((_dateTime->day = changeDate) && (_dateTime->hour >= (_applied ? 4 : 3))));
          }
          else
          if (_dateTime->month == 10)
          {
            changeDate = 31 - ((_dateTime->weekDay + 31 - _dateTime->day + 1) % 7);
            return ((_dateTime->day < changeDate) ||
                    ((_dateTime->day = changeDate) && (_dateTime->hour < (_applied ? 4 : 3))));
          }

          return false;
      }

      return false;
    }

    __monitor void tick()
    {
      counterValue++;
    }

    __monitor unsigned char getIdleTime()
    {
      unsigned char curIdleTime = counterValue;
      counterValue = 0;

      return curIdleTime;
    }

    __monitor void clearTicks()
    {
      counterValue = 0;
    }

    void processIdleTime()
    {
      unsigned char curIdleTime = getIdleTime();

      if (!curIdleTime)
      {
        return;
      }

      bool isHourChanged = false;
      bool isMinuteChanged = false;

      while (curIdleTime)
      {
        unsigned char freeSeconds = 60 - RTCDateTime.second;

        if (curIdleTime < freeSeconds)
        {
          RTCDateTime.second += curIdleTime;
          curIdleTime = 0;
        }
        else
        {
          RTCDateTime.second = 0;
          curIdleTime -= freeSeconds;
          isMinuteChanged = true;

          if (cycleTimerLowBatteryCheck > 0)
          {
            cycleTimerLowBatteryCheck--;
          }

          if (RTCDateTime.minute < 59)
          {
            RTCDateTime.minute++;
          }
          else
          {
            RTCDateTime.minute = 0;
            isHourChanged = true;

            if (RTCDateTime.hour < 23)
            {
              RTCDateTime.hour++;
            }
            else
            {
              RTCDateTime.hour = 0;
              RTCDateTime.weekDay = (RTCDateTime.weekDay + 1) % 7;

              if (RTCDateTime.day < DaysInMonth[RTCDateTime.leapYear][RTCDateTime.month])
              {
                RTCDateTime.day++;
              }
              else
              {
                RTCDateTime.day = 1;

                if (RTCDateTime.month < 12)
                {
                  RTCDateTime.month = 1;
                  RTCDateTime.year++;

                  RTCDateTime.leapYear = isLeapYear(RTCDateTime.year);
                }
              }
            }

            bool newSummerTime = isSummerTime(&RTCDateTime, RTCDateTime.summerTime);
            if (newSummerTime != RTCDateTime.summerTime)
            {
              if (newSummerTime)
              {
                if (RTCDateTime.hour < 23)
                {
                  RTCDateTime.summerTime = true;
                  RTCDateTime.hour++;
                }
              }
              else
              {
                if (RTCDateTime.hour > 0)
                {
                  RTCDateTime.summerTime = false;
                  RTCDateTime.hour--;
                }
              }
            }
          }
        }
      }

      if (!cycleTimerLowBatteryCheck)
      {
        cycleTimerLowBatteryCheck = LOW_BATTERY_CHECK_PERIOD_MIN;

        if (GLOBAL::ADC::isLowBatteryVoltage() && MainThread::isDeviceActiveBySchedule())
        {
          IndicatorDriver::schedule(3, 150, 250);
        }
      }

      if (isMinuteChanged)
      {
        MainThread::calcIsDeviceActiveBySchedule();
      }

      if (isHourChanged)
      {
        GLOBAL::Counter::setUpdateCounter();
        DeviceManager::saveDeviceStatus();
        GLOBAL::ADC::startConversion();
      }
    }

    void setDateTime(bool _setDate, unsigned short _year, unsigned char _month, unsigned char _day,
                     bool _setTime, unsigned char _hour, unsigned char _minute, unsigned char _second)
    {
      if (_setDate)
      {
        RTCDateTime.year = (_year > 1900) ? (_year % 10000) : 1900;
        RTCDateTime.leapYear = isLeapYear(RTCDateTime.year);
        RTCDateTime.month = ((_month - 1) % 12) + 1;
        RTCDateTime.day = ((_day - 1) % DaysInMonth[RTCDateTime.leapYear][RTCDateTime.month]) + 1;
        RTCDateTime.weekDay = weekDay(RTCDateTime.year, RTCDateTime.month, RTCDateTime.day);
      }

      if (_setTime)
      {
        RTCDateTime.hour = _hour % 24;
        RTCDateTime.minute = _minute % 60;
        RTCDateTime.second = _second % 60;
      }

      RTCDateTime.summerTime = isSummerTime(&RTCDateTime, true);

      clearTicks();

      MainThread::calcIsDeviceActiveBySchedule();
      GLOBAL::Counter::setUpdateCounter();
      DeviceManager::saveDeviceStatus();
    }

    void setSummerTimeRule(TSummerTimeRule _summerTimeRule)
    {
      RTCConfig.summerTimeRule = _summerTimeRule;
      RTCDateTime.summerTime = isSummerTime(&RTCDateTime, true);

      MainThread::calcIsDeviceActiveBySchedule();
      GLOBAL::Counter::setUpdateCounter();
      DeviceManager::saveDeviceStatus();
    }

    void correctDateTime(TRTCDateTime* _dateTime, bool _direction)
    {
      if ((_dateTime->year < 2000) || (_dateTime->year >= 2100))
      {
        _dateTime->year = _direction ? 2000 : 2099;
      }

      _dateTime->leapYear = isLeapYear(_dateTime->year);

      if ((_dateTime->month < 1) || (_dateTime->month > 12))
      {
        _dateTime->month = _direction ? 1 : 12;
      }

      if ((_dateTime->day < 1) || (_dateTime->day > DaysInMonth[_dateTime->leapYear][_dateTime->month]))
      {
        _dateTime->day = _direction ? 1 : DaysInMonth[_dateTime->leapYear][_dateTime->month];
      }

      if (_dateTime->hour >= 24)
      {
        _dateTime->hour = _direction ? 0 : 23;
      }

      if (_dateTime->minute >= 60)
      {
        _dateTime->minute = _direction ? 0 : 59;
      }

      if (_dateTime->second >= 60)
      {
        _dateTime->second = _direction ? 0 : 59;
      }

      _dateTime->summerTime = isSummerTime(_dateTime, true);
    }

    void setDate(unsigned short _year, unsigned char _month, unsigned char _day)
    {
      setDateTime(true, _year, _month, _day, false, 0, 0, 0);
    }

    void setTime(unsigned char _hour, unsigned char _minute, unsigned char _second)
    {
      setDateTime(false, 0, 0, 0, true, _hour, _minute, _second);
    }

    void setDateTime(unsigned short _year, unsigned char _month, unsigned char _day,
                     unsigned char _hour, unsigned char _minute, unsigned char _second)
    {
      setDateTime(true, _year, _month, _day, true, _hour, _minute, _second);
    }

    void setDateTime(TRTCDateTime* _dateTime)
    {
      correctDateTime(_dateTime, false);
      setDateTime(true, _dateTime->year, _dateTime->month, _dateTime->day,
                  true, _dateTime->hour, _dateTime->minute, _dateTime->second);
    }

    void init(unsigned short _year, unsigned char _month, unsigned char _day,
              unsigned char _hour, unsigned char _minute, unsigned char _second,
              TSummerTimeRule _summerTimeRule)
    {
      RTCConfig.summerTimeRule = _summerTimeRule;
      setDateTime(_year, _month, _day, _hour, _minute, _second);
    }
  }
}

#endif

