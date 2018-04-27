#ifndef __USERINTERFACE_CPP_
#define __USERINTERFACE_CPP_

#include "UserInterface_Ref.h"

namespace UserInterface
{
  TMenuStackRecord menuStack[USER_MENU_STACK_SIZE];
  unsigned char menuStackPos = 0;
  unsigned char activeFunction = USER_FUNCTION_NONE;
  bool activeFunctionChanged = false;
  unsigned char activeParmSpace[USER_MENU_ACTIVE_PARM_SPACE_SIZE];

  bool isEnabled = false;
  bool isTimeOutEnabled = false;
  bool isMenuActive = false;
  bool isPhotoActive = false;
  TMenuAuthLevel menuAuthLevel = MenuAuthLevel_None;
  bool isTransition = false;
  unsigned char transitionKey = 0;
  bool transitionDownOnRefresh = false;
  unsigned char keyIterator = 0;

  GLOBAL::Counter::TCounterStatisticRecord curStatisticRecord;

  void setInactivityTimeTimeout()
  {
    isTimeOutEnabled = true;

    GLOBAL::MultyThreading::setTimer(
      GLOBALTIMERS_USERINTERFACE_TIMEOUT,
      Functions::Common::minof<unsigned char>(Functions::Common::maxof<unsigned char>(5, DeviceAdvancedSetup.inactivityTime), 60) * 1000);
  }

