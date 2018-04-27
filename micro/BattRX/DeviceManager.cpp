#ifndef __DEVICEMANAGER_CPP_
#define __DEVICEMANAGER_CPP_

#include "DeviceManager.h"
#include "GlobalDeviceProfile.h"

#include "GlobalRTC.h"
#include "GlobalADC.h"
#include "MultyThreading.h"
#include "Timer0Handler.h"
#include "Timer2Handler.h"
#include "PhotoSensor.h"
#include "KeyBoardDriver.h"
#include "CommProtocol_TWI_Master.h"
#include "CommProtocol_SPI_Master.h"
#include "LCDDriver.h"
#include "MemAT25Driver.h"
#include "GlobalCounter.h"
#include "IndicatorDriver.h"
#include "BacklightDriver.h"
#include "UserInterface.h"
#include "MainThread.h"
#include "CRC8.h"

#define DEVICE_APPLICATION_VERSION  {0x01, 0x01, 0x01, 0x0001}
#define DEVICE_SERIAL_NUMBER        {0x8B, 0x80, 0x0C, 0x57, 0xDF, 5, "R4EK3CHNK8Q6CD64"}

using namespace GLOBAL::DeviceProfile;

namespace DeviceManager
{
  __flash const TApplicationVersion FFApplicationVersion = DEVICE_APPLICATION_VERSION;

  __eeprom TDeviceSerialNumber EEDeviceSerialNumber = DEVICE_SERIAL_NUMBER;
  __eeprom TDeviceCounterConfig EEDefaultDeviceCounterConfig =
    {
      .detectDirection = CounterDetectDirectionType_NoDetectionDiv2,  //Детекция направления
      .invertCounting = false,                                        //Не инвертировать счет
      .bodyDetectionLevel = (70 / timerDiscreteness),                 //Количество периодов детекции объекта
    };

  __eeprom TDeviceAdvancedSetup EEDefaultDeviceAdvancedSetup =
  {
    .batterySaveMode = DeviceBatterySaveMode_Max,                   //Режим экономии батареи
    .backlight = true,                                              //Подсветка в меню
    .inactivityTime = 15,                                           //Время бездействия (в секундах)
    .workWeekMask = 0x7F,                                           //Маска рабочей недели
    .workDayStruct = WorkDayShiftStructure_Shift1,                  //Структура рабочего дня: одна смена
    .shiftStart1 = 540,                                             //Начало смены: 9-00
    .shiftEnd1 = 1260,                                              //Конец смены: 21-00
    .shiftStart2 = 780,                                             //Начало обеда: 13-00
    .shiftEnd2 = 840,                                               //Конец обеда: 14-00
#if (BATTERY_CONFIGURATION_SELECTED == BATTERY_CONFIGURATION_LI)
    .batteryCutOff = 300,                                           //3.00 V
#else
    .batteryCutOff = 200,                                           //2.00 V
#endif
  };

