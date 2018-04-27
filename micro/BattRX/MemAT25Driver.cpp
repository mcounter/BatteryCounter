#ifndef __MEMAT25DRIVER_CPP_
#define __MEMAT25DRIVER_CPP_

#include <string.h>
#include "MemAT25Driver.h"
#include "CommProtocol_SPI_Master.h"
#include "MultyThreading.h"
#include "CommonFunctions.h"
#include "CRC8.h"

#define MEMAT25_VALPERSEGMENT_HOUR    (3)
#define MEMAT25_VALPERSEGMENT_DAY     (2)
#define MEMAT25_VALPERSEGMENT_MONTH   (2)

#define MEMAT25_ERRORIDLETIME   (3000)
#define MEMAT25_BLOCKTIME       (30000)

#define MEMAT25CMD_WREN         (0x06)
#define MEMAT25CMD_WRDI         (0x04)
#define MEMAT25CMD_RDSR         (0x05)
#define MEMAT25CMD_WRSR         (0x01)
#define MEMAT25CMD_READ         (0x03)
#define MEMAT25CMD_WRITE        (0x02)

#define MEMAT25STATUS_NORMAL    (0x02)
#define MEMAT25STATUS_FLG_BUSY  (0x01)

using namespace Functions::Common;

namespace MemAT25Driver
{
  typedef enum
  {
    MemAT25ResourceStatus_Disabled = 0x00,
    MemAT25ResourceStatus_Ready = 0x01,
    MemAT25ResourceStatus_Scheduled = 0x02,
    MemAT25ResourceStatus_InProcess = 0x03,
    MemAT25ResourceStatus_Blocked = 0x04,
  } TMemAT25ResourceStatus;

  typedef enum
  {
    MemAT25ProtocolStatus_WriteStatusRegWREN = 0,
    MemAT25ProtocolStatus_WriteStatusReg = 1,
    MemAT25ProtocolStatus_WriteDataWREN = 2,
    MemAT25ProtocolStatus_WriteData = 3,
    MemAT25ProtocolStatus_ReadData = 4,
    MemAT25ProtocolStatus_ParseData = 5,
    MemAT25ProtocolStatus_ReadDataValidate = 6,
    MemAT25ProtocolStatus_ValidateData = 7,
  } TMemAT25ProtocolStatus;

  typedef enum
  {
    MemAT25WaitingStatus_None = 0,
    MemAT25WaitingStatus_Schedule = 1,
    MemAT25WaitingStatus_Wait = 2,
  } TMemAT25WaitingStatus;

  typedef struct
  {
    unsigned char data[12];

    unsigned long periodNum:24;
    unsigned long crc8:8;
  } TMem25DataSegmentStd;

  typedef struct
  {
    unsigned long InCnt1:13;
    unsigned long OutCnt1:13;
    unsigned long NoSensorMin1:6;

    unsigned long InCnt2:13;
    unsigned long OutCnt2:13;
    unsigned long NoSensorMin2:6;

    unsigned long InCnt3:13;
    unsigned long OutCnt3:13;
    unsigned long NoSensorMin3:6;

  } TMem25DataSegmentHour;

  typedef struct
  {
    unsigned short InCnt1;
    unsigned short OutCnt1;
    unsigned short NoSensorMin1;

    unsigned short InCnt2;
    unsigned short OutCnt2;
    unsigned short NoSensorMin2;
  } TMem25DataSegmentDay;

  typedef struct
  {
    unsigned char InCnt1H;
    unsigned short InCnt1L;
    unsigned char OutCnt1H;
    unsigned short OutCnt1L;

    unsigned char InCnt2H;
    unsigned short InCnt2L;
    unsigned char OutCnt2H;
    unsigned short OutCnt2L;
  } TMem25DataSegmentMonth;

  TMemAT25Operation operation;
  TMemAT25DataSegment dataSegment;

  TMem25DataSegmentStd operationBuffer;
  GLOBAL::Counter::TCounterPeriodData counterValue;
  TMemAT25COperationResult operationResult;

  TMemAT25ResourceStatus resourceStatus = MemAT25ResourceStatus_Disabled;
  unsigned char protocolStatus;
  TMemAT25WaitingStatus waitingStatus;

  __monitor void enable()
  {
    CommProtocol_SPI_Master::enable();

    resourceStatus = MemAT25ResourceStatus_Ready;
  }

  __monitor void disable()
  {
    MEM_SS_DIR = 1;
    MEM_SS_PORT = 1;

    CommProtocol_SPI_Master::disable();

    resourceStatus = MemAT25ResourceStatus_Disabled;
  }