  void setRefreshTimeout()
  {
    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_USERINTERFACE_REFRESHTIME, USER_INTERFACE_REFRESH_TIMEOUT_MS);
  }

  void initTransitionDownOnRefresh()
  {
    transitionDownOnRefresh = true;
    transitionKey = 0;
    isTransition = false;
    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_USERINTERFACE_REFRESHTIME, USER_INTERFACE_MESSAGE_TIMEOUT_MS);
  }

  void updateMenuStack(unsigned char _menuStackPos, unsigned char _menuFunction)
  {
    menuStack[_menuStackPos].menuFunction = _menuFunction;
    menuStack[_menuStackPos].menuReference = menuFunctions[_menuFunction];
    menuStack[_menuStackPos].funcState = menuFunctions[_menuFunction].args.parm;
  }

  void transitionUp(unsigned char _menuFunction)
  {
    transitionKey = 0;

    if (_menuFunction && (menuStackPos < (USER_MENU_STACK_SIZE - 1)))
    {
      menuStackPos++;
      updateMenuStack(menuStackPos, _menuFunction);
      isTransition = true;
    }
  }

  void enterInterface()
  {
    menuStackPos = 0;
    updateMenuStack(0, USER_FUNCTION_SCREENSAVER);
    isTransition = true;
  }

  void getNextTransitionKey()
  {
    if (keyIterator)
    {
      transitionKey = KeyBoardDriver::popBuff();
    }
    else
    {
      transitionKey = 0;
    }
  }

  bool checkDeviceSwitchOff()
  {
    return (DeviceAdvancedSetup.batterySaveMode & DeviceBatterySaveMode_NoScreen) ||
           ((UserInterfaceSetup.screenSaverSetup.screenSaverType == UserMenuScreenSaverType_None) &&
            (UserInterfaceSetup.infoblockMain.infoblockType == UserMenuInfoblockType_None)) ||
           (!MainThread::isDeviceActiveBySchedule());
  }

  void leaveInterface()
  {
    if (checkDeviceSwitchOff())
    {
      if (enabled())
      {
        disable();
      }
    }
    else
    {
      if (enabled())
      {
        enterInterface();
      }
      else
      {
        enable(false);
      }
    }

    isTimeOutEnabled = false;
    isMenuActive = false;
    isPhotoActive = false;
    menuAuthLevel = MenuAuthLevel_None;
  }

  void transitionDown()
  {
    transitionKey = 0;

    if (menuStackPos > 0)
    {
      menuStackPos--;
      isTransition = true;

      if (menuStackPos == 0)
      {
        if (!checkDeviceSwitchOff())
        {
          leaveInterface();
        }
      }
    }
    else
    {
      leaveInterface();
    }
  }

  void enable(bool _withUserKey)
  {
    if (!LCDDriver::enabled())
    {
      LCDDriver::enable();
    }

    enterInterface();
    KeyBoardDriver::clearBuff();
    activeFunction = USER_FUNCTION_NONE;
    activeFunctionChanged = false;
    transitionDownOnRefresh = false;

    if (_withUserKey)
    {
      isMenuActive = true;
      setInactivityTimeTimeout();
    }
    else
    {
      isMenuActive = false;
      isTimeOutEnabled = false;
    }

    menuAuthLevel = MenuAuthLevel_None;
    isPhotoActive = false;

    setRefreshTimeout();

    isEnabled = true;
  }

  void disable()
  {
    isEnabled = false;

    if (LCDDriver::enabled())
    {
      LCDDriver::disable();
    }

    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_USERINTERFACE_REFRESHTIME, 0);
    GLOBAL::MultyThreading::setTimer(GLOBALTIMERS_USERINTERFACE_TIMEOUT, 0);
  }

  bool enabled()
  {
    return isEnabled;
  }

  bool menuActive()
  {
    return isMenuActive;
  }

  bool photoActive()
  {
    return isPhotoActive;
  }

  __monitor void init()
  {
    disable();
  }

  void displayDoneMessage()
  {
    LCDDriver::clearBuffer();
    LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_MESSAGE_DONE), LCDDriver::LCDTextIdentation_Center);
    LCDDriver::refreshDisplay();

    initTransitionDownOnRefresh();
  }

  void displayErrorMessage()
  {
    LCDDriver::clearBuffer();
    LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_MESSAGE_ERROR), LCDDriver::LCDTextIdentation_Center);
    LCDDriver::refreshDisplay();

    initTransitionDownOnRefresh();
  }

  void processMenuOptionChanged()
  {
    transitionDown();
    displayDoneMessage();
  }

  void functionMenu()
  {
    while (transitionKey)
    {
      switch (transitionKey)
      {
        case 1:
          return;

        case 2:
          if (menuStack[menuStackPos].funcState > menuStack[menuStackPos].menuReference.args.parm)
          {
            menuStack[menuStackPos].funcState--;
          }
          else
          {
            menuStack[menuStackPos].funcState = menuStack[menuStackPos].menuReference.args.parm;
            while (menuDescription[menuStack[menuStackPos].funcState + 1].menuFunction != 0)
            {
              menuStack[menuStackPos].funcState++;
            }
          }
          break;

        case 3:
          menuStack[menuStackPos].funcState++;
          if (menuDescription[menuStack[menuStackPos].funcState].menuFunction == 0)
          {
            menuStack[menuStackPos].funcState = menuStack[menuStackPos].menuReference.args.parm;
          }
          break;

        case 4:
          transitionUp(menuDescription[menuStack[menuStackPos].funcState].menuFunction);
          return;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    LCDDriver::str2Buf(0, getString(menuDescription[menuStack[menuStackPos].funcState].textRefLine0), LCDDriver::LCDTextIdentation_Center);
    LCDDriver::str2Buf(1, getString(menuDescription[menuStack[menuStackPos].funcState].textRefLine1), LCDDriver::LCDTextIdentation_Center);

    LCDDriver::refreshDisplay();

    isTransition = false;
  }

  typedef struct
  {
    unsigned char lcdPos;
    unsigned char dtSegment;
    signed char difValue;
  } TSetupDateTimeNavigationStruct;

#define setupDateTimeNavigationStructSize     (12)
  __flash const TSetupDateTimeNavigationStruct setupDateTimeNavigationStruct[setupDateTimeNavigationStructSize] =
  {
    {
      .lcdPos = 2,
      .dtSegment = 0,
      .difValue = 10,
    },
    {
      .lcdPos = 3,
      .dtSegment = 0,
      .difValue = 1,
    },
    {
      .lcdPos = 5,
      .dtSegment = 1,
      .difValue = 10,
    },
    {
      .lcdPos = 6,
      .dtSegment = 1,
      .difValue = 1,
    },
    {
      .lcdPos = 8,
      .dtSegment = 2,
      .difValue = 10,
    },
    {
      .lcdPos = 9,
      .dtSegment = 2,
      .difValue = 1,
    },
    {
      .lcdPos = 16,
      .dtSegment = 3,
      .difValue = 10,
    },
    {
      .lcdPos = 17,
      .dtSegment = 3,
      .difValue = 1,
    },
    {
      .lcdPos = 19,
      .dtSegment = 4,
      .difValue = 10,
    },
    {
      .lcdPos = 20,
      .dtSegment = 4,
      .difValue = 1,
    },
    {
      .lcdPos = 22,
      .dtSegment = 5,
      .difValue = 10,
    },
    {
      .lcdPos = 23,
      .dtSegment = 5,
      .difValue = 1,
    },
  };

  void functionSetupDateTime()
  {
    GLOBAL::RTC::TRTCDateTime* curDateTime = (GLOBAL::RTC::TRTCDateTime*)activeParmSpace;
    unsigned char* curStatus = (unsigned char*)(activeParmSpace + sizeof(GLOBAL::RTC::TRTCDateTime));

    if (activeFunctionChanged)
    {
      *curDateTime = GLOBAL::RTC::RTCDateTime;
      *curStatus = 0;
    }

    while (transitionKey)
    {
      signed char curDif;

      switch (transitionKey)
      {
        case 1:
          if (*curStatus > 0)
          {
            (*curStatus)--;
          }
          else
          {
            return;
          }
          break;

        case 4:
          (*curStatus)++;
          if (*curStatus >= setupDateTimeNavigationStructSize)
          {
            GLOBAL::RTC::setDateTime(curDateTime);

            displayDoneMessage();
            return;
          }
          break;

        case 2:
        case 3:
          curDif = ((transitionKey == 2) ? -1 : 1) * setupDateTimeNavigationStruct[*curStatus].difValue;
          switch (setupDateTimeNavigationStruct[*curStatus].dtSegment)
          {
            case 0:
              curDateTime->year += curDif;
              break;

            case 1:
              curDateTime->month += curDif;
              break;

            case 2:
              curDateTime->day += curDif;
              break;

            case 3:
              curDateTime->hour += curDif;
              break;

            case 4:
              curDateTime->minute += curDif;
              break;

            case 5:
              curDateTime->second += curDif;
              break;
          }

          GLOBAL::RTC::correctDateTime(curDateTime, (curDif >= 0));
          break;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    LCDDriver::num2Buf(0, 3, curDateTime->year, 4, LCD_DISPLAY_SYMBOL_SPACE);
    LCDDriver::displayState.line[0][4] = LCD_DISPLAY_SYMBOL_DASH;
    LCDDriver::num2Buf(0, 6, curDateTime->month, 2, '0');
    LCDDriver::displayState.line[0][7] = LCD_DISPLAY_SYMBOL_DASH;
    LCDDriver::num2Buf(0, 9, curDateTime->day, 2, '0');

    LCDDriver::num2Buf(1, 1, curDateTime->hour, 2, LCD_DISPLAY_SYMBOL_SPACE);
    LCDDriver::displayState.line[1][2] = LCD_DISPLAY_SYMBOL_COLON;
    LCDDriver::num2Buf(1, 4, curDateTime->minute, 2, '0');
    LCDDriver::displayState.line[1][5] = LCD_DISPLAY_SYMBOL_COLON;
    LCDDriver::num2Buf(1, 7, curDateTime->second, 2, '0');

    LCDDriver::displayState.line[1][9] = curDateTime->summerTime ? LCD_DISPLAY_SYMBOL_SUN : LCD_DISPLAY_SYMBOL_SPACE;

    LCDDriver::refreshDisplay(
      LCDDriver::LCDDisplayMode_BlinkCursor,
      setupDateTimeNavigationStruct[*curStatus].lcdPos / LCD_DISPLAY_WIDTH,
      setupDateTimeNavigationStruct[*curStatus].lcdPos % LCD_DISPLAY_WIDTH);

    isTransition = false;
  }

  void functionCancel()
  {
    transitionDown();
    transitionDown();
  }

  void functionIncorrectFunction()
  {
    unsigned char curIncorrectFunctionL1[] = {9, 'I', 'N', 'C', 'O', 'R', 'R', 'E', 'C', 'T'};
    unsigned char curIncorrectFunctionL2[] = {9, 'F', 'U', 'N', 'C', 'T', 'I', 'O', 'N', '!'};

    LCDDriver::clearBuffer();

    LCDDriver::str2Buf(0, curIncorrectFunctionL1, LCDDriver::LCDTextIdentation_Center);
    LCDDriver::str2Buf(1, curIncorrectFunctionL2, LCDDriver::LCDTextIdentation_Center);

    LCDDriver::refreshDisplay();

    initTransitionDownOnRefresh();
  }

  void functionReportVisitorsTotal()
  {
    while (transitionKey)
    {
      if (transitionKey == 1)
      {
          return;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    if (DeviceCounterConfig.detectDirection >= GLOBAL::DeviceProfile::CounterDetectDirectionType_Simulation)
    {
      LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_REPORTS_MESSAGE_INCNT), LCDDriver::LCDTextIdentation_Left, 0);
      LCDDriver::num2Buf(0, 15, GLOBAL::Counter::totalInCnt, 8);
      LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_REPORTS_MESSAGE_OUTCNT), LCDDriver::LCDTextIdentation_Left, 0);
      LCDDriver::num2Buf(1, 15, GLOBAL::Counter::totalOutCnt, 8);
    }
    else
    {
      LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_REPORTS_MESSAGE_TOTALCNT), LCDDriver::LCDTextIdentation_Left, 0);
      LCDDriver::num2Buf(0, 15, GLOBAL::Counter::totalInCnt, 8);
    }

    LCDDriver::refreshDisplay();

    isTransition = false;
  }

  void functionReports()
  {
    unsigned long* curPeriodNum = (unsigned long*)activeParmSpace;
    bool* isReloadScheduled = (bool*)(activeParmSpace + sizeof(unsigned long));
    unsigned char* curStatus = (unsigned char*)(activeParmSpace + sizeof(unsigned long) + sizeof(bool));

    GLOBAL::RTC::TRTCDateTime curDateTime;

    if (activeFunctionChanged)
    {
      switch (menuStack[menuStackPos].funcState)
      {
        case 2:
        case 3:
        case 6:
          *curPeriodNum = GLOBAL::Counter::getPeriodNumDay(&GLOBAL::RTC::RTCDateTime);
          break;

        case 4:
          *curPeriodNum = GLOBAL::Counter::getPeriodNumMonth(&GLOBAL::RTC::RTCDateTime);
          break;

        default:
          *curPeriodNum = GLOBAL::Counter::getPeriodNumHour(&GLOBAL::RTC::RTCDateTime);
          break;
      }

      curStatisticRecord.status = GLOBAL::Counter::CounterStatisticProcessStatus_None;
      *isReloadScheduled = true;

      *curStatus = 0;
    }

    while (transitionKey)
    {
      signed char curDif;

      switch (transitionKey)
      {
        case 1:
          if (*curStatus > 0)
          {
            (*curStatus)--;
          }
          else
          {
            return;
          }
          break;

        case 4:
          //TODO: Add advanced data search
          break;

        case 2:
        case 3:
          curDif = (transitionKey == 2) ? -1 : 1;

          switch (menuStack[menuStackPos].funcState)
          {
            case 3:
              *curPeriodNum += curDif * 7;
              break;

            default:
              *curPeriodNum += curDif;
              break;
          }

          *isReloadScheduled = true;
          break;
      }

      getNextTransitionKey();
    }

    if (curStatisticRecord.status == GLOBAL::Counter::CounterStatisticProcessStatus_Scheduled)
    {
      return;
    }

    GLOBAL::Counter::TCounterStatisticType curCounterStatisticType;

    switch (menuStack[menuStackPos].funcState)
    {
      case 2:
      case 3:
      case 6:
        GLOBAL::Counter::getRTCDateTimeDay(&curDateTime, *curPeriodNum);
        curCounterStatisticType = GLOBAL::Counter::CounterStatisticType_Day;
        break;

      case 4:
        GLOBAL::Counter::getRTCDateTimeMonth(&curDateTime, *curPeriodNum);
        curCounterStatisticType = GLOBAL::Counter::CounterStatisticType_Month;
        break;

      default:
        GLOBAL::Counter::getRTCDateTimeHour(&curDateTime, *curPeriodNum);
        curCounterStatisticType = GLOBAL::Counter::CounterStatisticType_Hour;
        break;
    }

    switch (menuStack[menuStackPos].funcState)
    {
      case 3:
        curStatisticRecord.periodNumFrom = *curPeriodNum - curDateTime.weekDay;
        curStatisticRecord.periodNumTo = curStatisticRecord.periodNumFrom + 6;

        GLOBAL::Counter::getRTCDateTimeDay(&curDateTime, curStatisticRecord.periodNumFrom);
        break;

      default:
        curStatisticRecord.periodNumFrom = *curPeriodNum;
        curStatisticRecord.periodNumTo = *curPeriodNum;
        break;
    }

    LCDDriver::clearBuffer();

    switch (menuStack[menuStackPos].funcState)
    {
      case 1:
      case 2:
      case 3:
      case 5:
      case 6:
        LCDDriver::num2Buf(0, 3, curDateTime.year, 4, LCD_DISPLAY_SYMBOL_SPACE);
        LCDDriver::displayState.line[0][4] = LCD_DISPLAY_SYMBOL_DASH;
        LCDDriver::num2Buf(0, 6, curDateTime.month, 2, '0');
        LCDDriver::displayState.line[0][7] = LCD_DISPLAY_SYMBOL_DASH;
        LCDDriver::num2Buf(0, 9, curDateTime.day, 2, '0');
        break;
    }

    switch (menuStack[menuStackPos].funcState)
    {
      case 1:
      case 5:
        LCDDriver::num2Buf(0, 12, curDateTime.hour, 2, LCD_DISPLAY_SYMBOL_SPACE);
        LCDDriver::displayState.line[0][13] = LCD_DISPLAY_SYMBOL_COLON;
        LCDDriver::num2Buf(0, 15, 0, 2, '0');
        break;

      case 3:
        LCDDriver::displayState.line[0][11] = '+';
        LCDDriver::displayState.line[0][13] = '7';
        break;

      case 4:
        LCDDriver::num2Buf(0, 3, curDateTime.year, 4, LCD_DISPLAY_SYMBOL_SPACE);
        LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_MONTH_NAME_JANUARY + curDateTime.month - 1), LCDDriver::LCDTextIdentation_Left, 5);
        break;
    }

    if ((*isReloadScheduled) || (curStatisticRecord.status == GLOBAL::Counter::CounterStatisticProcessStatus_None))
    {
      if (GLOBAL::Counter::scheduleStatisticOperation(&curStatisticRecord, curCounterStatisticType))
      {
        *isReloadScheduled = false;
      }

      LCDDriver::displayState.line[1][15] = LCD_DISPLAY_SYMBOL_SUN;
    }
    else
    {
      if (curStatisticRecord.status == GLOBAL::Counter::CounterStatisticProcessStatus_Error)
      {
        LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_MESSAGE_ERROR), LCDDriver::LCDTextIdentation_Right, 15);
      }
      else
      {
        if ((menuStack[menuStackPos].funcState) >= 5)
        {
          LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_REPORTS_MESSAGE_TOTALCNT), LCDDriver::LCDTextIdentation_Left, 0);
          LCDDriver::num2Buf(1, 15, curStatisticRecord.NoSensorSec / 60, 8);
        }
        else
        if (DeviceCounterConfig.detectDirection >= GLOBAL::DeviceProfile::CounterDetectDirectionType_Simulation)
        {
          LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_REPORTS_MESSAGE_INCNT_SHORT), LCDDriver::LCDTextIdentation_Left, 0);
          LCDDriver::num2Buf(1, 6, curStatisticRecord.InCnt, 7);

          LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_REPORTS_MESSAGE_OUTCNT_SHORT), LCDDriver::LCDTextIdentation_Left, 8);
          LCDDriver::num2Buf(1, 15, curStatisticRecord.OutCnt, 7);
        }
        else
        {
          LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_REPORTS_MESSAGE_TOTALCNT), LCDDriver::LCDTextIdentation_Left, 0);
          LCDDriver::num2Buf(1, 15, curStatisticRecord.InCnt, 8);
        }
      }

      isTransition = false;
    }

    LCDDriver::refreshDisplay();
  }

  void functionSafeBattRemove()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = 0;
    }

    while (transitionKey)
    {
      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    switch (menuStack[menuStackPos].funcState)
    {
      case 0:
        if (GLOBAL::Counter::ready())
        {
          DeviceManager::saveDeviceStatus();
          GLOBAL::Counter::setUpdateCounter();
          menuStack[menuStackPos].funcState = 1;
        }
        break;

      case 1:
        if (GLOBAL::Counter::ready() && (!GLOBAL::Counter::isUpdateCounter()))
        {
          if (MemAT25Driver::blockMemOperations())
          {
            menuStack[menuStackPos].funcState = 2;
          }
        }
        break;

      case 2:
        if (MemAT25Driver::blocked())
        {
          setInactivityTimeTimeout();

          LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_MESSAGE_DONE), LCDDriver::LCDTextIdentation_Center);
          LCDDriver::displayState.line[1][6] = '0';
          LCDDriver::displayState.line[1][7] = '0';
          LCDDriver::displayState.line[1][8] = LCD_DISPLAY_SYMBOL_COLON;
          LCDDriver::num2Buf(1, 10, GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_MEMAT25_ERRORTIMER) / 1000, 2, '0');
          LCDDriver::refreshDisplay();
        }
        else
        {
          transitionDown();
        }
        return;
    }

    LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_MESSAGE_SAVING), LCDDriver::LCDTextIdentation_Center);
    LCDDriver::displayState.line[1][15] = LCD_DISPLAY_SYMBOL_SUN;
    LCDDriver::refreshDisplay();
  }

  void functionSetupSummerTimeMenu()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = USER_MENU_SETUP_SUMMERTIME + GLOBAL::RTC::RTCConfig.summerTimeRule;
    }

    functionMenu();
  }

  void functionSetupSummerTime()
  {
    GLOBAL::RTC::setSummerTimeRule((GLOBAL::RTC::TSummerTimeRule)menuStack[menuStackPos].funcState);
    processMenuOptionChanged();
  }

  void functionSetupDetectorMenu()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = USER_MENU_SETUP_COUNTER_DETECTOR + DeviceCounterConfig.detectDirection;
    }

    functionMenu();
  }

  void functionSetupDetector()
  {
    DeviceCounterConfig.detectDirection = (TCounterDetectDirectionType)menuStack[menuStackPos].funcState;
    DeviceManager::saveDeviceCounterConfig();
    processMenuOptionChanged();
  }

  void functionSetupInventCntMenu()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = USER_MENU_SETUP_COUNTER_INVERTCOUNT + DeviceCounterConfig.invertCounting;
    }

    functionMenu();
  }

  void functionSetupInventCnt()
  {
    DeviceCounterConfig.invertCounting = (bool)menuStack[menuStackPos].funcState;
    DeviceManager::saveDeviceCounterConfig();
    processMenuOptionChanged();
  }

  void functionSetupSaveModeMenu()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = USER_MENU_SETUP_ENERGYSAVING_SAVEMODE + DeviceAdvancedSetup.batterySaveMode;
    }

    functionMenu();
  }

  void functionSetupSaveMode()
  {
    DeviceAdvancedSetup.batterySaveMode = (TDeviceBatterySaveMode)menuStack[menuStackPos].funcState;
    DeviceManager::saveDeviceAdvancedSetup();
    processMenuOptionChanged();
  }

  void functionSetupWorkTodayMenu()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = USER_MENU_SETUP_ENERGYSAVING_WORKTODAY + ((DeviceAdvancedSetup.workWeekMask & 0x80) ? 1 : 0);
    }

    functionMenu();
  }

  void functionSetupWorkToday()
  {
    if (menuStack[menuStackPos].funcState)
    {
      DeviceAdvancedSetup.workWeekMask |= 0x80;
    }
    else
    {
      DeviceAdvancedSetup.workWeekMask &= 0x7F;
    }

    DeviceManager::saveDeviceAdvancedSetup();
    processMenuOptionChanged();
  }

  void functionSetupWorkDayMenu()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = USER_MENU_SETUP_ENERGYSAVING_WORKDAY + DeviceAdvancedSetup.workDayStruct;
    }

    functionMenu();
  }

  void setWorkDaySetup(TDeviceAdvancedSetup* _curSetup)
  {
    DeviceAdvancedSetup.workDayStruct = _curSetup->workDayStruct;
    DeviceAdvancedSetup.shiftStart1 = _curSetup->shiftStart1;
    DeviceAdvancedSetup.shiftEnd1 = _curSetup->shiftEnd1;
    DeviceAdvancedSetup.shiftStart2 = _curSetup->shiftStart2;
    DeviceAdvancedSetup.shiftEnd2 = _curSetup->shiftEnd2;

    DeviceManager::saveDeviceAdvancedSetup();
    processMenuOptionChanged();
  }

  __flash const unsigned short setupWorkDayDiffValues[4] = {600, 60, 10, 1};
  __flash const unsigned char setupWorkDayDisplayPos[8] = {2, 3, 5, 6, 10, 11, 13, 14};

  void functionSetupWorkDay()
  {
    TDeviceAdvancedSetup* curAdvSetup = (TDeviceAdvancedSetup*)activeParmSpace;
    unsigned char* curStatus = (unsigned char*)(activeParmSpace + sizeof(TDeviceAdvancedSetup));

    if (activeFunctionChanged)
    {
      *curAdvSetup = DeviceAdvancedSetup;
      curAdvSetup->workDayStruct = (TWorkDayShiftStructure)menuStack[menuStackPos].funcState;
      *curStatus = 0;

      if (curAdvSetup->workDayStruct == WorkDayShiftStructure_WholeDay)
      {
        setWorkDaySetup(curAdvSetup);
        return;
      }
    }

    while (transitionKey)
    {
      signed short curDif;
      unsigned short* curValue;

      switch (transitionKey)
      {
        case 1:
          if (*curStatus > 0)
          {
            (*curStatus)--;
          }
          else
          {
            return;
          }
          break;

        case 4:
          (*curStatus)++;
          if (((curAdvSetup->workDayStruct == WorkDayShiftStructure_Shift1) && (*curStatus >= 8)) ||
              (*curStatus >= 16))
          {
            setWorkDaySetup(curAdvSetup);
            return;
          }
          break;

        case 2:
        case 3:
          curDif = ((transitionKey == 2) ? -1 : 1) * setupWorkDayDiffValues[*curStatus % 4];

          switch (*curStatus / 4)
          {
            case 0:
              curValue = &(curAdvSetup->shiftStart1);
              break;

            case 1:
              curValue = &(curAdvSetup->shiftEnd1);
              break;

            case 2:
              curValue = &(curAdvSetup->shiftStart2);
              break;

            case 3:
              curValue = &(curAdvSetup->shiftEnd2);
              break;
          }

          *curValue += curDif;

          if (*curValue > 1440)
          {
            *curValue = (curDif > 0) ? 1440 : 0;
          }
          break;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    unsigned short* curShiftStart;
    unsigned short* curShiftEnd;

    if (*curStatus < 8)
    {
      LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_TEXT_SHIFT1), LCDDriver::LCDTextIdentation_Center);

      curShiftStart = &(curAdvSetup->shiftStart1);
      curShiftEnd = &(curAdvSetup->shiftEnd1);
    }
    else
    {
      LCDDriver::str2Buf(
        0,
        getString((curAdvSetup->workDayStruct == WorkDayShiftStructure_Shift2) ?
          USER_TEXT_CONST_TEXT_SHIFT2 :
          USER_TEXT_CONST_TEXT_LUNCH),
        LCDDriver::LCDTextIdentation_Center);

      curShiftStart = &(curAdvSetup->shiftStart2);
      curShiftEnd = &(curAdvSetup->shiftEnd2);
    }

    LCDDriver::num2Buf(1, 3, *curShiftStart / 60, 2, LCD_DISPLAY_SYMBOL_SPACE);
      LCDDriver::displayState.line[1][4] = LCD_DISPLAY_SYMBOL_COLON;
      LCDDriver::num2Buf(1, 6, *curShiftStart % 60, 2, '0');
      LCDDriver::displayState.line[1][8] = LCD_DISPLAY_SYMBOL_DASH;
      LCDDriver::num2Buf(1, 11, *curShiftEnd / 60, 2, LCD_DISPLAY_SYMBOL_SPACE);
      LCDDriver::displayState.line[1][12] = LCD_DISPLAY_SYMBOL_COLON;
      LCDDriver::num2Buf(1, 14, *curShiftEnd % 60, 2, '0');

    LCDDriver::refreshDisplay(
      LCDDriver::LCDDisplayMode_BlinkCursor,
      1,
      setupWorkDayDisplayPos[*curStatus % 8]);

    isTransition = false;
  }

  void functionSetupDetectionTime()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = DeviceCounterConfig.bodyDetectionLevel;
    }

    while (transitionKey)
    {
      switch (transitionKey)
      {
        case 1:
          return;

        case 4:
          DeviceCounterConfig.bodyDetectionLevel = menuStack[menuStackPos].funcState;
          DeviceManager::saveDeviceCounterConfig();
          displayDoneMessage();
          return;

        case 2:
            if (menuStack[menuStackPos].funcState > 1)
            {
              menuStack[menuStackPos].funcState--;
            }
          break;

        case 3:
          if (menuStack[menuStackPos].funcState < 255)
          {
            menuStack[menuStackPos].funcState++;
          }
          break;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_SETUP_COUNTER_DETECTIONTIME), LCDDriver::LCDTextIdentation_Center);
    LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_TEXT_MILLISECONDS_SHORT), LCDDriver::LCDTextIdentation_Right, 15);

    unsigned short calcBodyDetLevel = (unsigned short)(menuStack[menuStackPos].funcState) * timerDiscreteness;
    if (GLOBAL::DeviceProfile::DeviceCounterConfig.detectDirection < GLOBAL::DeviceProfile::CounterDetectDirectionType_StrongDetection)
    {
      calcBodyDetLevel += COUNTER_BODY_DETECTION_ADD_MS;
    }

    LCDDriver::num2Buf(1, 12, calcBodyDetLevel, 4);

    LCDDriver::refreshDisplay();

    isTransition = false;
  }

  void functionSetupInactivityTime()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = DeviceAdvancedSetup.inactivityTime;
      if (menuStack[menuStackPos].funcState < 5)
      {
        menuStack[menuStackPos].funcState = 5;
      }
    }

    while (transitionKey)
    {
      switch (transitionKey)
      {
        case 1:
          return;

        case 4:
          DeviceAdvancedSetup.inactivityTime = menuStack[menuStackPos].funcState;
          DeviceManager::saveDeviceAdvancedSetup();
          displayDoneMessage();
          return;

        case 2:
            if (menuStack[menuStackPos].funcState > 5)
            {
              menuStack[menuStackPos].funcState--;
            }
          break;

        case 3:
          if (menuStack[menuStackPos].funcState < 60)
          {
            menuStack[menuStackPos].funcState++;
          }
          break;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_TEXT_TIMEOUT), LCDDriver::LCDTextIdentation_Center);
    LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_TEXT_SECONDS_SHORT), LCDDriver::LCDTextIdentation_Right, 15);

    LCDDriver::num2Buf(1, 11, menuStack[menuStackPos].funcState, 4);

    LCDDriver::refreshDisplay();

    isTransition = false;
  }

  void functionSetupWorkWeek()
  {
    unsigned char* curWorkDayPos = (unsigned char*)activeParmSpace;
    unsigned char* curWorkDayMask = (unsigned char*)(activeParmSpace + sizeof(unsigned char));
    unsigned char* curWorkWeekMask = (unsigned char*)(activeParmSpace + sizeof(unsigned char) + sizeof(unsigned char));

    if (activeFunctionChanged)
    {
      *curWorkDayPos = 0;
      *curWorkDayMask = 0x01;
      *curWorkWeekMask = DeviceAdvancedSetup.workWeekMask;
    }

    while (transitionKey)
    {
      switch (transitionKey)
      {
        case 1:
          if (*curWorkDayPos > 0)
          {
            (*curWorkDayPos)--;
            (*curWorkDayMask) >>= 1;
          }
          else
          {
            return;
          }
          break;

        case 4:
          (*curWorkDayPos)++;
          (*curWorkDayMask) <<= 1;
          if (*curWorkDayPos >= 7)
          {
            DeviceAdvancedSetup.workWeekMask = *curWorkWeekMask;

            DeviceManager::saveDeviceAdvancedSetup();
            displayDoneMessage();
            return;
          }
          break;

        case 2:
        case 3:
          *curWorkWeekMask ^= *curWorkDayMask;
          break;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKWEEK_MASK), LCDDriver::LCDTextIdentation_Center);

    unsigned char curMask = 0x01;
    unsigned char curPos = 1;
    for (unsigned char i = 0; i < 7; i++)
    {
      LCDDriver::displayState.line[1][curPos] = ((*curWorkWeekMask) & curMask) ? '^' : LCD_DISPLAY_SYMBOL_SPACE;
      curMask <<= 1;
      curPos += 2;
    }

    LCDDriver::refreshDisplay(
      LCDDriver::LCDDisplayMode_BlinkCursor,
      1,
      (*curWorkDayPos * 2) + 1);

    isTransition = false;
  }

  void functionSetCheckPassword(bool _authScreen)
  {
    unsigned char* curPwd = (unsigned char*)activeParmSpace;
    unsigned char* curPwdCopy = (unsigned char*)(activeParmSpace + DEVICE_PASSWORD_LENGTH);
    unsigned char* curStatus = (unsigned char*)(activeParmSpace + (2 * DEVICE_PASSWORD_LENGTH));
    unsigned char* curPwdPos = (unsigned char*)(activeParmSpace + (2 * DEVICE_PASSWORD_LENGTH) + sizeof(unsigned char));

    if (activeFunctionChanged)
    {
      for (unsigned char i = 0; i < DEVICE_PASSWORD_LENGTH; i++)
      {
        curPwd[i] = 0;
        curPwdCopy[i] = 0;
      }

      *curPwdPos = 0;

      if (_authScreen)
      {
        *curStatus = 3;

        if (DeviceManager::checkPasswordMaster(curPwd))
        {
          menuAuthLevel = MenuAuthLevel_Master;
          return;
        }

        while (transitionKey)
        {
          getNextTransitionKey();
        }
      }
      else
      {
        *curStatus = 0;
      }
    }

    while (transitionKey)
    {
      unsigned char curChar;
      unsigned char curDif;

      switch (transitionKey)
      {
        case 1:
          if (*curPwdPos > 0)
          {
            curPwd[*curPwdPos] = 0;
            (*curPwdPos)--;
          }
          else
          {
            return;
          }
          break;

        case 4:
          if ((*curPwdPos >= (DEVICE_PASSWORD_LENGTH - 1)) ||
              (curPwd[*curPwdPos] == 0))
          {
            switch (*curStatus)
            {
              case 0:
                switch (menuStack[menuStackPos].funcState)
                {
                  case 0:
                    if (!DeviceManager::checkPasswordMaster(curPwd))
                    {
                      displayErrorMessage();
                      return;
                    }
                    break;

                  case 1:
                    if (!DeviceManager::checkPasswordReports(curPwd))
                    {
                      displayErrorMessage();
                      return;
                    }
                    break;
                }

                (*curStatus)++;
                break;

              case 1:
                (*curStatus)++;
                break;

              case 2:
                for (unsigned char i = 0; i < DEVICE_PASSWORD_LENGTH; i++)
                {
                  if (curPwd[i] != curPwdCopy[i])
                  {
                    displayErrorMessage();
                    return;
                  }
                }

                switch (menuStack[menuStackPos].funcState)
                {
                  case 0:
                    DeviceManager::setPasswordMaster(curPwd);
                    break;

                  case 1:
                    DeviceManager::setPasswordReports(curPwd);
                    break;
                }

                displayDoneMessage();
                return;

              case 3:
                while (transitionKey)
                {
                  getNextTransitionKey();
                }

                if (DeviceManager::checkPasswordMaster(curPwd))
                {
                  menuAuthLevel = MenuAuthLevel_Master;
                  return;
                }

                if (DeviceManager::checkPasswordReports(curPwd))
                {
                  menuAuthLevel = MenuAuthLevel_Reports;
                  return;
                }

                DeviceManager::incPwdFails();

                displayErrorMessage();
                return;
            }

            for (unsigned char i = 0; i < DEVICE_PASSWORD_LENGTH; i++)
            {
              curPwdCopy[i] = curPwd[i];
              curPwd[i] = 0;
            }

            *curPwdPos = 0;
          }
          else
          {
            (*curPwdPos)++;
          }
          break;

        case 2:
        case 3:
          curChar = curPwd[*curPwdPos];
          curDif = (transitionKey == 2) ? 9 : 1;
          if (curChar >= 0x30)
          {
            curChar = curChar - 0x30;
          }
          else
          {
            curChar = 0;
            curDif = 0;
          }

          curChar = (curChar + curDif) % 10;
          curPwd[*curPwdPos] = curChar + 0x30;
          break;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    switch (*curStatus)
    {
      case 0:
        LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_SETUP_PASSWORD_CURRENT), LCDDriver::LCDTextIdentation_Center);
        break;

      case 1:
        LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_SETUP_PASSWORD_NEW), LCDDriver::LCDTextIdentation_Center);
        break;

      case 2:
        LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_SETUP_PASSWORD_REPEAT), LCDDriver::LCDTextIdentation_Center);
        break;

      case 3:
        LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_MESSAGE_TYPE_PASSWORD), LCDDriver::LCDTextIdentation_Center);
        break;
    }

    unsigned char curPos = (LCD_DISPLAY_WIDTH - DEVICE_PASSWORD_LENGTH) / 2;
    for (unsigned char i = 0; i < (*curPwdPos); i++)
    {
      LCDDriver::displayState.line[1][curPos] = '*';
      curPos++;
    }

    LCDDriver::displayState.line[1][curPos] = curPwd[*curPwdPos] ? curPwd[*curPwdPos] : LCD_DISPLAY_SYMBOL_SPACE;

    LCDDriver::refreshDisplay(
      LCDDriver::LCDDisplayMode_BlinkCursor,
      1,
      curPos);

    isTransition = false;
  }

  void functionSetupPassword()
  {
    functionSetCheckPassword(false);
  }

  void functionAuthenticationScreen()
  {
    functionSetCheckPassword(true);
  }

  void functionReset()
  {
    switch(menuStack[menuStackPos].funcState)
    {
      case 1:
        DeviceManager::resetCounters();
        break;

      case 2:
        DeviceManager::resetToFactoryDefaults();
        break;

      case 3:
        DeviceManager::resetData();
        break;

      case 4:
        DeviceManager::resetFull();
        break;
    }

    processMenuOptionChanged();
  }

  void functionBatteryVoltage()
  {
    LCDDriver::clearBuffer();

    LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_INFO_BATTERY_VOLTAGE), LCDDriver::LCDTextIdentation_Center);

    unsigned short curBatteryVoltage = GLOBAL::ADC::getBatteryCurrentVoltage();

    LCDDriver::num2Buf(1, 15, curBatteryVoltage % 100, 2, '0');
    LCDDriver::displayState.line[1][13] = '.';
    LCDDriver::num2Buf(1, 12, curBatteryVoltage / 100, 2);

    LCDDriver::refreshDisplay();

    isTransition = false;
  }

  void displaySensorQuality(unsigned char _lineNum, unsigned char _qualityPct)
  {
    LCDDriver::displayState.line[_lineNum][0] = '[';
    LCDDriver::displayState.line[_lineNum][15] = ']';
    unsigned char curQulityBarNum = (((unsigned short)_qualityPct) * 14) / 100;
    if ((_qualityPct > 95) || (curQulityBarNum > 14))
    {
      curQulityBarNum = 14;
    }

    for (unsigned char i = 0; i < 14; i++)
    {
      LCDDriver::displayState.line[_lineNum][1 + i] = (i < curQulityBarNum) ? LCD_DISPLAY_SYMBOL_BLACKBLOCK : LCD_DISPLAY_SYMBOL_DASH;
    }

    if (curQulityBarNum <= 11)
    {
      LCDDriver::displayState.line[_lineNum][14] = '%';
      LCDDriver::num2Buf(_lineNum, 13, _qualityPct, 2, LCD_DISPLAY_SYMBOL_SPACE);
    }
  }

  void functionSensorQuality()
  {
    isPhotoActive = true;

    while (transitionKey)
    {
      switch (transitionKey)
      {
        case 1:
          isPhotoActive = false;
          return;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();
    displaySensorQuality(0, PhotoSensor::getCounterQualityPct1());
    if (GLOBAL::DeviceProfile::DeviceCounterConfig.detectDirection >= GLOBAL::DeviceProfile::CounterDetectDirectionType_StrongDetection)
    {
      displaySensorQuality(1, PhotoSensor::getCounterQualityPct2());
    }

    LCDDriver::refreshDisplay();

    setInactivityTimeTimeout();
  }

  void functionSetupBacklightMenu()
  {
    if (activeFunctionChanged)
    {
      menuStack[menuStackPos].funcState = USER_MENU_SETUP_ENERGYSAVING_BACKLIGHT + DeviceAdvancedSetup.backlight;
    }

    functionMenu();
  }

  void functionSetupBacklight()
  {
    DeviceAdvancedSetup.backlight = (bool)menuStack[menuStackPos].funcState;
    DeviceManager::saveDeviceAdvancedSetup();
    processMenuOptionChanged();
  }

  void functionSerialNumber()
  {
    LCDDriver::clearBuffer();

    LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_INFO_SERIALNUM), LCDDriver::LCDTextIdentation_Center);

    for (unsigned char i = 0; i < DEVICE_SERIAL_NUMBER_STR_LNG; i++)
    {
      LCDDriver::displayState.line[1][i] = GLOBAL::DeviceProfile::DeviceSerialNumber.serialNumStr[i];
    }

    LCDDriver::refreshDisplay();

    isTransition = false;
  }

  void functionResetNum()
  {
    LCDDriver::clearBuffer();

    unsigned short curStrNum = 0;
    unsigned long curValue = 0;
    switch (menuStack[menuStackPos].funcState)
    {
      case 0:
        curStrNum = USER_TEXT_CONST_INFO_RESETNUM_RESTARTS;
        curValue = DeviceManager::getTotalRestarts();
        break;

      case 1:
        curStrNum = USER_TEXT_CONST_INFO_RESETNUM_DATARESET;
        curValue = DeviceManager::getTotalDataReset();
        break;

      case 2:
        curStrNum = USER_TEXT_CONST_INFO_RESETNUM_FACTORYRESET;
        curValue = DeviceManager::getTotalFactoryReset();
        break;

      case 3:
        curStrNum = USER_TEXT_CONST_INFO_RESETNUM_PASSWORDFAILS_L1;
        curValue = DeviceManager::getTotalPwdFails();
        break;
    }

    LCDDriver::str2Buf(0, getString(curStrNum), LCDDriver::LCDTextIdentation_Center);
    LCDDriver::num2Buf(1, 15, curValue, 10);

    LCDDriver::refreshDisplay();
  }

  void run()
  {
    if (!isEnabled)
    {
      return;
    }

    if (!LCDDriver::ready())
    {
      return;
    }

    if (isTimeOutEnabled && (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_USERINTERFACE_TIMEOUT)))
    {
      leaveInterface();

      if (enabled())
      {
        isTransition = true;
      }
      else
      {
        return;
      }
    }

    if (!GLOBAL::MultyThreading::getTimer(GLOBALTIMERS_USERINTERFACE_REFRESHTIME))
    {
      if (!isMenuActive)
      {
        leaveInterface();
      }

      if (enabled())
      {
        if (transitionDownOnRefresh)
        {
          transitionDownOnRefresh = false;
          KeyBoardDriver::clearBuff();

          transitionDown();

          if (!enabled())
          {
            return;
          }
        }

        isTransition = true;
        setRefreshTimeout();
      }
      else
      {
        return;
      }
    }

    if (transitionDownOnRefresh)
    {
      return;
    }

    transitionKey = KeyBoardDriver::popBuff();
    if (transitionKey)
    {
      if ((!isMenuActive) &&
          GLOBAL::DeviceProfile::DeviceAdvancedSetup.backlight &&
          (transitionKey != 1))
      {
        transitionKey = 0;
      }

      isTransition = true;
      isMenuActive = true;

      setInactivityTimeTimeout();
    }

    if (isTransition)
    {
      keyIterator = USER_INTERFACE_KEY_ITERATOR_MAX;

      if (isMenuActive && (menuAuthLevel == MenuAuthLevel_None))
      {
        activeFunctionChanged = (activeFunction != USER_FUNCTION_AUTHENTICATION_SCREEN);
        activeFunction = USER_FUNCTION_AUTHENTICATION_SCREEN;
        functionAuthenticationScreen();
      }

      if ((!isMenuActive) || (menuAuthLevel != MenuAuthLevel_None))
      {
        activeFunctionChanged = (activeFunction != menuStack[menuStackPos].menuFunction);
        activeFunction = menuStack[menuStackPos].menuFunction;

        if (menuStack[menuStackPos].menuReference.entryPoint)
        {
          (*(void(*)(void))(menuStack[menuStackPos].menuReference.entryPoint))();
        }
        else
        {
          functionIncorrectFunction();
        }
      }

      if (transitionKey == 1)
      {
        transitionDown();
      }
    }

    transitionKey = 0;
  }
}

#endif