  __eeprom TUserInterfaceSetup EEDefaultUserInterfaceSetup =
  {
    .language = UserInterfaceLanguage_RUS,
    .screenSaverSetup =
    {
      .screenSaverType = UserMenuScreenSaverType_Default,
      .defaultLine0 = {0x20, 0x20, 0x20, 0x20,  'M',  'C',  'O',  'U',  'N',  'T',  'E',  'R', 0x20, 0x20, 0x20, 0x20},
      .defaultLine1 = {0x20, 0x20, 0x20, 0x20, 0x20,  'a',  't',  't',  'o',  'm', 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    },

    .infoblockMain =
    {
      .infoblockType = UserMenuInfoblockType_DateTimeShort2Cnt,
      .counter1 =
      {
        .counterType = UserMenuInfoblockCounterType_VisitorsHour,
        .counterDir = UserMenuInfoblockCounterDirType_In,
        .counterShift = 0,
      },
      .counter2 =
      {
        .counterType = UserMenuInfoblockCounterType_VisitorsDay,
        .counterDir = UserMenuInfoblockCounterDirType_In,
        .counterShift = 0,
      },
    },

    .infoblockLeft =
    {
      .infoblockType = UserMenuInfoblockType_Counter2,
      .counter1 =
      {
        .counterType = UserMenuInfoblockCounterType_VisitorsDay,
        .counterDir = UserMenuInfoblockCounterDirType_In,
        .counterShift = 1,
      },
      .counter2 =
      {
        .counterType = UserMenuInfoblockCounterType_VisitorsWeek,
        .counterDir = UserMenuInfoblockCounterDirType_In,
        .counterShift = 0,
      },
    },

    .infoblockRight =
    {
      .infoblockType = UserMenuInfoblockType_Counter2,
      .counter1 =
      {
        .counterType = UserMenuInfoblockCounterType_VisitorsWeek,
        .counterDir = UserMenuInfoblockCounterDirType_In,
        .counterShift = 1,
      },
      .counter2 =
      {
        .counterType = UserMenuInfoblockCounterType_VisitorsMonth,
        .counterDir = UserMenuInfoblockCounterDirType_In,
        .counterShift = 0,
      },
    },
  };

  __eeprom TDeviceStartAction EEDeviceStartAction = DeviceStartAction_FirstStart;

  typedef struct
  {
    unsigned short year;
    unsigned char month;    //1-12
    unsigned char day;      //1-31
    unsigned char hour;     //0-23
    unsigned char minute;   //0-59
    unsigned char second;   //0-59
    GLOBAL::RTC::TSummerTimeRule summerTimeRule;
  } TDeviceStatusSaved;

  typedef struct
  {
    unsigned long totalInCnt;
    unsigned long totalOutCnt;
    unsigned long totalRestarts;
    unsigned long totalDataReset;
    unsigned long totalFactoryReset;
    unsigned long totalPwdFails;
  } TDeviceTotalsSaved;

  __eeprom TDeviceStatusSaved EEDeviceStatusSaved =
  {
    .year = 2014,
    .month = 8,
    .day = 1,
    .hour = 0,
    .minute = 0,
    .second = 0,
    .summerTimeRule = GLOBAL::RTC::SummerTimeRule_Ukraine,
  };

  __eeprom TDeviceTotalsSaved EEDeviceTotalsSaved =
  {
    .totalInCnt = 0,
    .totalOutCnt = 0,
    .totalRestarts = 0,
    .totalDataReset = 0,
    .totalFactoryReset = 0,
    .totalPwdFails = 0,
  };

  __eeprom unsigned char EEPwdMaster[DEVICE_PASSWORD_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0};
  __eeprom unsigned char EEPwdReports[DEVICE_PASSWORD_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0};
  __eeprom unsigned char EEMemorySecureTemplate[EXT_MEMORY_SEGMENTSIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  __eeprom __no_init TDeviceCounterConfig EEDeviceCounterConfig;
  __eeprom __no_init TDeviceAdvancedSetup EEDeviceAdvancedSetup;
  __eeprom __no_init TUserInterfaceSetup EEUserInterfaceSetup;

  TDeviceStatusCode deviceStatusCode;

  void loadFactoryDefaults();
  void loadDeviceConfiguration();
  void initModules();
  void loadMemorySecureTemplate();
  void updateMemorySecureTemplate();

  void init()
  {
    EEDeviceTotalsSaved.totalRestarts++;

    bool isLoadFactoryDefaults = (EEDeviceStartAction == DeviceStartAction_FirstStart);

    if (EEDeviceStartAction == DeviceStartAction_FirstStart)
    {
      loadMemorySecureTemplate();
      updateMemorySecureTemplate();
    }

    if (!isLoadFactoryDefaults)
    {
      MENU_KEY1_DIR = 0;
      MENU_KEY1_PORT = 1;

      MENU_KEY4_DIR = 0;
      MENU_KEY4_PORT = 1;

      isLoadFactoryDefaults = true;

      for (unsigned char i = 0; i < 100; i++)
      {
        if (MENU_KEY1_PIN || MENU_KEY4_PIN)
        {
          isLoadFactoryDefaults = false;
          break;
        }
      }
    }

    if (isLoadFactoryDefaults)
    {
      loadFactoryDefaults();

      INDICATOR_LED_DIR = 1;
      INDICATOR_LED_PORT = 1;
      __delay_cycles(clockFrequency);
      INDICATOR_LED_PORT = 0;
      __delay_cycles(clockFrequency / 2);
    }

    loadDeviceConfiguration();

    deviceStatusCode = DeviceStatusCode_Initialization;

    initModules();
  }

  void loadFactoryDefaults()
  {
    EEDeviceTotalsSaved.totalFactoryReset++;

    EEDeviceCounterConfig = EEDefaultDeviceCounterConfig;
    EEDeviceAdvancedSetup = EEDefaultDeviceAdvancedSetup;
    EEUserInterfaceSetup = EEDefaultUserInterfaceSetup;

    for (unsigned char i = 0; i < DEVICE_PASSWORD_LENGTH; i++)
    {
      EEPwdMaster[i] = 0;
      EEPwdReports[i] = 0;
    }

    EEDeviceStartAction = DeviceStartAction_Standard;
  }

  void loadDeviceConfiguration()
  {
    ApplicationVersion = FFApplicationVersion;
    DeviceSerialNumber = EEDeviceSerialNumber;
    DeviceCounterConfig = EEDeviceCounterConfig;
    DeviceAdvancedSetup = EEDeviceAdvancedSetup;
    UserInterfaceSetup = EEUserInterfaceSetup;

    loadMemorySecureTemplate();
  }

  void loadMemorySecureTemplate()
  {
    for (unsigned char i = 0; i < EXT_MEMORY_SEGMENTSIZE; i++)
    {
      MemorySecureTemplate[i] = EEMemorySecureTemplate[i];
    }
  }

  void updateMemorySecureTemplate()
  {
    for (unsigned char i = 0; i < EXT_MEMORY_SEGMENTSIZE; i++)
    {
      MemorySecureTemplate[i] ^= *((&GLOBAL::RTC::RTCDateTime.day) + (i % 4));
    }

    for (unsigned char iteration = 0; iteration < 2; iteration++)
    {
      for (unsigned char i = 0; i < EXT_MEMORY_SEGMENTSIZE; i++)
      {
        MemorySecureTemplate[i] = CRC8::calcCRC8(MemorySecureTemplate, i + 1);
      }
    }

    for (unsigned char i = 0; i < EXT_MEMORY_SEGMENTSIZE; i++)
    {
      EEMemorySecureTemplate[i] = MemorySecureTemplate[i];
    }
  }

  void initModules()
  {
    Timer0Handler::init();
    Timer2Handler::init();

    GLOBAL::RTC::init(EEDeviceStatusSaved.year, EEDeviceStatusSaved.month, EEDeviceStatusSaved.day,
                      EEDeviceStatusSaved.hour, EEDeviceStatusSaved.minute, EEDeviceStatusSaved.second,
                      EEDeviceStatusSaved.summerTimeRule);
    GLOBAL::ADC::init(DeviceAdvancedSetup.batteryCutOff);
    GLOBAL::MultyThreading::init();

    PhotoSensor::init();

    CommProtocol_TWI_Master::init();
    LCDDriver::init();

    CommProtocol_SPI_Master::init();
    MemAT25Driver::init();

    GLOBAL::Counter::init();
    GLOBAL::Counter::setTotals(EEDeviceTotalsSaved.totalInCnt, EEDeviceTotalsSaved.totalOutCnt);

    KeyBoardDriver::init();
    IndicatorDriver::init();
    BacklightDriver::init();
    UserInterface::init();

    MainThread::init();
  }

#define MODULE_RUN_TABLE_SIZE         (11)
__flash const void* moduleRunTable[MODULE_RUN_TABLE_SIZE] =
{
  (void*)(&(GLOBAL::RTC::processIdleTime)),
  (void*)(&(GLOBAL::ADC::run)),
  (void*)(&(CommProtocol_SPI_Master::run)),
  (void*)(&(CommProtocol_TWI_Master::run)),
  (void*)(&(MemAT25Driver::run)),
  (void*)(&(LCDDriver::run)),
  (void*)(&(GLOBAL::Counter::run)),
  (void*)(&(IndicatorDriver::run)),
  (void*)(&(MainThread::run)),
  (void*)(&(KeyBoardDriver::run)),
  (void*)(&(UserInterface::run)),
};

  void run()
  {
    unsigned char curProcess = 0;

    while (true)
    {
      if (moduleRunTable[curProcess])
      {
        (*(void(*)(void))(moduleRunTable[curProcess]))();
      }

      __watchdog_reset();

      curProcess = (curProcess + 1) % MODULE_RUN_TABLE_SIZE;

      if (curProcess == 0)
      {
        GLOBAL::MultyThreading::processIdleTime();
      }
    }
  }

  void saveDeviceStatus()
  {
    TDeviceStatusSaved curDeviceStatus =
    {
      .year = GLOBAL::RTC::RTCDateTime.year,
      .month = GLOBAL::RTC::RTCDateTime.month,
      .day = GLOBAL::RTC::RTCDateTime.day,
      .hour = GLOBAL::RTC::RTCDateTime.hour,
      .minute = GLOBAL::RTC::RTCDateTime.minute,
      .second = GLOBAL::RTC::RTCDateTime.second,
      .summerTimeRule = GLOBAL::RTC::RTCConfig.summerTimeRule,
     };

    EEDeviceStatusSaved = curDeviceStatus;
  }

  void saveTotalsInOut(unsigned long _totalInCnt, unsigned long _totalOutCnt)
  {
    EEDeviceTotalsSaved.totalInCnt = _totalInCnt;
    EEDeviceTotalsSaved.totalOutCnt = _totalOutCnt;
  }

  void saveDeviceCounterConfig()
  {
    EEDeviceCounterConfig = DeviceCounterConfig;
  }

  void saveDeviceAdvancedSetup()
  {
    EEDeviceAdvancedSetup = DeviceAdvancedSetup;
    MainThread::calcIsDeviceActiveBySchedule();
  }

  void saveUserInterfaceSetup()
  {
    EEUserInterfaceSetup = UserInterfaceSetup;
  }

  __monitor void resetCounters()
  {
    GLOBAL::Counter::setTotals(0, 0);
    EEDeviceTotalsSaved.totalInCnt = 0;
    EEDeviceTotalsSaved.totalOutCnt = 0;
    EEDeviceTotalsSaved.totalRestarts = 0;
    EEDeviceTotalsSaved.totalPwdFails = 0;
  }

  __monitor void resetToFactoryDefaults()
  {
    loadFactoryDefaults();
    loadDeviceConfiguration();
  }

  __monitor void resetData()
  {
    updateMemorySecureTemplate();

    EEDeviceTotalsSaved.totalInCnt = 0;
    EEDeviceTotalsSaved.totalOutCnt = 0;
    EEDeviceTotalsSaved.totalDataReset++;

    GLOBAL::Counter::resetData();
  }

  __monitor void resetFull()
  {
    resetToFactoryDefaults();
    resetData();
    resetCounters();
  }

  void incPwdFails()
  {
    EEDeviceTotalsSaved.totalPwdFails++;
  }

  bool checkPasswordMaster(unsigned char* _password)
  {
    for (unsigned char i = 0; i < DEVICE_PASSWORD_LENGTH; i++)
    {
      if (_password[i] != EEPwdMaster[i])
      {
        return false;
      }
    }

    return true;
  }

  bool checkPasswordReports(unsigned char* _password)
  {
    for (unsigned char i = 0; i < DEVICE_PASSWORD_LENGTH; i++)
    {
      if (_password[i] != EEPwdReports[i])
      {
        return false;
      }
    }

    return true;
  }

  void setPasswordMaster(unsigned char* _password)
  {
    for (unsigned char i = 0; i < DEVICE_PASSWORD_LENGTH; i++)
    {
      EEPwdMaster[i] = _password[i];
    }
  }

  void setPasswordReports(unsigned char* _password)
  {
    for (unsigned char i = 0; i < DEVICE_PASSWORD_LENGTH; i++)
    {
      EEPwdReports[i] = _password[i];
    }
  }

  unsigned long getTotalRestarts()
  {
    return EEDeviceTotalsSaved.totalRestarts;
  }

  unsigned long getTotalDataReset()
  {
    return EEDeviceTotalsSaved.totalDataReset;
  }

  unsigned long getTotalFactoryReset()
  {
    return EEDeviceTotalsSaved.totalFactoryReset;
  }

  unsigned long getTotalPwdFails()
  {
    return EEDeviceTotalsSaved.totalPwdFails;
  }
}

#endif

