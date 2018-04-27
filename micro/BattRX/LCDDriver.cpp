#ifndef __LCDDRIVER_CPP_
#define __LCDDRIVER_CPP_

#include "LCDDriver.h"
#include "CommProtocol_TWI_Master.h"
#include "MultyThreading.h"
#include "GlobalADC.h"

#define LCDDRIVER_SWITCHON_WAITING_TIME       (100)
#define LCDDRIVER_FOLLOWERSET_WAITING_TIME    (400)
#define LCDDRIVER_SLA_W                       (0x7C)
#define LCDDRIVER_CONTROL_CO_POS              (7)
#define LCDDRIVER_CONTROL_RS_POS              (6)

namespace LCDDriver
{
  typedef enum
  {
    LCDDriverStatus_Disabled = 0x00,
    LCDDriverStatus_Initializing = 0x01,
    LCDDriverStatus_Ready = 0x02,
    LCDDriverStatus_Reset = 0x03,
    LCDDriverStatus_Refresh = 0x04,
    LCDDriverStatus_SetDisplayMode = 0x05,
    LCDDriverStatus_SetEntryState = 0x06,
  } TLCDDriverStatus;

  typedef enum
  {
    LCDDriverInitSubStatus_SwitchOn = 0,
    LCDDriverInitSubStatus_WaitSwitchOn = 1,
    LCDDriverInitSubStatus_FunctionSetNormMode = 2,
    LCDDriverInitSubStatus_InitCGRAM = 3,
    LCDDriverInitSubStatus_FunctionSetInitExtMode = 4,
    LCDDriverInitSubStatus_FunctionSetExtMode = 5,
    LCDDriverInitSubStatus_IntOSCFreqSet = 6,
    LCDDriverInitSubStatus_ContrastSet = 7,
    LCDDriverInitSubStatus_PowerIconConSet = 8,
    LCDDriverInitSubStatus_FollowerSet = 9,
    LCDDriverInitSubStatus_WaitFollower = 10,
    LCDDriverInitSubStatus_DisplayOn = 11,
  } TLCDDriverInitSubStatus;

  typedef enum
  {
    LCDDriverResetSubStatus_ClearDisplay = 0,
    LCDDriverResetSubStatus_ReturnHome = 1,
    LCDDriverResetSubStatus_SetDisplayMode = 2,
    LCDDriverResetSubStatus_SetEntryState = 3,
  } TLCDDriverResetSubStatus;

  typedef enum
  {
    LCDDriverRefreshSubStatus_SetDDRAMLine0 = 0,
    LCDDriverRefreshSubStatus_SetDDRAMLine1 = 1,
    LCDDriverRefreshSubStatus_SetDisplayMode = 2,
    LCDDriverRefreshSubStatus_SetCursorPos = 3,
  } TLCDDriverRefreshSubStatus;

  typedef enum
  {
    LCDMemoryPosition_CGRAM = 0x40,
    LCDMemoryPosition_Line0 = 0x80,
    LCDMemoryPosition_Line1 = 0xC0,
  } TLCDMemoryPosition;

  __flash unsigned char LCDDRIVER_EXT_SYMBOLS[] = {0x0E, 0x11, 0x10, 0x1C, 0x10, 0x11, 0x0E, 0x00,
                                                   0x00, 0x00, 0x0E, 0x11, 0x1C, 0x11, 0x0E, 0x00,
                                                   0x0A, 0x00, 0x0E, 0x04, 0x04, 0x04, 0x0E, 0x00,
                                                   0x00, 0x0A, 0x00, 0x0C, 0x04, 0x04, 0x0E, 0x00,
                                                   0x04, 0x0E, 0x11, 0x11, 0x13, 0x17, 0x1F, 0x1F};

  TLCDDriverStatus lcdStatus = LCDDriverStatus_Disabled;
  unsigned char lcdSubStatus;

  TLCDDisplayState displayState;

  __monitor void enable()
  {
    CommProtocol_TWI_Master::enable();

    lcdStatus = LCDDriverStatus_Initializing;
    lcdSubStatus = LCDDriverInitSubStatus_SwitchOn;
  }

  __monitor void disable()
  {
    LCD_VDD_DIR = 1;
    LCD_VDD_PORT = 0;

    CommProtocol_TWI_Master::disable();

    lcdStatus = LCDDriverStatus_Disabled;
  }

  bool enabled()
  {
    return lcdStatus != LCDDriverStatus_Disabled;
  }

