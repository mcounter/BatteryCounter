#ifndef __USERINTERFACE_WIDGET_CPP_
#define __USERINTERFACE_WIDGET_CPP_

#include "UserInterface_Ref.h"

namespace UserInterface
{
  typedef struct
  {
    bool isEnabled;
    bool isCalculated;
    bool isScheduled;
    unsigned long calculatedPeriod;
    unsigned long value;
    unsigned long valueTotal;
  } TWidgetCounterConfig;

  unsigned long calcValueWithDirection(TUserMenuInfoblockCounterDirType _counterDir, unsigned long _inCnt, unsigned long _outCnt)
  {
    switch (_counterDir)
    {
      case UserMenuInfoblockCounterDirType_In:
        return _inCnt;

      case UserMenuInfoblockCounterDirType_Out:
        return _outCnt;

      case UserMenuInfoblockCounterDirType_Max:
        return Functions::Common::maxof<unsigned long>(_inCnt, _outCnt);

      case UserMenuInfoblockCounterDirType_Min:
        return Functions::Common::minof<unsigned long>(_inCnt, _outCnt);
    }

    return (_inCnt + _outCnt) / 2;
  }

  void processCounterStatistic(TWidgetCounterConfig* _widgetConfig, TUserMenuInfoblockCounterSetup* _counterSetup)
  {
    _widgetConfig->isCalculated = true;
    _widgetConfig->isScheduled = false;
    _widgetConfig->calculatedPeriod = curStatisticRecord.periodNumTo;
    _widgetConfig->value = 0;

    if (curStatisticRecord.status == GLOBAL::Counter::CounterStatisticProcessStatus_Error)
    {
      return;
    }

    switch (_counterSetup->counterType)
    {
      case UserMenuInfoblockCounterType_VisitorsHour:
      case UserMenuInfoblockCounterType_VisitorsDay:
      case UserMenuInfoblockCounterType_VisitorsWeek:
      case UserMenuInfoblockCounterType_VisitorsMonth:
        _widgetConfig->value = calcValueWithDirection(_counterSetup->counterDir, curStatisticRecord.InCnt, curStatisticRecord.OutCnt);
        break;

      case UserMenuInfoblockCounterType_NoSensorHour:
      case UserMenuInfoblockCounterType_NoSensorDay:
        _widgetConfig->value = curStatisticRecord.NoSensorSec / 60;
        break;
    }
  }

  void scheduleWidgetStatisticOperation(
    TWidgetCounterConfig* _widgetConfig,
    GLOBAL::Counter::TCounterStatisticType _counterStatisticType,
    unsigned long curPeriodFrom,
    unsigned char periodLng = 1)
  {
    if (periodLng <= 0)
    {
      _widgetConfig->valueTotal = 0;
      _widgetConfig->isCalculated = true;
      return;
    }

    unsigned long curPeriodTo = curPeriodFrom + periodLng - 1;

    if (_widgetConfig->isCalculated && (_widgetConfig->calculatedPeriod != curPeriodTo))
    {
      _widgetConfig->isCalculated = false;
    }

    if (_widgetConfig->isCalculated)
    {
      _widgetConfig->valueTotal = _widgetConfig->value;
    }
    else
    {
      curStatisticRecord.periodNumFrom = curPeriodFrom;
      curStatisticRecord.periodNumTo = curPeriodTo;

      if (GLOBAL::Counter::scheduleStatisticOperation(&curStatisticRecord, _counterStatisticType))
      {
        _widgetConfig->isScheduled = true;
      }
    }
  }

