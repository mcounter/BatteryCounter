#ifndef __DEVICEMANAGER_CPP_
#define __DEVICEMANAGER_CPP_

#include "DeviceManager.h"
#include "GlobalDeviceProfile.h"

#include "GlobalADC.h"
#include "MultyThreading.h"
#include "Timer0Handler.h"
#include "KeyBoardDriver.h"
#include "IndicatorDriver.h"

#define DEVICE_APPLICATION_VERSION  {0x01, 0x02, 0x01, 0x0001}

using namespace GLOBAL::DeviceProfile;

namespace DeviceManager
{
  __flash const TApplicationVersion FFApplicationVersion = DEVICE_APPLICATION_VERSION;

  __eeprom TDeviceTransmitterConfig EEDefaultDeviceTransmitterConfig =
    {
      .transmitterMode = DeviceTransmitterMode_NoDetetion,

#if (BATTERY_CONFIGURATION_SELECTED == BATTERY_CONFIGURATION_LI)
    .batteryCutOff = 300,                                           //3.00 V
#else
    .batteryCutOff = 200,                                           //2.00 V
#endif
  };

  __eeprom TDeviceStartAction EEDeviceStartAction = DeviceStartAction_FirstStart;

  __eeprom __no_init TDeviceTransmitterConfig EEDeviceTransmitterConfig;

  void loadFactoryDefaults();
  void loadDeviceConfiguration();
  void initModules();

  void init()
  {
    bool isLoadFactoryDefaults = (EEDeviceStartAction == DeviceStartAction_FirstStart);

    if (!isLoadFactoryDefaults)
    {
      CONFIG_KEY_DIR = 0;
      CONFIG_KEY_PORT = 1;

      isLoadFactoryDefaults = true;

      for (unsigned char i = 0; i < 100; i++)
      {
        if (CONFIG_KEY_PIN)
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

    initModules();
  }

  void loadFactoryDefaults()
  {
    EEDeviceTransmitterConfig = EEDefaultDeviceTransmitterConfig;

    EEDeviceStartAction = DeviceStartAction_Standard;
  }

  void loadDeviceConfiguration()
  {
    ApplicationVersion = FFApplicationVersion;
    DeviceTransmitterConfig = EEDeviceTransmitterConfig;
  }

  void initModules()
  {
    Timer0Handler::init();

    GLOBAL::ADC::init(DeviceTransmitterConfig.batteryCutOff);
    GLOBAL::MultyThreading::init();

    KeyBoardDriver::init();
    IndicatorDriver::init();
  }

#define MODULE_RUN_TABLE_SIZE         (3)
__flash const void* moduleRunTable[MODULE_RUN_TABLE_SIZE] =
{
  (void*)(&(GLOBAL::ADC::run)),
  (void*)(&(IndicatorDriver::run)),
  (void*)(&(KeyBoardDriver::run)),
};

  void run()
  {
    IndicatorDriver::schedule(2, 250, 500);

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
        MCUCR |= (1<<SE); //Enable go to sleep mode
        __sleep();        //Go to sleep mode

        __no_operation();
        __no_operation();
        __no_operation();
        __no_operation();
        __no_operation();

        GLOBAL::MultyThreading::processIdleTime();
      }
    }
  }

  void switchTransmitterMode()
  {
    DeviceTransmitterConfig.transmitterMode = (TDeviceTransmitterMode)((DeviceTransmitterConfig.transmitterMode + 1) % (DeviceTransmitterMode_WithDetection + 1));
    EEDeviceTransmitterConfig.transmitterMode = DeviceTransmitterConfig.transmitterMode;

    Timer0Handler::disable();
    Timer0Handler::enable();

    switch (DeviceTransmitterConfig.transmitterMode)
    {
      case DeviceTransmitterMode_NoDetetion:
        IndicatorDriver::schedule(2, 250, 250);
        break;

      case DeviceTransmitterMode_WithDetection:
        IndicatorDriver::schedule(4, 250, 250);
        break;
    }
  }
}

#endif

