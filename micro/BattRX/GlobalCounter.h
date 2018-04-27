#ifndef __GLOBALCOUNTER_H_
#define __GLOBALCOUNTER_H_

#include "GlobalRTC.h"

namespace GLOBAL
{
  namespace Counter
  {
    typedef struct
    {
      unsigned long periodNumHour;
      unsigned short InCntHour;
      unsigned short OutCntHour;
      unsigned short NoSensorSecHour;

      unsigned long periodNumDay;
      unsigned short InCntDay;
      unsigned short OutCntDay;
      unsigned long NoSensorSecDay;

      unsigned short periodNumMonth;
      unsigned long InCntMonth;
      unsigned long OutCntMonth;
    } TCounterPeriodData;

    typedef enum
    {
      CounterStatisticProcessStatus_None = 0,
      CounterStatisticProcessStatus_Scheduled = 1,
      CounterStatisticProcessStatus_Processed = 2,
      CounterStatisticProcessStatus_Error = 3,
    } TCounterStatisticProcessStatus;

    typedef enum
    {
      CounterStatisticType_None = 0,
      CounterStatisticType_Hour = 1,
      CounterStatisticType_Day = 2,
      CounterStatisticType_Month = 4,
    } TCounterStatisticType;

    typedef struct
    {
      unsigned long periodNumFrom;
      unsigned long periodNumTo;

      unsigned long curPeriodNum;

      unsigned long InCnt;
      unsigned long OutCnt;

      unsigned long NoSensorSec;

      TCounterStatisticProcessStatus status;
    } TCounterStatisticRecord;

    extern unsigned long totalInCnt;
    extern unsigned long totalOutCnt;
    extern TCounterPeriodData curPeriod;

    void init();
    void run();
    bool ready();

    void addCounter(unsigned short _inCnt, unsigned short _outCnt, unsigned short _noSensorSec);
    void setTotals(unsigned long _totalIn, unsigned long _totalOut);
    void setUpdateCounter();
    bool isUpdateCounter();
    void resetData();

    unsigned short getPeriodNumMonth(unsigned short _year, unsigned char _month);
    unsigned long getPeriodNumDay(unsigned short _year, unsigned char _month, unsigned char _day);
    unsigned long getPeriodNumHour(unsigned short _year, unsigned char _month, unsigned char _day, unsigned char _hour);

    unsigned short getPeriodNumMonth(GLOBAL::RTC::TRTCDateTime* _dateTime);
    unsigned long getPeriodNumDay(GLOBAL::RTC::TRTCDateTime* _dateTime);
    unsigned long getPeriodNumHour(GLOBAL::RTC::TRTCDateTime* _dateTime);

    void getRTCDateTimeMonth(GLOBAL::RTC::TRTCDateTime* _dateTime, unsigned short _periodNum);
    void getRTCDateTimeDay(GLOBAL::RTC::TRTCDateTime* _dateTime, unsigned long _periodNum);
    void getRTCDateTimeHour(GLOBAL::RTC::TRTCDateTime* _dateTime, unsigned long _periodNum);
    bool scheduleStatisticOperation(TCounterStatisticRecord* _statisticRecord, TCounterStatisticType _statisticType);
  }
}

#endif

