#ifndef __GLOBALCOUNTER_CPP_
#define __GLOBALCOUNTER_CPP_

#include "GlobalCounter.h"
#include "GlobalSpace.h"
#include "MemAT25Driver.h"
#include "DeviceManager.h"

#define COUNTER_MAX_RW_TRY_NUM          (3)

namespace GLOBAL
{
  namespace Counter
  {
    typedef enum
    {
      CounterStatus_Normal = 0,
      CounterStatus_Load = 1,
      CounterStatus_Save = 2,
      CounterStatus_GetStatistic = 3,
    } TCounterStatus;

    typedef enum
    {
      CounterOperationStatus_Scheduling = 0,
      CounterOperationStatus_Waiting = 1,
    } TCounterOperationStatus;

    TCounterPeriodData curPeriod;
    unsigned long totalInCnt;
    unsigned long totalOutCnt;

    TCounterPeriodData prevPeriod;
    unsigned char updateCounter = CounterStatisticType_None;

    TCounterStatus counterStatus = CounterStatus_Normal;
    unsigned char counterSubStatusSet = CounterStatisticType_None;
    TCounterOperationStatus counterOperationStatus = CounterOperationStatus_Scheduling;
    unsigned char tryNum = 0;

    TCounterStatisticRecord* curStatisticRecord;

    unsigned short getPeriodNumMonth(unsigned short _year, unsigned char _month)
    {
      return ((_year - 2000) * 12) + (_month - 1);
    }

    unsigned long getPeriodNumDay(unsigned short _year, unsigned char _month, unsigned char _day)
    {
      unsigned long a = (14 - _month) / 12;
      unsigned long y = _year + 4800 - a;
      unsigned long m = _month + (12 * a) - 3;

      return (_day + (((153 * m) + 2) / 5) + (365 * y) + (y / 4) - (y / 100) + (y / 400) - 32045 - 2451544);
    }

    unsigned long getPeriodNumHour(unsigned short _year, unsigned char _month, unsigned char _day, unsigned char _hour)
    {
      return (getPeriodNumDay(_year, _month, _day) * 24) + _hour;
    }

    unsigned short getPeriodNumMonth(GLOBAL::RTC::TRTCDateTime* _dateTime)
    {
      return getPeriodNumMonth(
        _dateTime->year,
        _dateTime->month);
    }

    unsigned long getPeriodNumDay(GLOBAL::RTC::TRTCDateTime* _dateTime)
    {
      return getPeriodNumDay(
        _dateTime->year,
        _dateTime->month,
        _dateTime->day);
    }

    unsigned long getPeriodNumHour(GLOBAL::RTC::TRTCDateTime* _dateTime)
    {
      return getPeriodNumHour(
        _dateTime->year,
        _dateTime->month,
        _dateTime->day,
        _dateTime->hour);
    }

    void getRTCDateTimeMonth(GLOBAL::RTC::TRTCDateTime* _dateTime, unsigned short _periodNum)
    {
      _dateTime->month = (_periodNum % 12) + 1;
      _dateTime->year = (_periodNum / 12) + 2000;
    }

    void getRTCDateTimeDay(GLOBAL::RTC::TRTCDateTime* _dateTime, unsigned long _periodNum)
    {
      _periodNum = _periodNum + 2451544;

      unsigned long tmp = _periodNum + 32044;
      unsigned long b = ((tmp << 2) + 3) / 146097;
      tmp = tmp - ((146097 * b) >> 2);
      unsigned long d = ((tmp << 2) + 3) / 1461;
      tmp = tmp - ((1461 * d) >> 2);
      unsigned long m = ((5 * tmp) + 2) / 153;

      _dateTime->day = tmp - (((153 * m) + 2) / 5) + 1;
      _dateTime->month = m + 3 - (12 * (m / 10));
      _dateTime->year = (100 * b) + d - 4800 + (m / 10);
      _dateTime->weekDay = _periodNum % 7;
    }

    void getRTCDateTimeHour(GLOBAL::RTC::TRTCDateTime* _dateTime, unsigned long _periodNum)
    {
      _dateTime->hour = _periodNum % 24;

      getRTCDateTimeDay(_dateTime, _periodNum / 24);
    }