  void updateCounter(TWidgetCounterConfig* _widgetConfig, TUserMenuInfoblockCounterSetup* _counterSetup)
  {
    unsigned long curCounterPeriod;

    switch (_counterSetup->counterType)
    {
      case UserMenuInfoblockCounterType_VisitorsHour:
        if (_counterSetup->counterShift)
        {
          curCounterPeriod = GLOBAL::Counter::getPeriodNumHour(&GLOBAL::RTC::RTCDateTime) - _counterSetup->counterShift;
          scheduleWidgetStatisticOperation(_widgetConfig, GLOBAL::Counter::CounterStatisticType_Hour, curCounterPeriod);
        }
        else
        {
          _widgetConfig->valueTotal = calcValueWithDirection(_counterSetup->counterDir, GLOBAL::Counter::curPeriod.InCntHour, GLOBAL::Counter::curPeriod.OutCntHour);
          _widgetConfig->isCalculated = true;
        }
        break;

      case UserMenuInfoblockCounterType_VisitorsDay:
        if (_counterSetup->counterShift)
        {
          curCounterPeriod = GLOBAL::Counter::getPeriodNumDay(&GLOBAL::RTC::RTCDateTime) - _counterSetup->counterShift;
          scheduleWidgetStatisticOperation(_widgetConfig, GLOBAL::Counter::CounterStatisticType_Day, curCounterPeriod);
        }
        else
        {
          _widgetConfig->valueTotal = calcValueWithDirection(_counterSetup->counterDir, GLOBAL::Counter::curPeriod.InCntDay, GLOBAL::Counter::curPeriod.OutCntDay);
          _widgetConfig->isCalculated = true;
        }
        break;

      case UserMenuInfoblockCounterType_VisitorsWeek:
        curCounterPeriod = GLOBAL::Counter::getPeriodNumDay(&GLOBAL::RTC::RTCDateTime) - GLOBAL::RTC::RTCDateTime.weekDay - (7 * _counterSetup->counterShift);
        scheduleWidgetStatisticOperation(_widgetConfig, GLOBAL::Counter::CounterStatisticType_Day, curCounterPeriod, _counterSetup->counterShift ? 7 : GLOBAL::RTC::RTCDateTime.weekDay);
        if (_widgetConfig->isCalculated && (!_counterSetup->counterShift))
        {
          _widgetConfig->valueTotal += calcValueWithDirection(_counterSetup->counterDir, GLOBAL::Counter::curPeriod.InCntDay, GLOBAL::Counter::curPeriod.OutCntDay);
        }
        break;

      case UserMenuInfoblockCounterType_VisitorsMonth:
        if (_counterSetup->counterShift)
        {
          curCounterPeriod = GLOBAL::Counter::getPeriodNumMonth(&GLOBAL::RTC::RTCDateTime) - _counterSetup->counterShift;
          scheduleWidgetStatisticOperation(_widgetConfig, GLOBAL::Counter::CounterStatisticType_Month, curCounterPeriod);
        }
        else
        {
          _widgetConfig->valueTotal = calcValueWithDirection(_counterSetup->counterDir, GLOBAL::Counter::curPeriod.InCntMonth, GLOBAL::Counter::curPeriod.OutCntMonth);
          _widgetConfig->isCalculated = true;
        }
        break;

      case UserMenuInfoblockCounterType_VisitorsTotal:
        _widgetConfig->valueTotal = calcValueWithDirection(_counterSetup->counterDir, GLOBAL::Counter::totalInCnt, GLOBAL::Counter::totalOutCnt);
        _widgetConfig->isCalculated = true;
        break;

      case UserMenuInfoblockCounterType_NoSensorHour:
        if (_counterSetup->counterShift)
        {
          curCounterPeriod = GLOBAL::Counter::getPeriodNumHour(&GLOBAL::RTC::RTCDateTime) - _counterSetup->counterShift;
          scheduleWidgetStatisticOperation(_widgetConfig, GLOBAL::Counter::CounterStatisticType_Hour, curCounterPeriod);
        }
        else
        {
          _widgetConfig->valueTotal = GLOBAL::Counter::curPeriod.NoSensorSecHour / 60;
          _widgetConfig->isCalculated = true;
        }
        break;

      case UserMenuInfoblockCounterType_NoSensorDay:
        if (_counterSetup->counterShift)
        {
          curCounterPeriod = GLOBAL::Counter::getPeriodNumDay(&GLOBAL::RTC::RTCDateTime) - _counterSetup->counterShift;
          scheduleWidgetStatisticOperation(_widgetConfig, GLOBAL::Counter::CounterStatisticType_Day, curCounterPeriod);
        }
        else
        {
          _widgetConfig->valueTotal = GLOBAL::Counter::curPeriod.NoSensorSecDay / 60;
          _widgetConfig->isCalculated = true;
        }
        break;

      default:
        _widgetConfig->isCalculated = true;
        break;
    }
  }

  void displayWidgetBackground(TUserMenuInfoblockType _infoblockType, bool _designPreview = false)
  {
    switch (_infoblockType)
    {
      case UserMenuInfoblockType_None:
        if (_designPreview)
        {
          LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_TEXT_WIDGET_SWITCHED_OFF), LCDDriver::LCDTextIdentation_Center);
        }
        break;