  bool ready()
  {
    return lcdStatus == LCDDriverStatus_Ready;
  }

  void clearBuffer()
  {
    for (unsigned char i = 0; i < LCD_DISPLAY_WIDTH; i++)
    {
      for (unsigned char j = 0; j < LCD_DISPLAY_HEIGHT; j++)
      {
        displayState.line[j][i] = LCD_DISPLAY_SYMBOL_SPACE;
      }
    }
  }

  void str2Buf(
    unsigned char _lineNum,
    unsigned char __generic* _str,
    TLCDTextIdentation _identation,
    unsigned char _pos)
  {
    if (!_str)
    {
      return;
    }

    unsigned char curStrLng = Functions::Common::minof<unsigned char>(_str[0], LCD_DISPLAY_WIDTH);
    if (curStrLng <= 0)
    {
      return;
    }

    unsigned char curPos = Functions::Common::minof<unsigned char>(_pos, LCD_DISPLAY_WIDTH - 1);
    unsigned char* curDestPos = displayState.line[_lineNum];

    switch (_identation)
    {
      case LCDTextIdentation_Center:
        curDestPos += ((LCD_DISPLAY_WIDTH - curStrLng) / 2);
        break;

      case LCDTextIdentation_Left:
        curStrLng = Functions::Common::minof<unsigned char>(curStrLng, LCD_DISPLAY_WIDTH - curPos);
        curDestPos += curPos;
        break;

      case LCDTextIdentation_Right:
        curStrLng = Functions::Common::minof<unsigned char>(curStrLng, curPos + 1);
        curDestPos += (curPos + 1 - curStrLng);
        break;
    }

    memcpy_G(curDestPos, _str + 1, curStrLng);
  }

  void num2Buf(
    unsigned char _lineNum,
    unsigned char _linePos,
    unsigned long _value,
    unsigned char _maxSize,
    unsigned char _fillChar)
  {
    unsigned char* curDest = displayState.line[_lineNum];

    unsigned char linePos = Functions::Common::minof<unsigned char>(_linePos, LCD_DISPLAY_WIDTH - 1);
    unsigned char maxSize = Functions::Common::minof<unsigned char>(_maxSize, linePos + 1);
    unsigned long curValue = _value;

    for (unsigned char i = 0; i < maxSize; i++)
    {
      unsigned char curDigit = curValue % 10;
      curValue /= 10;

      if ((i == 0) || curDigit || curValue)
      {
        curDest[linePos - i] = '0' + curDigit;
      }
      else if (_fillChar)
      {
        curDest[linePos - i] = _fillChar;
      }
      else
      {
        break;
      }
    }
  }

  __monitor void init()
  {
    disable();

    clearBuffer();
  }

  bool sendSingleCommand(unsigned char _command)
  {
    if (!CommProtocol_TWI_Master::ready())
    {
      return false;
    }

    CommProtocol_TWI_Master::bufferTWI.length = 3;
    CommProtocol_TWI_Master::bufferTWI.buffer[0] = LCDDRIVER_SLA_W;
    CommProtocol_TWI_Master::bufferTWI.buffer[1] = (0<<LCDDRIVER_CONTROL_CO_POS) | (0<<LCDDRIVER_CONTROL_RS_POS);
    CommProtocol_TWI_Master::bufferTWI.buffer[2] = _command;
    CommProtocol_TWI_Master::bufferTWI.status = CommProtocol_TWI_Master::TWIBufferStatus_Ready;

    return true;
  }

  bool initCGRAM()
  {
    if (!CommProtocol_TWI_Master::ready())
    {
      return false;
    }

    CommProtocol_TWI_Master::bufferTWI.length = 4 + sizeof(LCDDRIVER_EXT_SYMBOLS);
    CommProtocol_TWI_Master::bufferTWI.buffer[0] = LCDDRIVER_SLA_W;
    CommProtocol_TWI_Master::bufferTWI.buffer[1] = (1<<LCDDRIVER_CONTROL_CO_POS) | (0<<LCDDRIVER_CONTROL_RS_POS);
    CommProtocol_TWI_Master::bufferTWI.buffer[2] = LCDMemoryPosition_CGRAM;
    CommProtocol_TWI_Master::bufferTWI.buffer[3] = (0<<LCDDRIVER_CONTROL_CO_POS) | (1<<LCDDRIVER_CONTROL_RS_POS);

    for (unsigned char i = 0; i < sizeof(LCDDRIVER_EXT_SYMBOLS); i++)
    {
      CommProtocol_TWI_Master::bufferTWI.buffer[i + 4] = LCDDRIVER_EXT_SYMBOLS[i];
    }

    CommProtocol_TWI_Master::bufferTWI.status = CommProtocol_TWI_Master::TWIBufferStatus_Ready;

    return true;
  }