  bool enabled()
  {
    return resourceStatus != MemAT25ResourceStatus_Disabled;
  }

  bool ready()
  {
    return resourceStatus == MemAT25ResourceStatus_Ready;
  }

  __monitor void init()
  {
    disable();
  }

  void schedule()
  {
    resourceStatus = MemAT25ResourceStatus_Scheduled;
  }

  void finish()
  {
    resourceStatus = MemAT25ResourceStatus_Ready;
  }

  void inProcess()
  {
    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_MEMAT25_ERRORTIMER, MEMAT25_ERRORIDLETIME);
    resourceStatus = MemAT25ResourceStatus_InProcess;
  }

  bool startMemOperation(TMemAT25Operation _operation, TMemAT25DataSegment _dataSegment)
  {
    if (!ready())
    {
      return false;
    }

    operation = _operation;
    dataSegment = _dataSegment;
    operationResult = MemAT25COperationResult_None;
    waitingStatus = MemAT25WaitingStatus_None;

    schedule();

    return true;
  }

  void scheduleCmd(unsigned char _cmd, unsigned char _parmLng)
  {
    CommProtocol_SPI_Master::bufferSPI.length = _parmLng + 1;
    CommProtocol_SPI_Master::bufferSPI.status = CommProtocol_SPI_Master::SPIBufferStatus_Ready;
    CommProtocol_SPI_Master::bufferSPI.result = CommProtocol_SPI_Master::SPIResultCodeType_OK;
    CommProtocol_SPI_Master::bufferSPI.buffer[0] = _cmd;

    memset(CommProtocol_SPI_Master::bufferSPI.buffer + 1, 0xFF, _parmLng);
  }

  void scheduleCmdWREN()
  {
    scheduleCmd(MEMAT25CMD_WREN, 0);
  }

  void scheduleCmdRDSR()
  {
    waitingStatus = MemAT25WaitingStatus_Wait;
    scheduleCmd(MEMAT25CMD_RDSR, 1);
  }

  void scheduleCmdWRSR()
  {
    waitingStatus = MemAT25WaitingStatus_Wait;
    scheduleCmd(MEMAT25CMD_WRSR, 1);
    CommProtocol_SPI_Master::bufferSPI.buffer[1] = MEMAT25STATUS_NORMAL;
  }

  void setMemAddr()
  {
    unsigned short memAddr;

    switch (dataSegment)
    {
      case MemAT25DataSegment_Hour:
        memAddr = ((counterValue.periodNumHour / MEMAT25_VALPERSEGMENT_HOUR) % (EXT_MEMORY_SIZE_HOUR_SEGMENT / EXT_MEMORY_SEGMENTSIZE)) * EXT_MEMORY_SEGMENTSIZE;
        break;

      case MemAT25DataSegment_Day:
        memAddr = (((counterValue.periodNumDay / MEMAT25_VALPERSEGMENT_DAY) % (EXT_MEMORY_SIZE_DAY_SEGMENT / EXT_MEMORY_SEGMENTSIZE)) * EXT_MEMORY_SEGMENTSIZE) + EXT_MEMORY_SIZE_HOUR_SEGMENT;
        break;

      case MemAT25DataSegment_Month:
        memAddr = (((counterValue.periodNumMonth / MEMAT25_VALPERSEGMENT_MONTH) % (EXT_MEMORY_SIZE_MONTH_SEGMENT / EXT_MEMORY_SEGMENTSIZE)) * EXT_MEMORY_SEGMENTSIZE) + EXT_MEMORY_SIZE_HOUR_SEGMENT + EXT_MEMORY_SIZE_DAY_SEGMENT;
        break;
    }

    CommProtocol_SPI_Master::bufferSPI.buffer[1] = (unsigned char)(memAddr >> 8);
    CommProtocol_SPI_Master::bufferSPI.buffer[2] = (unsigned char)memAddr;
  }

  void scheduleCmdRead()
  {
    scheduleCmd(MEMAT25CMD_READ, 2 + EXT_MEMORY_SEGMENTSIZE);
    setMemAddr();
  }

  void maskOperationBuffer()
  {
    unsigned char* operationBufferPtr = (unsigned char*)(&operationBuffer);

    for (unsigned char i = 0; i < sizeof(TMem25DataSegmentStd); i++)
    {
      operationBufferPtr[i] ^= GLOBAL::DeviceProfile::MemorySecureTemplate[i];
    }
  }

  void scheduleCmdWriteHour()
  {
    TMem25DataSegmentHour* curDataSegment = (TMem25DataSegmentHour*)(operationBuffer.data);

    unsigned char subPeriodNum = counterValue.periodNumHour % MEMAT25_VALPERSEGMENT_HOUR;
    operationBuffer.periodNum = (counterValue.periodNumHour / MEMAT25_VALPERSEGMENT_HOUR) * MEMAT25_VALPERSEGMENT_HOUR;

    unsigned char noSensorMinTmp = (unsigned char)minof<unsigned short>(60, counterValue.NoSensorSecHour / 60);
    switch(subPeriodNum)
    {
      case 0:
        curDataSegment->InCnt1 = counterValue.InCntHour;
        curDataSegment->OutCnt1 = counterValue.OutCntHour;
        curDataSegment->NoSensorMin1 = noSensorMinTmp;
        break;

      case 1:
        curDataSegment->InCnt2 = counterValue.InCntHour;
        curDataSegment->OutCnt2 = counterValue.OutCntHour;
        curDataSegment->NoSensorMin2 = noSensorMinTmp;
        break;

      case 2:
        curDataSegment->InCnt3 = counterValue.InCntHour;
        curDataSegment->OutCnt3 = counterValue.OutCntHour;
        curDataSegment->NoSensorMin3 = noSensorMinTmp;
        break;
    }
  }

  void scheduleCmdWriteDay()
  {
    TMem25DataSegmentDay* curDataSegment = (TMem25DataSegmentDay*)(operationBuffer.data);

    unsigned char subPeriodNum = counterValue.periodNumDay % MEMAT25_VALPERSEGMENT_DAY;
    operationBuffer.periodNum = (counterValue.periodNumDay / MEMAT25_VALPERSEGMENT_DAY) * MEMAT25_VALPERSEGMENT_DAY;

    unsigned char noSensorMinTmp = (unsigned char)minof<unsigned short>(1440, counterValue.NoSensorSecDay / 60);
    switch(subPeriodNum)
    {
      case 0:
        curDataSegment->InCnt1 = counterValue.InCntDay;
        curDataSegment->OutCnt1 = counterValue.OutCntDay;
        curDataSegment->NoSensorMin1 = noSensorMinTmp;
        break;

      case 1:
        curDataSegment->InCnt2 = counterValue.InCntDay;
        curDataSegment->OutCnt2 = counterValue.OutCntDay;
        curDataSegment->NoSensorMin2 = noSensorMinTmp;
        break;
    }
  }

  void scheduleCmdWriteMonth()
  {
    TMem25DataSegmentMonth* curDataSegment = (TMem25DataSegmentMonth*)(operationBuffer.data);

    unsigned char subPeriodNum = counterValue.periodNumMonth % MEMAT25_VALPERSEGMENT_MONTH;
    operationBuffer.periodNum = (counterValue.periodNumMonth / MEMAT25_VALPERSEGMENT_MONTH) * MEMAT25_VALPERSEGMENT_MONTH;

    switch(subPeriodNum)
    {
      case 0:
        curDataSegment->InCnt1H = (unsigned char)(counterValue.InCntMonth >> 16);
        curDataSegment->InCnt1L = (unsigned short)counterValue.InCntMonth;
        curDataSegment->OutCnt1H = (unsigned char)(counterValue.OutCntMonth >> 16);
        curDataSegment->OutCnt1L = (unsigned short)counterValue.OutCntMonth;
        break;

      case 1:
        curDataSegment->InCnt2H = (unsigned char)(counterValue.InCntMonth >> 16);
        curDataSegment->InCnt2L = (unsigned short)counterValue.InCntMonth;
        curDataSegment->OutCnt2H = (unsigned char)(counterValue.OutCntMonth >> 16);
        curDataSegment->OutCnt2L = (unsigned short)counterValue.OutCntMonth;
        break;
    }
  }

  void scheduleCmdWrite()
  {
    scheduleCmd(MEMAT25CMD_WRITE, 2 + EXT_MEMORY_SEGMENTSIZE);
    setMemAddr();

    switch (dataSegment)
    {
      case MemAT25DataSegment_Hour:
        scheduleCmdWriteHour();
        break;

      case MemAT25DataSegment_Day:
        scheduleCmdWriteDay();
        break;

      case MemAT25DataSegment_Month:
        scheduleCmdWriteMonth();
        break;
    }

    operationBuffer.crc8 = CRC8::calcCRC8((unsigned char*)(&operationBuffer), sizeof(TMem25DataSegmentStd) - sizeof(CRC8::TCRC8));
    maskOperationBuffer();

    memcpy(CommProtocol_SPI_Master::bufferSPI.buffer + 3, &operationBuffer, sizeof(TMem25DataSegmentStd));
  }

  void populateValueBufferHour()
  {
    TMem25DataSegmentHour* curDataSegment = (TMem25DataSegmentHour*)(operationBuffer.data);

    unsigned char subPeriodNum = counterValue.periodNumHour % MEMAT25_VALPERSEGMENT_HOUR;

    unsigned short noSensorMinTmp = 0;
    switch(subPeriodNum)
    {
      case 0:
        counterValue.InCntHour = curDataSegment->InCnt1;
        counterValue.OutCntHour = curDataSegment->OutCnt1;
        noSensorMinTmp = curDataSegment->NoSensorMin1;
        break;

      case 1:
        counterValue.InCntHour = curDataSegment->InCnt2;
        counterValue.OutCntHour = curDataSegment->OutCnt2;
        noSensorMinTmp = curDataSegment->NoSensorMin2;
        break;

      case 2:
        counterValue.InCntHour = curDataSegment->InCnt3;
        counterValue.OutCntHour = curDataSegment->OutCnt3;
        noSensorMinTmp = curDataSegment->NoSensorMin3;
        break;
    }

    counterValue.NoSensorSecHour = noSensorMinTmp * 60;
  }

  void populateValueBufferDay()
  {
    TMem25DataSegmentDay* curDataSegment = (TMem25DataSegmentDay*)(operationBuffer.data);

    unsigned char subPeriodNum = counterValue.periodNumDay % MEMAT25_VALPERSEGMENT_DAY;

    unsigned long noSensorMinTmp = 0;
    switch(subPeriodNum)
    {
      case 0:
        counterValue.InCntDay = curDataSegment->InCnt1;
        counterValue.OutCntDay = curDataSegment->OutCnt1;
        noSensorMinTmp = curDataSegment->NoSensorMin1;
        break;

      case 1:
        counterValue.InCntDay = curDataSegment->InCnt2;
        counterValue.OutCntDay = curDataSegment->OutCnt2;
        noSensorMinTmp = curDataSegment->NoSensorMin2;
        break;
    }

    counterValue.NoSensorSecDay = noSensorMinTmp * 60;
  }

  void populateValueBufferMonth()
  {
    TMem25DataSegmentMonth* curDataSegment = (TMem25DataSegmentMonth*)(operationBuffer.data);

    unsigned char subPeriodNum = counterValue.periodNumMonth % MEMAT25_VALPERSEGMENT_MONTH;

    switch(subPeriodNum)
    {
      case 0:
        counterValue.InCntMonth = (((unsigned long)(curDataSegment->InCnt1H)) << 16) + curDataSegment->InCnt1L;
        counterValue.OutCntMonth = (((unsigned long)(curDataSegment->OutCnt1H)) << 16) + curDataSegment->OutCnt1L;
        break;

      case 1:
        counterValue.InCntMonth = (((unsigned long)(curDataSegment->InCnt2H)) << 16) + curDataSegment->InCnt2L;
        counterValue.OutCntMonth = (((unsigned long)(curDataSegment->OutCnt2H)) << 16) + curDataSegment->OutCnt2L;
        break;
    }
  }

  void populateValueBuffer()
  {
    switch (dataSegment)
    {
      case MemAT25DataSegment_Hour:
        populateValueBufferHour();
        break;

      case MemAT25DataSegment_Day:
        populateValueBufferDay();
        break;

      case MemAT25DataSegment_Month:
        populateValueBufferMonth();
        break;
    }
  }

  void processMemOperation()
  {
    if (resourceStatus == MemAT25ResourceStatus_Scheduled)
    {
      switch (CommProtocol_SPI_Master::bufferSPI.status)
      {
        case CommProtocol_SPI_Master::SPIBufferStatus_None:
        case CommProtocol_SPI_Master::SPIBufferStatus_Processed:
          protocolStatus = MemAT25ProtocolStatus_ReadData;
          scheduleCmdRDSR();
          inProcess();
          break;
      }
    }

    bool validationResult;

    if (resourceStatus == MemAT25ResourceStatus_InProcess)
    {
      if (CommProtocol_SPI_Master::bufferSPI.status == CommProtocol_SPI_Master::SPIBufferStatus_Processed)
      {
        if (CommProtocol_SPI_Master::bufferSPI.result == CommProtocol_SPI_Master::SPIResultCodeType_OK)
        {
          if ((waitingStatus == MemAT25WaitingStatus_Schedule) ||
              ((waitingStatus == MemAT25WaitingStatus_Wait) &&
               ((CommProtocol_SPI_Master::bufferSPI.buffer[1] & MEMAT25STATUS_FLG_BUSY) != 0x00)))
          {
            scheduleCmdRDSR();
            return;
          }

          waitingStatus = MemAT25WaitingStatus_None;

          switch (protocolStatus)
          {
            case MemAT25ProtocolStatus_WriteStatusRegWREN:
            case MemAT25ProtocolStatus_WriteDataWREN:
              scheduleCmdWREN();
              protocolStatus++;
              break;

            case MemAT25ProtocolStatus_WriteStatusReg:
              scheduleCmdWRSR();
              protocolStatus = MemAT25ProtocolStatus_WriteDataWREN;
              waitingStatus = MemAT25WaitingStatus_Schedule;
              break;

            case MemAT25ProtocolStatus_WriteData:
              scheduleCmdWrite();
              protocolStatus = MemAT25ProtocolStatus_ReadDataValidate;
              waitingStatus = MemAT25WaitingStatus_Schedule;
              break;

            case MemAT25ProtocolStatus_ReadData:
            case MemAT25ProtocolStatus_ReadDataValidate:
              scheduleCmdRead();
              protocolStatus++;
              break;

            case MemAT25ProtocolStatus_ParseData:
              memcpy(&operationBuffer, CommProtocol_SPI_Master::bufferSPI.buffer + 3, sizeof(TMem25DataSegmentStd));
              maskOperationBuffer();

              validationResult = true;
              if (operationBuffer.crc8 != CRC8::calcCRC8((unsigned char*)(&operationBuffer), sizeof(TMem25DataSegmentStd) - sizeof(CRC8::TCRC8)))
              {
                validationResult = false;
              }
              else
              {
                switch (dataSegment)
                {
                  case MemAT25DataSegment_Hour:
                    if ((operationBuffer.periodNum / MEMAT25_VALPERSEGMENT_HOUR) != (counterValue.periodNumHour / MEMAT25_VALPERSEGMENT_HOUR))
                    {
                      validationResult = false;
                    }
                    break;

                  case MemAT25DataSegment_Day:
                    if ((operationBuffer.periodNum / MEMAT25_VALPERSEGMENT_DAY) != (counterValue.periodNumDay / MEMAT25_VALPERSEGMENT_DAY))
                    {
                      validationResult = false;
                    }
                    break;

                  case MemAT25DataSegment_Month:
                    if ((operationBuffer.periodNum / MEMAT25_VALPERSEGMENT_MONTH) != (counterValue.periodNumMonth / MEMAT25_VALPERSEGMENT_MONTH))
                    {
                      validationResult = false;
                    }
                    break;
                }
              }

              if (!validationResult)
              {
                memset(&operationBuffer, 0x00, sizeof(TMem25DataSegmentStd));
              }

              if (operation == MemAT25Operation_ReadValue)
              {
                populateValueBuffer();
                operationResult = MemAT25COperationResult_OK;
                finish();
              }
              else
              {
                protocolStatus = MemAT25ProtocolStatus_WriteStatusRegWREN;
              }
              break;

            case MemAT25ProtocolStatus_ValidateData:
              operationResult = (memcmp(&operationBuffer, CommProtocol_SPI_Master::bufferSPI.buffer + 3, sizeof(TMem25DataSegmentStd)) == 0) ? MemAT25COperationResult_OK : MemAT25COperationResult_Error;
              finish();
              break;
          }
        }
        else
        {
          operationResult = MemAT25COperationResult_Error;
          finish();
        }
      }
    }
  }

  bool blocked()
  {
    return resourceStatus == MemAT25ResourceStatus_Blocked;
  }

  bool blockMemOperations()
  {
    if (enabled() && (!ready()))
    {
      return false;
    }

    disable();

    resourceStatus = MemAT25ResourceStatus_Blocked;

    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_MEMAT25_ERRORTIMER, MEMAT25_BLOCKTIME);

    return true;

  }

  void run()
  {
    switch (resourceStatus)
    {
      case MemAT25ResourceStatus_Disabled:
      case MemAT25ResourceStatus_Ready:
        return;

      case MemAT25ResourceStatus_InProcess:
        if (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_MEMAT25_ERRORTIMER))
        {
          operationResult = MemAT25COperationResult_Error;
          finish();
        }
        else
        {
          processMemOperation();
        }
        break;

      case MemAT25ResourceStatus_Scheduled:
        processMemOperation();
        break;

      case MemAT25ResourceStatus_Blocked:
        if (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_MEMAT25_ERRORTIMER))
        {
          disable();
        }
        break;
    }
  }
}

#endif

