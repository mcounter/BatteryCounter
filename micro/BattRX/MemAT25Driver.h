#ifndef __MEMAT25DRIVER_H_
#define __MEMAT25DRIVER_H_

#include "GlobalSpace.h"
#include "GlobalCounter.h"

namespace MemAT25Driver
{
  typedef enum
  {
    MemAT25Operation_ReadValue = 0,
    MemAT25Operation_WriteValue = 1,
  } TMemAT25Operation;

  typedef enum
  {
    MemAT25DataSegment_Hour = 0,
    MemAT25DataSegment_Day = 1,
    MemAT25DataSegment_Month = 2,
  } TMemAT25DataSegment;

  typedef enum
  {
    MemAT25COperationResult_None = 0,
    MemAT25COperationResult_OK = 1,
    MemAT25COperationResult_Error = 2,
  } TMemAT25COperationResult;

  extern GLOBAL::Counter::TCounterPeriodData counterValue;
  extern TMemAT25COperationResult operationResult;

  void init();
  void enable();
  void disable();
  bool enabled();
  bool ready();
  void run();

  bool startMemOperation(TMemAT25Operation _operation, TMemAT25DataSegment _dataSegment);

  bool blocked();
  bool blockMemOperations();
}

#endif