      case UserMenuInfoblockType_DateTimeFull2Cnt:
        LCDDriver::num2Buf(0, 1, GLOBAL::RTC::RTCDateTime.day, 2, LCD_DISPLAY_SYMBOL_SPACE);
        LCDDriver::displayState.line[0][2] = LCD_DISPLAY_SYMBOL_DASH;
        LCDDriver::num2Buf(0, 4, GLOBAL::RTC::RTCDateTime.month, 2, '0');
        LCDDriver::displayState.line[0][5] = LCD_DISPLAY_SYMBOL_DASH;
        LCDDriver::num2Buf(0, 9, GLOBAL::RTC::RTCDateTime.year, 4, LCD_DISPLAY_SYMBOL_SPACE);

        LCDDriver::num2Buf(1, 1, GLOBAL::RTC::RTCDateTime.hour, 2, LCD_DISPLAY_SYMBOL_SPACE);
        LCDDriver::displayState.line[1][2] = LCD_DISPLAY_SYMBOL_COLON;
        LCDDriver::num2Buf(1, 4, GLOBAL::RTC::RTCDateTime.minute, 2, '0');
        LCDDriver::displayState.line[1][5] = LCD_DISPLAY_SYMBOL_COLON;
        LCDDriver::num2Buf(1, 7, GLOBAL::RTC::RTCDateTime.second, 2, '0');