    __monitor void getCurPeriodsNum(unsigned long* _periodNumHour, unsigned long* _periodNumDay, unsigned short* _periodNumMonth)
    {
      *_periodNumHour = getPeriodNumHour(
        GLOBAL::RTC::RTCDateTime.year,
        GLOBAL::RTC::RTCDateTime.month,
        GLOBAL::RTC::RTCDateTime.day,
        GLOBAL::RTC::RTCDateTime.hour);

      *_periodNumDay = *_periodNumHour / 24;

      *_periodNumMonth = getPeriodNumMonth(
        GLOBAL::RTC::RTCDateTime.year,
        GLOBAL::RTC::RTCDateTime.month);
    }

    __monitor void addCounterHour(unsigned short _inCnt, unsigned short _outCnt, unsigned short _noSensorSec)
    {
      curPeriod.InCntHour += _inCnt;
      curPeriod.OutCntHour += _outCnt;
      curPeriod.NoSensorSecHour += _noSensorSec;

      if (curPeriod.NoSensorSecHour > 3600)
      {
        curPeriod.NoSensorSecHour = 3600;
      }
    }

    __monitor void addCounterDay(unsigned short _inCnt, unsigned short _outCnt, unsigned short _noSensorSec)
    {
      curPeriod.InCntDay += _inCnt;
      curPeriod.OutCntDay += _outCnt;
      curPeriod.NoSensorSecDay += _noSensorSec;

      if (curPeriod.NoSensorSecDay > 86400)
      {
        curPeriod.NoSensorSecDay = 86400;
      }
    }

    __monitor void addCounterMonth(unsigned short _inCnt, unsigned short _outCnt)
    {
      curPeriod.InCntMonth += _inCnt;
      curPeriod.OutCntMonth += _outCnt;
    }

    __monitor void addCounter(unsigned short _inCnt, unsigned short _outCnt, unsigned short _noSensorSec)
    {
      addCounterHour(_inCnt, _outCnt, _noSensorSec);
      addCounterDay(_inCnt, _outCnt, _noSensorSec);
      addCounterMonth(_inCnt, _outCnt);

      totalInCnt += _inCnt;
      totalOutCnt += _outCnt;
    }

    __monitor void setTotals(unsigned long _totalIn, unsigned long _totalOut)
    {
      totalInCnt = _totalIn;
      totalOutCnt = _totalOut;
    }

    void scheduleCounterOperation(TCounterStatus _operation, unsigned char _subStatusSet)
    {
      counterStatus = _operation;
      counterSubStatusSet = _subStatusSet;
      counterOperationStatus = CounterOperationStatus_Scheduling;
      tryNum = 0;
    }

    __monitor void init()
    {
      memset(&prevPeriod, 0, sizeof(TCounterPeriodData));
      memset(&curPeriod, 0, sizeof(TCounterPeriodData));

      getCurPeriodsNum(&(curPeriod.periodNumHour), &(curPeriod.periodNumDay), &(curPeriod.periodNumMonth));

      updateCounter = CounterStatisticType_None;
      scheduleCounterOperation(CounterStatus_Load, CounterStatisticType_Hour | CounterStatisticType_Day | CounterStatisticType_Month);
    }

    __monitor bool isUpdateCounter()
    {
      return updateCounter != CounterStatisticType_None;
    }

    __monitor void setUpdateCounter()
    {
      updateCounter = CounterStatisticType_Hour | CounterStatisticType_Day | CounterStatisticType_Month;
    }

    __monitor void resetData()
    {
      curPeriod.InCntHour = 0;
      curPeriod.OutCntHour = 0;
      curPeriod.NoSensorSecHour = 0;

      curPeriod.InCntDay = 0;
      curPeriod.OutCntDay = 0;
      curPeriod.NoSensorSecDay = 0;

      curPeriod.InCntMonth = 0;
      curPeriod.OutCntMonth = 0;

      totalInCnt = 0;
      totalOutCnt = 0;

      setUpdateCounter();
    }