  bool setDDRAM(unsigned char _lineNum)
  {
    if (!CommProtocol_TWI_Master::ready())
    {
      return false;
    }

    CommProtocol_TWI_Master::bufferTWI.length = 4 + LCD_DISPLAY_WIDTH;
    CommProtocol_TWI_Master::bufferTWI.buffer[0] = LCDDRIVER_SLA_W;
    CommProtocol_TWI_Master::bufferTWI.buffer[1] = (1<<LCDDRIVER_CONTROL_CO_POS) | (0 << LCDDRIVER_CONTROL_RS_POS);

    switch (_lineNum)
    {
      case 0:
        CommProtocol_TWI_Master::bufferTWI.buffer[2] = LCDMemoryPosition_Line0;
        break;

      case 1:
        CommProtocol_TWI_Master::bufferTWI.buffer[2] = LCDMemoryPosition_Line1;
        break;
    }

    CommProtocol_TWI_Master::bufferTWI.buffer[3] = (0<<LCDDRIVER_CONTROL_CO_POS) | (1 << LCDDRIVER_CONTROL_RS_POS);

    for (unsigned char i = 0; i < LCD_DISPLAY_WIDTH; i++)
    {
      CommProtocol_TWI_Master::bufferTWI.buffer[i + 4] = displayState.line[_lineNum][i];
    }

    CommProtocol_TWI_Master::bufferTWI.status = CommProtocol_TWI_Master::TWIBufferStatus_Ready;

    return true;
  }

  bool setCursorPos()
  {
    if (displayState.displayMode != LCDDisplayMode_NoCursor)
    {
      switch(displayState.cursorPosY)
      {
        case 0:
          return sendSingleCommand(LCDMemoryPosition_Line0 + (displayState.cursorPosX % 0x28));

        case 1:
          return sendSingleCommand(LCDMemoryPosition_Line1 + (displayState.cursorPosX % 0x28));
          break;
      }
    }

    return true;
  }

  void processInitialize()
  {
    bool isProcessed = true;

    switch (lcdSubStatus)
    {
      case LCDDriverInitSubStatus_SwitchOn:
        LCD_VDD_DIR = 1;
        LCD_VDD_PORT = 1;

        GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_LCDDRIVER_WAITINGTIMER, LCDDRIVER_SWITCHON_WAITING_TIME);
        break;

      case LCDDriverInitSubStatus_WaitSwitchOn:
      case LCDDriverInitSubStatus_WaitFollower:
        isProcessed = GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_LCDDRIVER_WAITINGTIMER) == 0;
        break;

      case LCDDriverInitSubStatus_FunctionSetNormMode:
        isProcessed = sendSingleCommand(0x38);
        break;

      case LCDDriverInitSubStatus_InitCGRAM:
        isProcessed = initCGRAM();
        break;

      case LCDDriverInitSubStatus_FunctionSetInitExtMode:
      case LCDDriverInitSubStatus_FunctionSetExtMode:
        isProcessed = sendSingleCommand(0x39);
        break;

      case LCDDriverInitSubStatus_IntOSCFreqSet:
        isProcessed = sendSingleCommand(0x10); // Bias = 1/5, Freq = min
        break;

      case LCDDriverInitSubStatus_ContrastSet:
        isProcessed = sendSingleCommand(0x70); //Contrast = middle
        break;

      case LCDDriverInitSubStatus_PowerIconConSet:
        isProcessed = sendSingleCommand(0x56); //Icon = off, Buster = on, Contrast = middle
        break;