        if (_designPreview)
        {
          LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_TEXT_WIDGET_COUNTER1_SHORT), LCDDriver::LCDTextIdentation_Right, 15);
          LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_TEXT_WIDGET_COUNTER2_SHORT), LCDDriver::LCDTextIdentation_Right, 15);
        }
        break;

      case UserMenuInfoblockType_DateTimeShort2Cnt:
      case UserMenuInfoblockType_DateTimeShort1Cnt:
        LCDDriver::num2Buf(0, 1, GLOBAL::RTC::RTCDateTime.day, 2, LCD_DISPLAY_SYMBOL_SPACE);
        LCDDriver::displayState.line[0][2] = LCD_DISPLAY_SYMBOL_SLASH;
        LCDDriver::num2Buf(0, 4, GLOBAL::RTC::RTCDateTime.month, 2, '0');
        LCDDriver::displayState.line[0][5] = LCD_DISPLAY_SYMBOL_SLASH;
        LCDDriver::num2Buf(0, 7, GLOBAL::RTC::RTCDateTime.year % 100, 2, '0');

        LCDDriver::num2Buf(0, 10, GLOBAL::RTC::RTCDateTime.hour, 2, LCD_DISPLAY_SYMBOL_SPACE);
        LCDDriver::displayState.line[0][11] = LCD_DISPLAY_SYMBOL_COLON;
        LCDDriver::num2Buf(0, 13, GLOBAL::RTC::RTCDateTime.minute, 2, '0');

        if (_designPreview)
        {
          if (_infoblockType == UserMenuInfoblockType_DateTimeShort1Cnt)
          {
            LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_TEXT_WIDGET_COUNTER1_LONG), LCDDriver::LCDTextIdentation_Right, 15);
          }
          else
          {
            LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_TEXT_WIDGET_COUNTER1_SHORT), LCDDriver::LCDTextIdentation_Right, 6);
            LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_TEXT_WIDGET_COUNTER2_SHORT), LCDDriver::LCDTextIdentation_Right, 15);
          }
        }
        break;

      case UserMenuInfoblockType_Counter2:
        if (_designPreview)
        {
          LCDDriver::str2Buf(0, getString(USER_TEXT_CONST_TEXT_WIDGET_COUNTER1_LONG), LCDDriver::LCDTextIdentation_Right, 15);
          LCDDriver::str2Buf(1, getString(USER_TEXT_CONST_TEXT_WIDGET_COUNTER2_LONG), LCDDriver::LCDTextIdentation_Right, 15);
        }
        break;
    }
  }

  void displayWidgetCounterName(
    TUserMenuInfoblockCounterSetup* _counterSetup,
    unsigned char _posY,
    unsigned char _posX,
    bool _extended)
  {
    unsigned short strId;

    switch (_counterSetup->counterType)
    {
      case UserMenuInfoblockCounterType_NoSensorHour:
      case UserMenuInfoblockCounterType_NoSensorDay:
        strId = USER_TEXT_CONST_TEXT_WIDGET_NOSENSOR;
        break;

      default:
        switch (_counterSetup->counterDir)
        {
          case UserMenuInfoblockCounterDirType_Out:
            strId = USER_TEXT_CONST_TEXT_WIDGET_COUNT_OUT;
            break;

          case UserMenuInfoblockCounterDirType_Avg:
            strId = USER_TEXT_CONST_TEXT_WIDGET_COUNT_AVG;
            break;

          case UserMenuInfoblockCounterDirType_Max:
            strId = USER_TEXT_CONST_TEXT_WIDGET_COUNT_MAX;
            break;

          case UserMenuInfoblockCounterDirType_Min:
            strId = USER_TEXT_CONST_TEXT_WIDGET_COUNT_MIN;
            break;

          default:
            strId = USER_TEXT_CONST_TEXT_WIDGET_COUNT_IN;
            break;
        }
        break;
    }

    LCDDriver::str2Buf(_posY, getString(strId), LCDDriver::LCDTextIdentation_Left, _posX);

    if (_extended)
    {
      switch (_counterSetup->counterType)
      {
        case UserMenuInfoblockCounterType_VisitorsHour:
        case UserMenuInfoblockCounterType_NoSensorHour:
          strId = USER_TEXT_CONST_TEXT_WIDGET_HOUR_SHORT;
          break;

        case UserMenuInfoblockCounterType_VisitorsDay:
        case UserMenuInfoblockCounterType_NoSensorDay:
          strId = USER_TEXT_CONST_TEXT_WIDGET_DAY_SHORT;
          break;

        case UserMenuInfoblockCounterType_VisitorsWeek:
          strId = USER_TEXT_CONST_TEXT_WIDGET_WEEK_SHORT;
          break;

        case UserMenuInfoblockCounterType_VisitorsMonth:
          strId = USER_TEXT_CONST_TEXT_WIDGET_MONTH_SHORT;
          break;

        case UserMenuInfoblockCounterType_VisitorsTotal:
          strId = USER_TEXT_CONST_TEXT_WIDGET_TOTAL_SHORT;
          break;
      }

      LCDDriver::str2Buf(_posY, getString(strId), LCDDriver::LCDTextIdentation_Left, _posX + 3);

      if (_counterSetup->counterShift && (_counterSetup->counterType != UserMenuInfoblockCounterType_VisitorsTotal))
      {
        LCDDriver::displayState.line[_posY][_posX + 4] = LCD_DISPLAY_SYMBOL_DASH;

        if (_counterSetup->counterShift >= 100)
        {
          LCDDriver::num2Buf(_posY, _posX + 7, _counterSetup->counterShift, 3);
        }
        else if (_counterSetup->counterShift >= 10)
        {
          LCDDriver::num2Buf(_posY, _posX + 6, _counterSetup->counterShift, 2);
        }
        else
        {
          LCDDriver::num2Buf(_posY, _posX + 5, _counterSetup->counterShift, 1);
        }
      }
    }
  }

  void displayWidgetCounterValue(
    TUserMenuInfoblockSetup* _widgetConfig,
    TWidgetCounterConfig* _counterSetup1,
    TWidgetCounterConfig* _counterSetup2,
    bool _waiting = false)
  {
    typedef enum
    {
      WidgetCounterNameDisplayType_None = 0,
      WidgetCounterNameDisplayType_Short = 1,
      WidgetCounterNameDisplayType_Full = 2,
    } TWidgetCounterNameDisplayType;

    unsigned char counter1PosY = 0;
    unsigned char counter1PosX = 0;
    unsigned char counter1Lng = 0;
    unsigned char name1PosX = 0;
    TWidgetCounterNameDisplayType name1Type = WidgetCounterNameDisplayType_None;

    unsigned char counter2PosY = 0;
    unsigned char counter2PosX = 0;
    unsigned char counter2Lng = 0;
    unsigned char name2PosX = 0;
    TWidgetCounterNameDisplayType name2Type = WidgetCounterNameDisplayType_None;

    unsigned char lowBatterySymbolPosY = 0;
    unsigned char lowBatterySymbolPosX = 0;

    switch (_widgetConfig->infoblockType)
    {
      case UserMenuInfoblockType_DateTimeFull2Cnt:
        counter1PosY = 0;
        counter1PosX = 15;
        counter1Lng = 6;

        counter2PosY = 1;
        counter2PosX = 15;
        counter2Lng = 6;

        lowBatterySymbolPosY = 1;
        lowBatterySymbolPosX = 9;
        break;

      case UserMenuInfoblockType_DateTimeShort2Cnt:
        counter1PosY = 1;
        counter1PosX = 6;
        counter1Lng = 7;
        name1PosX = 0;
        name1Type = WidgetCounterNameDisplayType_Short;

        counter2PosY = 1;
        counter2PosX = 15;
        counter2Lng = 7;
        name2PosX = 8;
        name2Type = WidgetCounterNameDisplayType_Short;

        lowBatterySymbolPosY = 0;
        lowBatterySymbolPosX = 15;
        break;

      case UserMenuInfoblockType_DateTimeShort1Cnt:
        counter1PosY = 1;
        counter1PosX = 15;
        counter1Lng = 8;
        name1PosX = 0;
        name1Type = WidgetCounterNameDisplayType_Full;

        lowBatterySymbolPosY = 0;
        lowBatterySymbolPosX = 15;
        break;

      case UserMenuInfoblockType_Counter2:
        counter1PosY = 0;
        counter1PosX = 15;
        counter1Lng = 8;
        name1PosX = 0;
        name1Type = WidgetCounterNameDisplayType_Full;

        counter2PosY = 1;
        counter2PosX = 15;
        counter2Lng = 8;
        name2PosX = 0;
        name2Type = WidgetCounterNameDisplayType_Full;
        break;
    }

    if (_counterSetup1->isEnabled && counter1Lng)
    {
      if (name1Type != WidgetCounterNameDisplayType_None)
      {
        displayWidgetCounterName(&(_widgetConfig->counter1), counter1PosY, name1PosX, name1Type == WidgetCounterNameDisplayType_Full);
      }

      if (_waiting)
      {
        LCDDriver::displayState.line[counter1PosY][counter1PosX] = LCD_DISPLAY_SYMBOL_SUN;
      }
      else
      {
        LCDDriver::num2Buf(counter1PosY, counter1PosX, _counterSetup1->valueTotal, counter1Lng);
      }
    }

    if (_counterSetup2->isEnabled && counter2Lng)
    {
      if (name2Type != WidgetCounterNameDisplayType_None)
      {
        displayWidgetCounterName(&(_widgetConfig->counter2), counter2PosY, name2PosX, name2Type == WidgetCounterNameDisplayType_Full);
      }

      if (_waiting)
      {
        LCDDriver::displayState.line[counter2PosY][counter2PosX] = LCD_DISPLAY_SYMBOL_SUN;
      }
      else
      {
        LCDDriver::num2Buf(counter2PosY, counter2PosX, _counterSetup2->valueTotal, counter2Lng);
      }
    }

    LCDDriver::refreshDisplay(LCDDriver::LCDDisplayMode_NoCursor, 0, 0, true, lowBatterySymbolPosY, lowBatterySymbolPosX);
  }

  void functionWidget()
  {
    if (UserInterfaceSetup.infoblockMain.infoblockType == UserMenuInfoblockType_None)
    {
      switch (menuAuthLevel)
      {
        case MenuAuthLevel_Master:
          updateMenuStack(menuStackPos, USER_MENUITEM_MAIN_MENU);
          break;

        case MenuAuthLevel_Reports:
          updateMenuStack(menuStackPos, USER_MENUITEM_MAIN_MENU_REPORTS);
          break;
      }

      isTransition = true;
      return;
    }

    while (transitionKey)
    {
      switch (transitionKey)
      {
        case 1:
          return;

        case 2:
          switch (menuStack[menuStackPos].funcState)
          {
            case 0:
              menuStack[menuStackPos].funcState = 1;
              activeFunctionChanged = true;
              break;

            case 2:
              menuStack[menuStackPos].funcState = 0;
              activeFunctionChanged = true;
              break;
          }
          break;

        case 3:
          switch (menuStack[menuStackPos].funcState)
          {
            case 0:
              menuStack[menuStackPos].funcState = 2;
              activeFunctionChanged = true;
              break;

            case 1:
              menuStack[menuStackPos].funcState = 0;
              activeFunctionChanged = true;
              break;
          }
          break;

        case 4:
          switch (menuAuthLevel)
          {
            case MenuAuthLevel_Master:
              transitionUp(USER_MENUITEM_MAIN_MENU);
              break;

            case MenuAuthLevel_Reports:
              transitionUp(USER_MENUITEM_MAIN_MENU_REPORTS);
              break;
          }
          return;
      }

      getNextTransitionKey();
    }

    TWidgetCounterConfig* curCounter1 = (TWidgetCounterConfig*)activeParmSpace;
    TWidgetCounterConfig* curCounter2 = (TWidgetCounterConfig*)(activeParmSpace + sizeof(TWidgetCounterConfig));

    TUserMenuInfoblockSetup* curWidgetConfig;

    switch (menuStack[menuStackPos].funcState)
    {
      case 1:
        curWidgetConfig = &(UserInterfaceSetup.infoblockLeft);
        break;

      case 2:
        curWidgetConfig = &(UserInterfaceSetup.infoblockRight);
        break;

      default:
        curWidgetConfig = &(UserInterfaceSetup.infoblockMain);
        break;
    }

    if (activeFunctionChanged)
    {
      curCounter1->isEnabled = (curWidgetConfig->infoblockType != UserMenuInfoblockType_None) &&
                               (curWidgetConfig->counter1.counterType != UserMenuInfoblockCounterType_None);
      curCounter1->isCalculated = false;
      curCounter1->isScheduled = false;

      curCounter2->isEnabled = (curWidgetConfig->infoblockType != UserMenuInfoblockType_None) &&
                               (curWidgetConfig->infoblockType != UserMenuInfoblockType_DateTimeShort1Cnt) &&
                               (curWidgetConfig->counter2.counterType != UserMenuInfoblockCounterType_None);
      curCounter2->isCalculated = false;
      curCounter2->isScheduled = false;

      curStatisticRecord.status = GLOBAL::Counter::CounterStatisticProcessStatus_None;
    }

    LCDDriver::clearBuffer();

    displayWidgetBackground(curWidgetConfig->infoblockType);

    if (curStatisticRecord.status == GLOBAL::Counter::CounterStatisticProcessStatus_Scheduled)
    {
      displayWidgetCounterValue(curWidgetConfig, curCounter1, curCounter2, true);
      return;
    }

    if (curStatisticRecord.status != GLOBAL::Counter::CounterStatisticProcessStatus_None)
    {
      if (curCounter1->isEnabled && curCounter1->isScheduled)
      {
        processCounterStatistic(curCounter1, &(curWidgetConfig->counter1));
      }
      else
      if (curCounter2->isEnabled && curCounter2->isScheduled)
      {
        processCounterStatistic(curCounter2, &(curWidgetConfig->counter2));
      }

      curStatisticRecord.status = GLOBAL::Counter::CounterStatisticProcessStatus_None;
    }

    if (curCounter1->isEnabled)
    {
      updateCounter(curCounter1, &(curWidgetConfig->counter1));
      if (!curCounter1->isCalculated)
      {
        displayWidgetCounterValue(curWidgetConfig, curCounter1, curCounter2, true);
        return;
      }
    }

    if (curCounter2->isEnabled)
    {
      updateCounter(curCounter2, &(curWidgetConfig->counter2));
      if (!curCounter2->isCalculated)
      {
        displayWidgetCounterValue(curWidgetConfig, curCounter1, curCounter2, true);
        return;
      }
    }

    displayWidgetCounterValue(curWidgetConfig, curCounter1, curCounter2);
  }

  void functionSetupWidgets()
  {
    TUserMenuInfoblockSetup* curWidgetSetup = (TUserMenuInfoblockSetup*)activeParmSpace;
    unsigned char* curWidgetSetupStatus = (unsigned char*)(activeParmSpace + sizeof(TUserMenuInfoblockSetup));

    TUserMenuInfoblockSetup* curUserInterfaceSetupWidget;
    TUserMenuInfoblockCounterSetup* curCounterSetup;

    switch (menuStack[menuStackPos].funcState)
    {
      case 1:
        curUserInterfaceSetupWidget = &(UserInterfaceSetup.infoblockLeft);
        break;

      case 2:
        curUserInterfaceSetupWidget = &(UserInterfaceSetup.infoblockRight);
        break;

      default:
        curUserInterfaceSetupWidget = &(UserInterfaceSetup.infoblockMain);
        break;
    }

    if (activeFunctionChanged)
    {
      *curWidgetSetup = *curUserInterfaceSetupWidget;
      (*curWidgetSetupStatus) = 0;
    }

    switch (*curWidgetSetupStatus)
    {
      case 5:
      case 6:
      case 7:
      case 8:
        curCounterSetup = &(curWidgetSetup->counter2);
        break;

      default:
        curCounterSetup = &(curWidgetSetup->counter1);
        break;
    }

    while (transitionKey)
    {
      unsigned char setupMaxStep = 0;
      unsigned char difValue;

      switch (transitionKey)
      {
        case 1:
          switch (*curWidgetSetupStatus)
          {
            case 0:
              return;

            case 5:
              (*curWidgetSetupStatus) = 1;
               break;

            case 4:
            case 8:
              switch (curCounterSetup->counterType)
              {
                case UserMenuInfoblockCounterType_NoSensorHour:
                case UserMenuInfoblockCounterType_NoSensorDay:
                  (*curWidgetSetupStatus) -= 2;
                  break;

                default:
                  (*curWidgetSetupStatus)--;
                  break;
              }
              break;

            default:
              (*curWidgetSetupStatus)--;
              break;
          }
          break;

        case 2:
        case 3:
          switch (*curWidgetSetupStatus)
          {
            case 0:
              difValue = (transitionKey == 2) ? UserMenuInfoblockType_Counter2 : 1;
              curWidgetSetup->infoblockType = (TUserMenuInfoblockType)((curWidgetSetup->infoblockType + difValue) % (UserMenuInfoblockType_Counter2 + 1));
              break;

            case 2:
            case 6:
              difValue = (transitionKey == 2) ? UserMenuInfoblockCounterType_NoSensorDay : 1;
              curCounterSetup->counterType = (TUserMenuInfoblockCounterType)((curCounterSetup->counterType + difValue) % (UserMenuInfoblockCounterType_NoSensorDay + 1));
              break;

            case 3:
            case 7:
              difValue = (transitionKey == 2) ? UserMenuInfoblockCounterDirType_Min : 1;
              curCounterSetup->counterDir = (TUserMenuInfoblockCounterDirType)((curCounterSetup->counterDir + difValue) % (UserMenuInfoblockCounterDirType_Min + 1));
              break;

            case 4:
            case 8:
              difValue = (transitionKey == 2) ? 255 : 1;
              curCounterSetup->counterShift = curCounterSetup->counterShift + difValue;
              break;
          }
          break;

        case 4:
          switch (curWidgetSetup->infoblockType)
          {
            case UserMenuInfoblockType_None:
              setupMaxStep = 0;
              break;

            case UserMenuInfoblockType_DateTimeShort1Cnt:
              setupMaxStep = 4;
              break;

            default:
              setupMaxStep = 8;
              break;
          }

          switch (*curWidgetSetupStatus)
          {
            case 2:
            case 6:
              switch (curCounterSetup->counterType)
              {
                case UserMenuInfoblockCounterType_None:
                  (*curWidgetSetupStatus) += 3;
                  break;

                case UserMenuInfoblockCounterType_NoSensorHour:
                case UserMenuInfoblockCounterType_NoSensorDay:
                  (*curWidgetSetupStatus) += 2;
                  break;

                default:
                  (*curWidgetSetupStatus)++;
                  break;
              }
              break;

            case 3:
            case 7:
              if (curCounterSetup->counterType == UserMenuInfoblockCounterType_VisitorsTotal)
              {
                (*curWidgetSetupStatus) += 2;
              }
              else
              {
                (*curWidgetSetupStatus)++;
              }
              break;

            default:
              (*curWidgetSetupStatus)++;
              break;
          }

          if ((*curWidgetSetupStatus) > setupMaxStep)
          {
            *curUserInterfaceSetupWidget = *curWidgetSetup;
            DeviceManager::saveUserInterfaceSetup();
            processMenuOptionChanged();
            return;
          }
          return;
      }

      switch (*curWidgetSetupStatus)
      {
        case 5:
        case 6:
        case 7:
        case 8:
          curCounterSetup = &(curWidgetSetup->counter2);
          break;

        default:
          curCounterSetup = &(curWidgetSetup->counter1);
          break;
      }

      getNextTransitionKey();
    }

    LCDDriver::clearBuffer();

    unsigned short curTextConstL1 = 0;
    unsigned short curTextConstL2 = 0;
    unsigned short curShiftSymbolL2 = 0;

    switch (*curWidgetSetupStatus)
    {
      case 0:
        displayWidgetBackground(curWidgetSetup->infoblockType, true);
        break;

      case 1:
        curTextConstL1 = USER_TEXT_CONST_TEXT_WIDGET_COUNTER1_LONG;
        break;

      case 5:
        curTextConstL1 = USER_TEXT_CONST_TEXT_WIDGET_COUNTER2_LONG;
        break;

      case 2:
      case 6:
        switch (curCounterSetup->counterType)
        {
          case UserMenuInfoblockCounterType_None:
            curTextConstL1 = USER_TEXT_CONST_TEXT_WIDGET_SWITCHED_OFF;
            break;

          case UserMenuInfoblockCounterType_VisitorsHour:
            curTextConstL1 = USER_TEXT_CONST_REPORTS_VISITORS;
            curTextConstL2 = USER_TEXT_CONST_REPORTS_HOUR;
            break;

          case UserMenuInfoblockCounterType_VisitorsDay:
            curTextConstL1 = USER_TEXT_CONST_REPORTS_VISITORS;
            curTextConstL2 = USER_TEXT_CONST_REPORTS_DAY;
            break;

          case UserMenuInfoblockCounterType_VisitorsWeek:
            curTextConstL1 = USER_TEXT_CONST_REPORTS_VISITORS;
            curTextConstL2 = USER_TEXT_CONST_REPORTS_WEEK;
            break;

          case UserMenuInfoblockCounterType_VisitorsMonth:
            curTextConstL1 = USER_TEXT_CONST_REPORTS_VISITORS;
            curTextConstL2 = USER_TEXT_CONST_REPORTS_MONTH;
            break;

          case UserMenuInfoblockCounterType_VisitorsTotal:
            curTextConstL1 = USER_TEXT_CONST_REPORTS_VISITORS;
            curTextConstL2 = USER_TEXT_CONST_REPORTS_TOTAL;
            break;

          case UserMenuInfoblockCounterType_NoSensorHour:
            curTextConstL1 = USER_TEXT_CONST_REPORTS_NOSENSOR;
            curTextConstL2 = USER_TEXT_CONST_REPORTS_HOUR;
            break;

          case UserMenuInfoblockCounterType_NoSensorDay:
            curTextConstL1 = USER_TEXT_CONST_REPORTS_NOSENSOR;
            curTextConstL2 = USER_TEXT_CONST_REPORTS_DAY;
            break;
        }
        break;

      case 3:
      case 7:
        curTextConstL1 = USER_TEXT_CONST_TEXT_WIDGET_COUNTER_AGGREGATION_MODE;
        switch (curCounterSetup->counterDir)
        {
          case UserMenuInfoblockCounterDirType_In:
            curTextConstL2 = USER_TEXT_CONST_TEXT_WIDGET_COUNTER_AGGREGATION_IN;
            break;

          case UserMenuInfoblockCounterDirType_Out:
            curTextConstL2 = USER_TEXT_CONST_TEXT_WIDGET_COUNTER_AGGREGATION_OUT;
            break;

          case UserMenuInfoblockCounterDirType_Avg:
            curTextConstL2 = USER_TEXT_CONST_TEXT_WIDGET_COUNTER_AGGREGATION_AVG;
            break;

          case UserMenuInfoblockCounterDirType_Max:
            curTextConstL2 = USER_TEXT_CONST_TEXT_WIDGET_COUNTER_AGGREGATION_MAX;
            break;

          case UserMenuInfoblockCounterDirType_Min:
            curTextConstL2 = USER_TEXT_CONST_TEXT_WIDGET_COUNTER_AGGREGATION_MIN;
            break;
        }
        break;

      case 4:
      case 8:
        curTextConstL2 = USER_TEXT_CONST_TEXT_WIDGET_COUNTER_SHIFT;
        LCDDriver::num2Buf(1, 13, curCounterSetup->counterShift, 3, LCD_DISPLAY_SYMBOL_SPACE);

        switch (curCounterSetup->counterType)
        {
          case UserMenuInfoblockCounterType_VisitorsHour:
          case UserMenuInfoblockCounterType_NoSensorHour:
            curShiftSymbolL2 = USER_TEXT_CONST_TEXT_WIDGET_HOUR_SHORT;
            break;

          case UserMenuInfoblockCounterType_VisitorsDay:
          case UserMenuInfoblockCounterType_NoSensorDay:
            curShiftSymbolL2 = USER_TEXT_CONST_TEXT_WIDGET_DAY_SHORT;
            break;

          case UserMenuInfoblockCounterType_VisitorsWeek:
            curShiftSymbolL2 = USER_TEXT_CONST_TEXT_WIDGET_WEEK_SHORT;
            break;

          case UserMenuInfoblockCounterType_VisitorsMonth:
            curShiftSymbolL2 = USER_TEXT_CONST_TEXT_WIDGET_MONTH_SHORT;
            break;
        }
        break;
    }

    if (curTextConstL1)
    {
      LCDDriver::str2Buf(0, getString(curTextConstL1), LCDDriver::LCDTextIdentation_Center);
    }

    if (curTextConstL2)
    {
      LCDDriver::str2Buf(1, getString(curTextConstL2), LCDDriver::LCDTextIdentation_Center);
    }

    if (curShiftSymbolL2)
    {
      LCDDriver::str2Buf(1, getString(curShiftSymbolL2), LCDDriver::LCDTextIdentation_Left, 15);
    }

    LCDDriver::refreshDisplay(LCDDriver::LCDDisplayMode_NoCursor);
  }
}

#endif