    __monitor void saveCounter()
    {
      DeviceManager::saveTotalsInOut(totalInCnt, totalOutCnt);

      unsigned long curPeriodNumHour;
      unsigned long curPeriodNumDay;
      unsigned short curPeriodNumMonth;

      getCurPeriodsNum(&curPeriodNumHour, &curPeriodNumDay, &curPeriodNumMonth);

      if (curPeriodNumHour == curPeriod.periodNumHour)
      {
        prevPeriod = curPeriod;
        scheduleCounterOperation(CounterStatus_Save, CounterStatisticType_Hour | CounterStatisticType_Day | CounterStatisticType_Month);
      }
      else if (curPeriodNumHour > curPeriod.periodNumHour)
      {
        prevPeriod = curPeriod;

        unsigned char curUpdateCounter = CounterStatisticType_Hour;

        curPeriod.periodNumHour = curPeriodNumHour;
        curPeriod.InCntHour = 0;
        curPeriod.OutCntHour = 0;
        curPeriod.NoSensorSecHour = 0;

        if (curPeriod.periodNumDay != curPeriodNumDay)
        {
          curPeriod.periodNumDay = curPeriodNumDay;
          curPeriod.InCntDay = 0;
          curPeriod.OutCntDay = 0;
          curPeriod.NoSensorSecDay = 0;

          curUpdateCounter |= CounterStatisticType_Day;
        }

        if (curPeriod.periodNumMonth != curPeriodNumMonth)
        {
          curPeriod.periodNumMonth = curPeriodNumMonth;
          curPeriod.InCntMonth = 0;
          curPeriod.OutCntMonth = 0;

          curUpdateCounter |= CounterStatisticType_Month;
        }

        scheduleCounterOperation(CounterStatus_Save, curUpdateCounter);

        updateCounter = curUpdateCounter;
      }
      else
      {
        unsigned char curUpdateCounter = CounterStatisticType_Hour;

        curPeriod.periodNumHour = curPeriodNumHour;

        if (curPeriod.periodNumDay != curPeriodNumDay)
        {
          curPeriod.periodNumDay = curPeriodNumDay;
          curUpdateCounter |= CounterStatisticType_Day;
        }

        if (curPeriod.periodNumMonth != curPeriodNumMonth)
        {
          curPeriod.periodNumMonth = curPeriodNumMonth;
          curUpdateCounter |= CounterStatisticType_Month;
        }

        scheduleCounterOperation(CounterStatus_Load, curUpdateCounter);

        updateCounter = curUpdateCounter;
      }
    }

    bool enableMemory()
    {
      if (!MemAT25Driver::enabled())
      {
        MemAT25Driver::enable();
      }

      return MemAT25Driver::ready();
    }

    void startOperation(MemAT25Driver::TMemAT25Operation _memOperation, MemAT25Driver::TMemAT25DataSegment _dataSegment)
    {
      MemAT25Driver::startMemOperation(_memOperation, _dataSegment);
      counterOperationStatus = CounterOperationStatus_Waiting;
    }

    void finishOperation()
    {
      counterStatus = CounterStatus_Normal;

      if (MemAT25Driver::enabled())
      {
        MemAT25Driver::disable();
      }
    }

    void retryOperation()
    {
      tryNum++;

      if (tryNum <= COUNTER_MAX_RW_TRY_NUM)
      {
        counterOperationStatus = CounterOperationStatus_Scheduling;
      }
      else
      {
        finishOperation();
      }
    }