      case LCDDriverInitSubStatus_FollowerSet:
        isProcessed = sendSingleCommand(0x6D); //Follower = on, Rab = 2.5
        if (isProcessed)
        {
          GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_LCDDRIVER_WAITINGTIMER, LCDDRIVER_SWITCHON_WAITING_TIME);
        }
        break;

      case LCDDriverInitSubStatus_DisplayOn:
        displayState.displayMode = LCDDisplayMode_NoCursor;
        displayState.entryState = LCDDisplayEntryState_ShiftCursorRight;
        lcdStatus = LCDDriverStatus_Reset;
        lcdSubStatus = LCDDriverResetSubStatus_ClearDisplay;
        return;
    }

    if (isProcessed)
    {
      lcdSubStatus++;
    }
  }

  void processReset()
  {
    bool isProcessed = true;

    switch (lcdSubStatus)
    {
      case LCDDriverResetSubStatus_ClearDisplay:
        isProcessed = sendSingleCommand(0x01);
        break;

      case LCDDriverResetSubStatus_ReturnHome:
        isProcessed = sendSingleCommand(0x02);
        break;

      case LCDDriverResetSubStatus_SetDisplayMode:
        isProcessed = sendSingleCommand(displayState.displayMode);
        break;

      case LCDDriverResetSubStatus_SetEntryState:
        isProcessed = sendSingleCommand(displayState.entryState);

        if (isProcessed)
        {
          lcdStatus = LCDDriverStatus_Ready;
          return;
        }
        break;
    }

    if (isProcessed)
    {
      lcdSubStatus++;
    }
  }

  void processRefresh()
  {
    bool isProcessed = true;

    switch (lcdSubStatus)
    {
      case LCDDriverRefreshSubStatus_SetDDRAMLine0:
        isProcessed = setDDRAM(0);
        break;

      case LCDDriverRefreshSubStatus_SetDDRAMLine1:
        isProcessed = setDDRAM(1);
        break;

      case LCDDriverRefreshSubStatus_SetDisplayMode:
        isProcessed = sendSingleCommand(displayState.displayMode);
        break;

      case LCDDriverRefreshSubStatus_SetCursorPos:
        isProcessed = setCursorPos();

        if (isProcessed)
        {
          lcdStatus = LCDDriverStatus_Ready;
          return;
        }
        break;
    }

    if (isProcessed)
    {
      lcdSubStatus++;
    }
  }

  void processSetDisplayMode()
  {
    if (sendSingleCommand(displayState.displayMode))
    {
      lcdStatus = LCDDriverStatus_Ready;
    }
  }

  void processSetEntryState()
  {
    if (sendSingleCommand(displayState.entryState))
    {
      lcdStatus = LCDDriverStatus_Ready;
    }
  }

  bool resetDisplay(TLCDDisplayMode _displayMode, TLCDDisplayEntryState _entryState)
  {
    if (!ready())
    {
      return false;
    }

    displayState.displayMode = _displayMode;
    displayState.entryState = _entryState;
    lcdStatus = LCDDriverStatus_Reset;
    lcdSubStatus = LCDDriverResetSubStatus_ClearDisplay;

    return true;
  }

  bool refreshDisplay(
    TLCDDisplayMode _displayMode,
    unsigned char _cursorPosY,
    unsigned char _cursorPosX,
    bool _displayLowBatterySymbol,
    unsigned char _lowPatterySymbolPosY,
    unsigned char _lowPatterySymbolPosX)
  {
    if (!ready())
    {
      return false;
    }

    if (_displayLowBatterySymbol && GLOBAL::ADC::isLowBatteryVoltage())
    {
      displayState.line[_lowPatterySymbolPosY][_lowPatterySymbolPosX] = LCD_DISPLAY_SYMBOL_LOW_BATTERY;
    }

    displayState.displayMode = _displayMode;
    displayState.cursorPosY = _cursorPosY;
    displayState.cursorPosX = _cursorPosX;

    lcdStatus = LCDDriverStatus_Refresh;
    lcdSubStatus = LCDDriverRefreshSubStatus_SetDDRAMLine0;

    return true;
  }

  bool setDisplayMode(TLCDDisplayMode _displayMode)
  {
    if (!ready())
    {
      return false;
    }

    displayState.displayMode = _displayMode;
    lcdStatus = LCDDriverStatus_SetDisplayMode;

    return true;
  }

  bool setEntryState(TLCDDisplayEntryState _entryState)
  {
    if (!ready())
    {
      return false;
    }

    displayState.entryState = _entryState;
    lcdStatus = LCDDriverStatus_SetEntryState;

    return true;
  }

  void run()
  {
    switch (lcdStatus)
    {
      case LCDDriverStatus_Disabled:
      case LCDDriverStatus_Ready:
        return;

      case LCDDriverStatus_Initializing:
        processInitialize();
        break;

      case LCDDriverStatus_Reset:
        processReset();
        break;

      case LCDDriverStatus_Refresh:
        processRefresh();
        break;

      case LCDDriverStatus_SetDisplayMode:
        processSetDisplayMode();
        break;

      case LCDDriverStatus_SetEntryState:
        processSetEntryState();
        break;
    }
  }
}

#endif
