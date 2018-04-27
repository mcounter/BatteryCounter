#ifndef __GLOBALRTC_H_
#define __GLOBALRTC_H_

#include "GlobalRTC.h"

namespace GLOBAL
{
  namespace RTC
  {
    typedef struct
    {
      unsigned short year;
      unsigned char month;    //1-12
      unsigned char day;      //1-31
      unsigned char hour;     //0-23
      unsigned char minute;   //0-59
      unsigned char second;   //0-59
      unsigned char weekDay;  //0-6 (Monday-Sunday)
      bool leapYear;
      bool summerTime;
    } TRTCDateTime;

    typedef enum
    {
      SummerTimeRule_Off = 0,
      SummerTimeRule_On = 1,
      SummerTimeRule_Ukraine = 2,
    } TSummerTimeRule;

    typedef struct
    {
      TSummerTimeRule summerTimeRule;
    } TRTCConfig;

    extern TRTCConfig RTCConfig;
    extern TRTCDateTime RTCDateTime;

    void init(unsigned short _year, unsigned char _month, unsigned char _day,
              unsigned char _hour, unsigned char _minute, unsigned char _second,
              TSummerTimeRule _summerTimeRule);
    void tick();
    void processIdleTime();

    void setDate(unsigned short _year, unsigned char _month, unsigned char _day);
    void setTime(unsigned char _hour, unsigned char _minute, unsigned char _second);
    void setDateTime(unsigned short _year, unsigned char _month, unsigned char _day,
                     unsigned char _hour, unsigned char _minute, unsigned char _second);

    void correctDateTime(TRTCDateTime* _dateTime, bool _direction);
    void setDateTime(TRTCDateTime* _dateTime);

    void setSummerTimeRule(TSummerTimeRule _summerTimeRule);
  }
}

#endif