    void operationLoadSave()
    {
      if (counterOperationStatus == CounterOperationStatus_Scheduling)
      {
        if (counterSubStatusSet == CounterStatisticType_None)
        {
          finishOperation();
        }
        else
        if (enableMemory())
        {
          MemAT25Driver::TMemAT25Operation curMemAT25Operation = MemAT25Driver::MemAT25Operation_ReadValue;
          MemAT25Driver::TMemAT25DataSegment curMemAT25DataSegment = MemAT25Driver::MemAT25DataSegment_Hour;

          if (counterStatus == CounterStatus_Load)
          {
            MemAT25Driver::counterValue = curPeriod;
            curMemAT25Operation = MemAT25Driver::MemAT25Operation_ReadValue;
          }
          else
          {
            MemAT25Driver::counterValue = prevPeriod;
            curMemAT25Operation = MemAT25Driver::MemAT25Operation_WriteValue;
          }

          if (counterSubStatusSet & CounterStatisticType_Hour)
          {
            curMemAT25DataSegment = MemAT25Driver::MemAT25DataSegment_Hour;
          }
          else
          if (counterSubStatusSet & CounterStatisticType_Day)
          {
            curMemAT25DataSegment = MemAT25Driver::MemAT25DataSegment_Day;
          }
          else
          if (counterSubStatusSet & CounterStatisticType_Month)
          {
            curMemAT25DataSegment = MemAT25Driver::MemAT25DataSegment_Month;
          }

          startOperation(curMemAT25Operation, curMemAT25DataSegment);
        }
      }
      else
      {
        if (MemAT25Driver::ready())
        {
          if (MemAT25Driver::operationResult == MemAT25Driver::MemAT25COperationResult_OK)
          {
            if (counterSubStatusSet & CounterStatisticType_Hour)
            {
              if (counterStatus == CounterStatus_Load)
              {
                curPeriod.periodNumHour = MemAT25Driver::counterValue.periodNumHour;
                addCounterHour(MemAT25Driver::counterValue.InCntHour, MemAT25Driver::counterValue.OutCntHour, MemAT25Driver::counterValue.NoSensorSecHour);
              }

              counterSubStatusSet ^= CounterStatisticType_Hour;
            }
            else
            if (counterSubStatusSet & CounterStatisticType_Day)
            {
              if (counterStatus == CounterStatus_Load)
              {
                curPeriod.periodNumDay = MemAT25Driver::counterValue.periodNumDay;
                addCounterDay(MemAT25Driver::counterValue.InCntDay, MemAT25Driver::counterValue.OutCntDay, MemAT25Driver::counterValue.NoSensorSecDay);
              }

              counterSubStatusSet ^= CounterStatisticType_Day;
            }
            else
            if (counterSubStatusSet & CounterStatisticType_Month)
            {
              if (counterStatus == CounterStatus_Load)
              {
                curPeriod.periodNumMonth = MemAT25Driver::counterValue.periodNumMonth;
                addCounterMonth(MemAT25Driver::counterValue.InCntMonth, MemAT25Driver::counterValue.OutCntMonth);
              }

              counterSubStatusSet ^= CounterStatisticType_Month;
            }

            if (counterSubStatusSet == CounterStatisticType_None)
            {
              finishOperation();
            }
            else
            {
              scheduleCounterOperation(counterStatus, counterSubStatusSet);
            }
          }
          else
          {
            retryOperation();
          }
        }
      }
    }

    bool ready()
    {
      return counterStatus == CounterStatus_Normal;
    }

    bool scheduleStatisticOperation(TCounterStatisticRecord* _statisticRecord, TCounterStatisticType _statisticType)
    {
      if (!ready())
      {
        return false;
      }

      curStatisticRecord = _statisticRecord;
      curStatisticRecord->InCnt = 0;
      curStatisticRecord->OutCnt = 0;
      curStatisticRecord->NoSensorSec = 0;
      curStatisticRecord->status = CounterStatisticProcessStatus_Scheduled;

      if (curStatisticRecord->periodNumFrom > curStatisticRecord->periodNumTo)
      {
        curStatisticRecord->status = CounterStatisticProcessStatus_Processed;
        return true;
      }

      curStatisticRecord->curPeriodNum = curStatisticRecord->periodNumFrom;

      scheduleCounterOperation(CounterStatus_GetStatistic, _statisticType);

      return true;
    }

    void operationStatistic()
    {
      if (counterOperationStatus == CounterOperationStatus_Scheduling)
      {
        if (curStatisticRecord->curPeriodNum > curStatisticRecord->periodNumTo)
        {
          finishOperation();
          curStatisticRecord->status = CounterStatisticProcessStatus_Processed;
        }
        else
        {
          switch (counterSubStatusSet)
          {
            case CounterStatisticType_Hour:
              if (curStatisticRecord->curPeriodNum == curPeriod.periodNumHour)
              {
                curStatisticRecord->InCnt += curPeriod.InCntHour;
                curStatisticRecord->OutCnt += curPeriod.OutCntHour;
                curStatisticRecord->NoSensorSec += curPeriod.NoSensorSecHour;

                curStatisticRecord->curPeriodNum++;
                scheduleCounterOperation(CounterStatus_GetStatistic, counterSubStatusSet);
              }
              else
              {
                if (enableMemory())
                {
                  MemAT25Driver::counterValue.periodNumHour = curStatisticRecord->curPeriodNum;
                  startOperation(MemAT25Driver::MemAT25Operation_ReadValue, MemAT25Driver::MemAT25DataSegment_Hour);
                }
              }
              break;

            case CounterStatisticType_Day:
              if (curStatisticRecord->curPeriodNum == curPeriod.periodNumDay)
              {
                curStatisticRecord->InCnt += curPeriod.InCntDay;
                curStatisticRecord->OutCnt += curPeriod.OutCntDay;
                curStatisticRecord->NoSensorSec += curPeriod.NoSensorSecDay;

                curStatisticRecord->curPeriodNum++;
                scheduleCounterOperation(CounterStatus_GetStatistic, counterSubStatusSet);
              }
              else
              {
                if (enableMemory())
                {
                  MemAT25Driver::counterValue.periodNumDay = curStatisticRecord->curPeriodNum;
                  startOperation(MemAT25Driver::MemAT25Operation_ReadValue, MemAT25Driver::MemAT25DataSegment_Day);
                }
              }
              break;

            case CounterStatisticType_Month:
              if (curStatisticRecord->curPeriodNum == curPeriod.periodNumMonth)
              {
                curStatisticRecord->InCnt += curPeriod.InCntMonth;
                curStatisticRecord->OutCnt += curPeriod.OutCntMonth;

                curStatisticRecord->curPeriodNum++;
                scheduleCounterOperation(CounterStatus_GetStatistic, counterSubStatusSet);
              }
              else
              {
                if (enableMemory())
                {
                  MemAT25Driver::counterValue.periodNumMonth = curStatisticRecord->curPeriodNum;
                  startOperation(MemAT25Driver::MemAT25Operation_ReadValue, MemAT25Driver::MemAT25DataSegment_Month);
                }
              }
              break;
          }
        }
      }
      else
      {
        if (MemAT25Driver::ready())
        {
          if (MemAT25Driver::operationResult == MemAT25Driver::MemAT25COperationResult_OK)
          {
            switch (counterSubStatusSet)
            {
              case CounterStatisticType_Hour:
                curStatisticRecord->InCnt += MemAT25Driver::counterValue.InCntHour;
                curStatisticRecord->OutCnt += MemAT25Driver::counterValue.OutCntHour;
                curStatisticRecord->NoSensorSec += MemAT25Driver::counterValue.NoSensorSecHour;
                break;

              case CounterStatisticType_Day:
                curStatisticRecord->InCnt += MemAT25Driver::counterValue.InCntDay;
                curStatisticRecord->OutCnt += MemAT25Driver::counterValue.OutCntDay;
                curStatisticRecord->NoSensorSec += MemAT25Driver::counterValue.NoSensorSecDay;
                break;

              case CounterStatisticType_Month:
                curStatisticRecord->InCnt += MemAT25Driver::counterValue.InCntMonth;
                curStatisticRecord->OutCnt += MemAT25Driver::counterValue.OutCntMonth;
                break;
            }

            curStatisticRecord->curPeriodNum++;
            scheduleCounterOperation(CounterStatus_GetStatistic, counterSubStatusSet);
          }
          else
          {
            retryOperation();

            if (counterStatus == CounterStatus_Normal)
            {
              curStatisticRecord->status = CounterStatisticProcessStatus_Error;
            }
          }
        }
      }
    }

    void run()
    {
      switch (counterStatus)
      {
        case CounterStatus_Normal:
          if (updateCounter != CounterStatisticType_None)
          {
            updateCounter = CounterStatisticType_None;

            saveCounter();
          }
          break;

        case CounterStatus_Load:
        case CounterStatus_Save:
          operationLoadSave();
          break;

        case CounterStatus_GetStatistic:
          operationStatistic();
          break;
      }
    }
  }
}

#endif

